#include <curl/curl.h>
#include "../inc/datastructs.h"
#include "../inc/setcurloptions.h"
#include "../inc/leagueprocessing.h"
#include "../inc/teamsinfo.h"

#define NOT_FOUND 0
#define FOUND 1
#define END_LINKS 'N'
#define LAST_PAIR lig->numOfTeams/2-1

//int processLeague(CURL *curl, chunk* s, int startRound, int endRound, char* addr, team* teams, char* filename, int numTeams)
int processLeague(CURL* curl, chunk* s, int startRound, int endRound, league* lig)
{
	// This will hold all the results when the single round processing is finished
	pair* allRoundPairs;	
	
	while(startRound < endRound)
	{
		changeRoundAddress(lig->firstRoundAddr, startRound);
		// we need a new one for every round, it holds results temporarly before it is written to a file
		// and can be discarded anytime if the round process was unsucesfull without writting corupt data to the file
		allRoundPairs = malloc(sizeof(pair) * (lig->numOfTeams/2));
		if(allRoundPairs == NULL)
		{
			printf("malloc ERROR");
		}

		printf("\nProcessing Round %d  ", startRound+1);		
		processOneRound(curl, s, lig, allRoundPairs);
		lig->roundsPlayed++;
	
		// Ako je celo kolo uspešno obraðeno rezultate iz matrice upisujemo u fajl
		// Mora postojati mehanizam da se verifikuje uspešna obrada kola
	
		// Ovde imam niz sa svim timovima, ako je prva runda, dodati svakom timu ime i inicijalizovati parametre
		if(startRound == 0)
		{
			initAllTeams(lig, allRoundPairs);
//			printNames(lig);
		}


		printf("\n");
		printAllRoundResults(allRoundPairs);
		printf("---------------------------------------------\n");
		updateTeamsStats(lig, allRoundPairs);
		saveTeamsStats(lig);
//		printTeamsStats(lig);
		printf("---------------------------------------------\n");

		saveRoundResults(allRoundPairs, lig);
			
		
		free(s->ptr);
		init_chunk(s);
		free(allRoundPairs);
	
		startRound++;
		
	}
	printTeamsStats(lig);
	
		
}

void processOneRound(CURL* curl, chunk* s, league* lig, pair* allRoundPairs)
{
	CURLcode res;
	int tries = 10;
	// TODO dynamically alocate
	char links[14][1000];
	int totalPlayedInRound;
	
	curl_easy_setopt(curl, CURLOPT_URL, lig->firstRoundAddr);
	do
	{
		res = curl_easy_perform(curl);
		if(res == CURLE_OK)
		{
			break;
		}
		else
		{
			tries--;
		}
	}while(tries);

    if(res != CURLE_OK)
    fprintf(stderr, "curl_easy_perform() failed: %s\n",
    curl_easy_strerror(res));
 	
	totalPlayedInRound = getRoundGamesLinks(s->ptr, links, lig->numOfTeams/2);
	allRoundPairs[0].numPairsFoundInRound = totalPlayedInRound;
	

	visitAllLinks(links, lig->teams, lig->teams, allRoundPairs);
}

int findSeq(char* str1, char* str2)
{
	int i = 0, j;
	int sizeToFind = 0;
	// determine size of the array to find
	while(str2[i++] != '\0');
	
	sizeToFind = i - 1;
	i = 0;
	
	for(j = 0; j < sizeToFind; j++)
		{
			if(str1[i+j] != str2[j])
			{
				break;
				return 0;
			}
		}
	
		if(j == sizeToFind)
		{
//			printf("Found!\n");
			return 1;
			
		}
		return 0;
}

int formatLink(char* str1, char* jumpAdr)
{
	int i = 0, j = 0;
	strcpy(jumpAdr, "https://int.soccerway.com");
	while(str1[i] != '\"')
	{
		if(str1[i] != '\\')
		{
			jumpAdr[j+25] = str1[i];
			j++;
		}
		i++;
	}
	jumpAdr[j+25] = '\0';

}

int getRoundGamesLinks(char* str1, char links[][1000], int numLinks)
{
	int i = 0;

	char toFind[50];
	char jumpAdr[1000];
	
	int searchResult;
	int u = 0;	
	int totalLinks;
	
	while(str1[i] != '\0' && totalLinks < numLinks)
	{
	
		strcpy(toFind, "FT");
	
		while((searchResult = findSeq(&str1[i++], toFind)) != FOUND && str1[i] != '\0');
		if(searchResult == FOUND)
		{
			totalLinks++;
			strcpy(toFind, " \\\"><a href=\\\"\\/matches\\/20");
			while(findSeq(&str1[i++], toFind) != FOUND && str1[i] != '\0');
	
			formatLink(&str1[i+14], jumpAdr);
	
			strcpy(&links[u++][0], jumpAdr);			
			
		}

		
//	visitLink(jumpAdr);
//		printf("\n\n** %s\n%d\n", jumpAdr, u-1);
	}
	links[u][0] = END_LINKS;
	return totalLinks;
}

void visitAllLinks(char links[][1000], team* teams, team* teamsWhole, pair* allPairs)
{
	int i = 0;
	while(links[i][0] != END_LINKS)
	{
		visitLink(&links[i][0], &teams[i*2], teamsWhole, i, allPairs);
		i++;
	}
}

