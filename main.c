#include <stdio.h>
#include <curl/curl.h>
#include <string.h>

#include "inc/datastructs.h"

#include "./inc/setcurloptions.h"

#include "inc/leagueprocessing.h"

#include "inc/updates.h"

#include "inc/teamsinfo.h"

// Addreses of the first round
char leagueAddressITA_1_24[] = "https://int.soccerway.com/a/block_competition_matches_summary?block_id=page_competition_1_block_competition_matches_summary_10&callback_params=%7B%22page%22%3A15%2C%22block_service_id%22%3A%22competition_summary_block_competitionmatchessummary%22%2C%22round_id%22%3A82869%2C%22outgroup%22%3Afalse%2C%22view%22%3A1%2C%22competition_id%22%3A13%7D&action=changePage&params=%7B%22page%22%3A0%7D";
char leagueAddressITA_2_24[] = "https://int.soccerway.com/a/block_competition_matches_summary?block_id=page_competition_1_block_competition_matches_summary_10&callback_params=%7B%22page%22%3A19%2C%22block_service_id%22%3A%22competition_summary_block_competitionmatchessummary%22%2C%22round_id%22%3A82971%2C%22outgroup%22%3Afalse%2C%22view%22%3A1%2C%22competition_id%22%3A14%7D&action=changePage&params=%7B%22page%22%3A0%7D";

//////////////////////////////////////////////////////////
char leagueAddressENG_1_24[] = "https://int.soccerway.com/a/block_competition_matches_summary?block_id=page_competition_1_block_competition_matches_summary_10&callback_params=%7B%22page%22%3A14%2C%22block_service_id%22%3A%22competition_summary_block_competitionmatchessummary%22%2C%22round_id%22%3A81780%2C%22outgroup%22%3Afalse%2C%22view%22%3A1%2C%22competition_id%22%3A8%7D&action=changePage&params=%7B%22page%22%3A0%7D";

//////////////////////////////////////////////////////
char leagueAddressGER_1_24[] = "https://int.soccerway.com/a/block_competition_matches_summary?block_id=page_competition_1_block_competition_matches_summary_10&callback_params=%7B%22page%22%3A12%2C%22block_service_id%22%3A%22competition_summary_block_competitionmatchessummary%22%2C%22round_id%22%3A81840%2C%22outgroup%22%3Afalse%2C%22view%22%3A1%2C%22competition_id%22%3A9%7D&action=changePage&params=%7B%22page%22%3A0%7D";


// Addresses of the current round
char currentRoundAddrITA_1_24[] = "https://int.soccerway.com/national/italy/serie-a/20242025/regular-season/r82869/";
char currentRoundAddrITA_2_24[] = "https://int.soccerway.com/national/italy/serie-b/20242025/regular-season/r82971/";

char currentRoundAddrENG_1_24[] = "https://int.soccerway.com/national/england/premier-league/20242025/regular-season/r81780/";
char currentRoundAddrGER_1_24[] = "https://int.soccerway.com/national/germany/bundesliga/20242025/regular-season/r81840/";



#define CURRENT_ROUND_ADDR_ITA_1_24 currentRoundAddrITA_1_24
#define CURRENT_ROUND_ADDR_ITA_2_24 currentRoundAddrITA_2_24


#define CURRENT_ROUND_ADDR_ENG_1_24 currentRoundAddrENG_1_24
#define CURRENT_ROUND_ADDR_GER_1_24 currentRoundAddrGER_1_24


//////
#define FIRST_ROUND_ADDR_ITA_1_24       leagueAddressITA_1_24
#define NUM_TEAMS_ITA_1_24              20

#define FIRST_ROUND_ADDR_ENG_1_24       leagueAddressENG_1_24
#define NUM_TEAMS_ENG_1_24              20

#define FIRST_ROUND_ADDR_GER_1_24       leagueAddressGER_1_24
#define NUM_TEAMS_GER_1_24              18


// ita dva first ruond address
#define FIRST_ROUND_ADDR_ITA_2_24       leagueAddressITA_2_24
#define NUM_TEAMS_ITA_2_24              20
/************************************************************************************************************************************************/

char leagueAddress1ENG23[] = "https://int.soccerway.com/a/block_competition_matches_summary?block_id=page_competition_1_block_competition_matches_summary_10&callback_params=%7B%22page%22%3A37%2C%22block_service_id%22%3A%22competition_summary_block_competitionmatchessummary%22%2C%22round_id%22%3A76443%2C%22outgroup%22%3Afalse%2C%22view%22%3A1%2C%22competition_id%22%3A8%7D&action=changePage&params=%7B%22page%22%3A0%7D";
char leagueAddress1GER23[] = "https://int.soccerway.com/a/block_competition_matches_summary?block_id=page_competition_1_block_competition_matches_summary_10&callback_params=%7B%22page%22%3A33%2C%22block_service_id%22%3A%22competition_summary_block_competitionmatchessummary%22%2C%22round_id%22%3A76158%2C%22outgroup%22%3Afalse%2C%22view%22%3A1%2C%22competition_id%22%3A9%7D&action=changePage&params=%7B%22page%22%3A0%7D";
char leagueAddress1ITA23[] = "https://int.soccerway.com/a/block_competition_matches_summary?block_id=page_competition_1_block_competition_matches_summary_10&callback_params=%7B%22page%22%3A%2237%22%2C%22block_service_id%22%3A%22competition_summary_block_competitionmatchessummary%22%2C%22round_id%22%3A%2277308%22%2C%22outgroup%22%3A%22%22%2C%22view%22%3A%221%22%2C%22competition_id%22%3A%2213%22%7D&action=changePage&params=%7B%22page%22%3A0%7D";
char leagueAddress1ESP23[] = "https://int.soccerway.com/a/block_competition_matches_summary?block_id=page_competition_1_block_competition_matches_summary_10&callback_params=%7B%22page%22%3A37%2C%22block_service_id%22%3A%22competition_summary_block_competitionmatchessummary%22%2C%22round_id%22%3A76831%2C%22outgroup%22%3Afalse%2C%22view%22%3A1%2C%22competition_id%22%3A7%7D&action=changePage&params=%7B%22page%22%3A0%7D";
char leagueAddress1NED23[] = "https://int.soccerway.com/a/block_competition_matches_summary?block_id=page_competition_1_block_competition_matches_summary_10&callback_params=%7B%22page%22%3A33%2C%22block_service_id%22%3A%22competition_summary_block_competitionmatchessummary%22%2C%22round_id%22%3A77314%2C%22outgroup%22%3Afalse%2C%22view%22%3A1%2C%22competition_id%22%3A1%7D&action=changePage&params=%7B%22page%22%3A0%7D";
char leagueAddress1POR23[] = "https://int.soccerway.com/a/block_competition_matches_summary?block_id=page_competition_1_block_competition_matches_summary_10&callback_params=%7B%22page%22%3A33%2C%22block_service_id%22%3A%22competition_summary_block_competitionmatchessummary%22%2C%22round_id%22%3A76181%2C%22outgroup%22%3Afalse%2C%22view%22%3A1%2C%22competition_id%22%3A63%7D&action=changePage&params=%7B%22page%22%3A0%7D";



#define ENGLAND_LEAGUE1_23_ADR	    leagueAddress1ENG23
#define GERMANY_LEAGUE1_23_ADR	    leagueAddress1GER23
#define ITALY_LEAGUE1_23_ADR        leagueAddress1ITA23
#define SPAIN_LEAGUE1_23_ADR	    leagueAddress1ESP23
#define NETHERLANDS_LEAGUE1_23_ADR  leagueAddress1NED23
#define PORTUGAL_LEAGUE1_23_ADR		leagueAddress1POR23

/*****************************************************************************************************************************************************/


void initLeague(league* lig, char* currentRoundAddr, char* firstRoundAddr, int numTeams, char* subdir);

int lupdates(curlAndChunkPtrs* curlAndChunk, int* lastProcessedRound, int* lastRoundPlayed, char* addr, char* subdir);
void showTeamsStats(league* lig);