int visitLink(char* address, team* teams, team* teamsWhole, int pairNum, pair* allPairs)
{
	char toFind[50];
	int i = 0;
	int j = 0;
	char* ptr;
	char team1[50];
	char team2[50];
	char result[10];
	char halftime[10];
	
	CURL *curl1;
	CURLcode res;
	chunk s;
	init_chunk(&s);
 	
 	
 	curl1 = curl_easy_init();
 	if(curl1)
 	{
 		curl_easy_setopt(curl1, CURLOPT_WRITEFUNCTION, writefunc);
    	curl_easy_setopt(curl1, CURLOPT_WRITEDATA, &s);
 		setCurlOptions1(curl1);	
    
    	curl_easy_setopt(curl1, CURLOPT_URL, address);
    
 		res = curl_easy_perform(curl1);
    	if(res != CURLE_OK)
    	{
      		fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
      	}
 

	getTeams(s.ptr, team1, team2);
//	printf("%s %s ", team1, team2);
	
	strcpy(allPairs[pairNum].homeTeam, team1);
	strcpy(allPairs[pairNum].awayTeam, team2);
	
	getResult(s.ptr, result, halftime);
//	printf("%s %s\n", result, halftime);
	
	strcpy(allPairs[pairNum].result, result);
	strcpy(allPairs[pairNum].halftimeResult, halftime);
	
	printf("#");

/*	
	FILE *fp;
	fp = fopen("england.lg", "a");
	fprintf(fp, "%s-%s %s %s\n", team1, team2, result, halftime);

	
	if(rd == 0)
	{
		createListOfTeams(team1, teams);
		createListOfTeams(team2, &teams[1]);
		teams[0].twoPlusTotal = 0;
		teams[1].twoPlusTotal = 0;
		
		teams[0].twoPlusAsHost = 0;
		teams[1].twoPlusAsHost = 0;
		
		teams[0].twoPlusAsGuest = 0;
		teams[1].twoPlusAsGuest = 0;
		
		teams[0].numAtLeastOne = 0;
		teams[1].numAtLeastOne = 0;
		
		teams[0].htScoresAtLeastOne = 0;
		teams[1].htScoresAtLeastOne = 0;
		
		teams[0].htConceedesAtLeastOne = 0;
		teams[1].htConceedesAtLeastOne = 0;
		
		teams[0].onePlusTwoPlus = 0;
		teams[1].onePlusTwoPlus = 0;
		
		teams[0].played = 0;
		teams[1].played = 0;
		
		teams[0].moreInFirst = 0;
		teams[1].moreInFirst = 0;
		
		teams[0].playedAsHost = 0;
		teams[1].playedAsHost = 0;
		
		teams[0].playedAsGuest = 0;
		teams[1].playedAsGuest = 0;
		
	}
	updateTeamStats(team1, teamsWhole, result, halftime, 1);
	updateTeamStats(team2, teamsWhole, result, halftime, 0);
	*/
	
	free(s.ptr);
	
	curl_easy_cleanup(curl1);
	}
	
}

void changeRoundAddress(char* leagueAddress1, int round)
{
	int u = 0;
	while(leagueAddress1[u] != '\0')
		{
			if(leagueAddress1[u] == 'c' && leagueAddress1[u+1] == 'h' && leagueAddress1[u+2] == 'a')
			{
				
				if(round > 9)
				{
				
					leagueAddress1[u+34] = round/10 + '0';
					leagueAddress1[u+35] = round%10 + '0';
					
					leagueAddress1[u+36] = '%';
					leagueAddress1[u+37] = '7';
					leagueAddress1[u+38] = 'D';
					leagueAddress1[u+39] = '\0';
				}
				else
				{
					leagueAddress1[u+34] = round % 10 + '0';
					
				//	leagueAddress1[u+4] = '%';
				//	leagueAddress1[u+5] = '7';
				//	leagueAddress1[u+6] = 'D';
				//	leagueAddress1[u+7] = '\0';
				}
			}
			u++;
		}
		u = 0;
}


// Possible cause of the program crach when longer league scans are performed
void getTeams(char* str1, char* team1, char* team2)
{
	int i = 0;
	int j = 0;
	char toFind[50];
	
	static int lock = 0;
	
	lock++;
	
	if(lock < 3)
	{
		
		strcpy(toFind, "team-title");
	
		while(findSeq(&str1[i++], toFind) != FOUND && str1[i] != '\0');
	
		strcpy(toFind, "\">");
	
		while(findSeq(&str1[i++], toFind) != FOUND && str1[i] != '\0');

		i++;

		while(str1[i] != '<')
		{	
			team1[j++] = str1[i++];
		}
		team1[j] = '\0';

		if(lock < 2)
		{
			//recursive
			getTeams(&str1[i], team2, team1);
		}
	}
	lock = 0;
}

void getResult(char* str1, char* result, char* halftime)
{
	char toFind[50];
	int i = 0;
	int j= 0;
	
	strcpy(toFind, "FT</span>");
	while(findSeq(&str1[i++], toFind) != FOUND && str1[i] != '\0');
	strcpy(toFind, " -");
	while(findSeq(&str1[i++], toFind) != FOUND && str1[i] != '\0');
	
	result[0] = str1[i - 2];
	result[1] = str1[i];
	result[2] = str1[i + 2];
	result[3] = '\0';
//	printf("%s", result);
	
	strcpy(toFind, "(HT ");
	while(findSeq(&str1[i++], toFind) != FOUND && str1[i] != '\0');
	halftime[0] = str1[i + 3];
	halftime[1] = str1[i + 5];
	halftime[2] = str1[i + 7];
	halftime[3] = '\0';
//	printf("\nhalftime %s", halftime);
}