int main(int argc, char* argv[])
{
	/* Not necessarry anymore since team pointer is now part of league struct but I'll leave it here
	 commented as a reference and reminder on team struct
	
	team teamsEngland1[20];
	team teamsGermany1[18];
	team teamsItaly1[20];
	team teamsSpain1[20];
	team teamsNetherlands1[18];
	team teamsPortugal1[18];
	*/
	
	// Printf AVALIABLE LEAGUES, this is for the gui
	setbuf(stdout, NULL);
	printf("=======================|========================\n"); 
	printf("Hello from the Loopie_predictor backand!\n");
	printf("=======================|========================\n");
	
	
	league* italy1   = malloc(sizeof(league));
	league* italy2   = malloc(sizeof(league));
	
	league* england1 = malloc(sizeof(league));
	league* germany1 = malloc(sizeof(league));
	
	initLeague(italy1, CURRENT_ROUND_ADDR_ITA_1_24, FIRST_ROUND_ADDR_ITA_1_24, NUM_TEAMS_ITA_1_24, "ita1");
	initLeague(italy2, CURRENT_ROUND_ADDR_ITA_2_24, FIRST_ROUND_ADDR_ITA_2_24, NUM_TEAMS_ITA_2_24, "ita2");
	
	initLeague(england1, CURRENT_ROUND_ADDR_ENG_1_24, FIRST_ROUND_ADDR_ENG_1_24, NUM_TEAMS_ENG_1_24, "eng1");
	initLeague(germany1, CURRENT_ROUND_ADDR_GER_1_24, FIRST_ROUND_ADDR_GER_1_24, NUM_TEAMS_GER_1_24, "ger1");
	
	
	CURL *curl;
	CURLcode res;
  
  	chunk s;
	init_chunk(&s);
  
  	curl_global_init(CURL_GLOBAL_DEFAULT);

  	curl = curl_easy_init();
  	if (curl) 
	{
		setCurlOptions(curl, &s);
	    // Set cookies
    	curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "cookies.txt");
    	curl_easy_setopt(curl, CURLOPT_COOKIEJAR, "cookies.txt");


//#define VERBOSE_DEBUG
    
#if defined VERBOSE_DEBUG    
    	curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
#endif    
		
		curlAndChunkPtrs curlAndChunk;
	
		curlAndChunk.curl = curl;
		curlAndChunk.s = &s;
		
		//int currentRound, lastRound;
		//
		int lastProcessedRound, lastPlayedRound;
		
		if(strcmp(argv[1], "guiita1") == 0)
		{
			lastProcessedRound = findLastRound("ita1");
			lastPlayedRound = findCurrentRound(curl, &s, currentRoundAddrITA_1_24);
			processLeague(curl, &s, lastProcessedRound, lastPlayedRound, italy1);
		}
		if(strcmp(argv[1], "guiita2") == 0)
		{
			lastProcessedRound = findLastRound("ita2");
			lastPlayedRound = findCurrentRound(curl, &s, currentRoundAddrITA_1_24);
			processLeague(curl, &s, lastProcessedRound, lastPlayedRound, italy2);
		}
		
		
	
		int roundsToProcess;
		if(strcmp(argv[1], "ligupdates") == 0)
		{
			
			if(strcmp(argv[2], "ita1") == 0)
			{
				roundsToProcess = lupdates(&curlAndChunk, &lastProcessedRound, &lastPlayedRound, currentRoundAddrITA_1_24, "ita1");
				printf("%d Rounds to process", roundsToProcess);
				
			}
		}
		
		int statsAvailable;
		if(strcmp(argv[1], "ligstats") == 0)
		{	
			statsAvailable = loadTeams(italy1, "ita1");
			if(statsAvailable)
			{
				showTeamsStats(italy1);
			}
			else
			{
				printf("No data available yet for this League\n");
			}
		}
		
		if(strcmp(argv[1], "ligprocess") == 0)
		{
		//	currentRound = findCurrentRound(curl, &s, currentRoundAddrITA_1_24);
		//	lastRound = findLastRound("ita1");
			
			roundsToProcess = lupdates(&curlAndChunk, &lastProcessedRound, &lastPlayedRound, currentRoundAddrITA_1_24, "ita1");
		

			//
			if(lastProcessedRound == 0)
			{
				printf("No data available, processing league from round 1 to round %d\n", lastPlayedRound-1);
			}
			else if(lastProcessedRound < lastPlayedRound - 1)
			{
				printf("Processing league from round %d to round %d\n", lastProcessedRound+1, lastPlayedRound-1);
				statsAvailable = loadTeams(italy1, "ita1");
				if(statsAvailable)
				{
					printf("Stats before league update:\n");
					showTeamsStats(italy1);
				}
				else
				{
					printf("No data available yet for this League\n");
				}
				
				
			}
			else
			{
				printf("League stats are up to date. Stats will be shown\n");
				statsAvailable = loadTeams(italy1, "ita1");
				if(statsAvailable)
				{
					printf("Stats:\n");
					showTeamsStats(italy1);
				}
				else
				{
					printf("Stats Error ocured\n");
				}
			}
			
				// TESTING ONLY
		//	lastPlayedRound = 15;
		
		    // Process all rounds but the current one displayed on the site since it might not be finished yet hence -1
			processLeague(curl, &s, lastProcessedRound, lastPlayedRound-1, italy1);
			printf("League Processed\n");
			showTeamsStats(italy1);
		}
	
		
		
    	curl_easy_cleanup(curl);
  	}

  	curl_global_cleanup();
  

  	return 0;
}


void initLeague(league* lig, char* currentRoundAddr, char* firstRoundAddr, int numTeams, char* subdir)
{
	lig->numOfTeams = numTeams;
	strcpy(lig->subdir, subdir);
	lig->firstRoundAddr = firstRoundAddr;
	lig->currentRoundAddr = currentRoundAddr;
	lig->teams = malloc((sizeof(team))*(numTeams));
	lig->roundsPlayed = 0;
	
	
}

int lupdates(curlAndChunkPtrs* curlAndChunk, int* lastProcessedRound, int* lastPlayedRound, char* addr, char* subdir)
{
	*lastProcessedRound = findLastRound("ita1");
	*lastPlayedRound = findCurrentRound(curlAndChunk->curl, curlAndChunk->s, currentRoundAddrITA_1_24);
	if(*lastProcessedRound == 0)
	{
		printf("No rounds has been processed so far\n");
	}
	else
	{
		printf("Last round processed: %d\n", *lastProcessedRound);
	}
	printf("Current league round: %d\n", *lastPlayedRound);
	return lastPlayedRound - lastProcessedRound;
}

void showTeamsStats(league* lig)
{
	int i;
	for(i = 0; i < lig->numOfTeams; i++)
	{
		printf(">>%s<<\n", lig->teams[i].name);
		printf("|%hu %hu|\n", lig->teams[i].playedAsHost, lig->teams[i].playedAsGuest);
				
		printf("|%hu %hu %hu %hu %hu %hu|\n", lig->teams[i].wonAsHost, lig->teams[i].wonAsGuest,
										  lig->teams[i].drawAsHost, lig->teams[i].drawAsGuest,
										  lig->teams[i].lostAsHost, lig->teams[i].lostAsGuest);
				
		printf("|%hu %hu %hu %hu %hu %hu|\n", lig->teams[i].GGAsHost, lig->teams[i].GGAsGuest,
		                                              lig->teams[i].threePlusAsHost, lig->teams[i].threePlusAsGuest,
													  lig->teams[i].zeroToTwoAsHost, lig->teams[i].zeroToTwoAsGuest);
													  
		printf("|%hu %hu %hu %hu %hu|\n", lig->teams[i].numAtLeastOne, lig->teams[i].moreInFirst,
		                                          lig->teams[i].twoPlusAsHost, lig->teams[i].twoPlusAsGuest,
											      lig->teams[i].onePlusTwoPlus);	
	}
}

#ifdef LEAGUE_INIT_TEST
{
	
	printf("%s\n %s\n %d\n %s\n", england1->currentRoundAddr, england1->firstRoundAddr, england1->numOfTeams, england1->filename);
	system("pause");

	strcpy(england1->teams[1].name, "Brighton and Hove Albion");
	printf("%s", england1->teams[1].name);
	system("pause");
}

#endif
