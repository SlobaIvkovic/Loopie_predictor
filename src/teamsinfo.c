#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "../inc/datastructs.h"
#include "../inc/teamsinfo.h"

/*************************
�ta bude ako u prvom kolu bude odlo�ena utakmica
malo verovatno ali moguce, onda lista timova nije dobro
inicijalizovana
*/////////////////////////



int initAllTeams(league* lig, pair* allPairs)
{
	initAllTeamsNames(lig, allPairs);
	initAllTeamsStats(lig);
}

int initAllTeamsNames(league* lig, pair* allPairs)
{
	int i = 0;
	while(i < lig->numOfTeams/2)
	{
		strcpy(lig->teams[i*2].name, allPairs[i].homeTeam);
		strcpy(lig->teams[i*2+1].name, allPairs[i].awayTeam);
		i++;
	}
}

void initAllTeamsStats(league* lig)
{
	int i = 0;
	while(i < lig->numOfTeams)
	{
		lig->teams[i].twoPlusTotal = 0;
		
		lig->teams[i].twoPlusAsHost = 0;
		
		lig->teams[i].twoPlusAsGuest = 0;
		
		lig->teams[i].numAtLeastOne = 0;
		
		lig->teams[i].htScoresAtLeastOne = 0;
		
		lig->teams[i].htConceedesAtLeastOne = 0;
		
		lig->teams[i].onePlusTwoPlus = 0;

		lig->teams[i].played = 0;
		
		lig->teams[i].moreInFirst = 0;
		
		lig->teams[i].playedAsHost = 0;
		
		lig->teams[i].playedAsGuest = 0;
		
		//
		
//		lig->teams[i].GG = 0;

		i++;
	}
}

void printAllRoundResults(pair* allRoundPairs)
{
	int i = 0;
	for(i = 0; i < allRoundPairs[0].numPairsFoundInRound; i++)
	{
		printf("%s %s %s %s\n", allRoundPairs[i].homeTeam, allRoundPairs[i].awayTeam, allRoundPairs[i].result, allRoundPairs[i].halftimeResult);
	}
	
}

void printNames(league* lig)
{
	int i = 0;
	printf("\nAll teams in this league:\n");
	while(i < lig->numOfTeams)
	{
		printf("%s\n", lig->teams[i++].name);
	}
}

void saveNames(league* lig)
{
	int i = 0;
	char dir[50] = "../DATA/";
	strcat(dir, lig->subdir);
	strcat(dir, "/teamsnames.lg");
	FILE* fp = fopen(dir, "w");
	
	while(i < lig->numOfTeams)
	{
		fprintf(fp, "%s\n", lig->teams[i++].name);
	}
	fclose(fp);
}

int loadTeams(league* lig, char* subdir)
{
	int aux, aux2, aux3;
	char aux1[70] = "a";
	int i = 0;
	int j = 0;
	
	//Possibly check the existance of the folder first, make some sort of double check
	char nameBuff[50];
	char statsLine[200];
	
	char str[50] = "../DATA/";
	strcat(str, subdir);
	strcat(str,"/stats.lg");
	// check if the file is present
	FILE* fp = fopen(str, "r");
	if(fp == NULL)
	{
		printf("Stats file for this league does not exist or can't be opened\n");
		// if not, initialize team stats to 0
//		initAllTeamsStats(lig);
		return 0;
		
	}
	else
	{
		printf("Reading stats\n");
		
		fscanf(fp,"%d", &lig->roundsPlayed);
		fgets(nameBuff, 50, fp); // Swallows the new line
		
			while(!feof(fp))
			{
				fgets(nameBuff, sizeof(nameBuff), fp);
			//	fscanf(fp, "%s", nameBuff);
				
				while(nameBuff[j] != '\n')
				{
					lig->teams[i].name[j] = nameBuff[j];
					j++;
				}
				lig->teams[i].name[j] = '\0';
				j = 0;
			//	printf(">>%s<<\n", lig->teams[i].name);



				
				fscanf(fp, "%*s %hu %*s %hu", &lig->teams[i].playedAsHost, &lig->teams[i].playedAsGuest);
				
				fscanf(fp, "%*s %hu %*s %hu %*s %hu %*s %hu %*s %hu %*s %hu", &lig->teams[i].wonAsHost, &lig->teams[i].wonAsGuest,
													                          &lig->teams[i].drawAsHost, &lig->teams[i].drawAsGuest,
													                          &lig->teams[i].lostAsHost, &lig->teams[i].lostAsGuest);
													                          
				fscanf(fp, "%*s %hu %*s %hu %*s %hu %*s %hu %*s %hu %*s %hu", &lig->teams[i].GGAsHost, &lig->teams[i].GGAsGuest,
		                                                                      &lig->teams[i].threePlusAsHost, &lig->teams[i].threePlusAsGuest,
																              &lig->teams[i].zeroToTwoAsHost, &lig->teams[i].zeroToTwoAsGuest);
																  
				fscanf(fp, "%*s %hu %*s %hu %*s %hu %*s %hu %*s %hu", &lig->teams[i].numAtLeastOne, &lig->teams[i].moreInFirst,
		                                                              &lig->teams[i].twoPlusAsHost, &lig->teams[i].twoPlusAsGuest,
																      &lig->teams[i].onePlusTwoPlus);
																	  
				fgets(nameBuff, 50, fp); // swallow new line													  												  									                          


//Testing
/*				printf("|%hu %hu|\n", lig->teams[i].playedAsHost, lig->teams[i].playedAsGuest);
				
				printf("|%hu %hu %hu %hu %hu %hu|\n", lig->teams[i].wonAsHost, lig->teams[i].wonAsGuest,
										  lig->teams[i].drawAsHost, lig->teams[i].drawAsGuest,
										  lig->teams[i].lostAsHost, lig->teams[i].lostAsGuest);
				
				printf("|%hu %hu %hu %hu %hu %hu|\n", lig->teams[i].GGAsHost, lig->teams[i].GGAsGuest,
		                                              lig->teams[i].threePlusAsHost, lig->teams[i].threePlusAsGuest,
													  lig->teams[i].zeroToTwoAsHost, lig->teams[i].zeroToTwoAsGuest);
													  
				printf("|%hu %hu %hu %hu %hu|\n", lig->teams[i].numAtLeastOne, lig->teams[i].moreInFirst,
		                                          lig->teams[i].twoPlusAsHost, lig->teams[i].twoPlusAsGuest,
											      lig->teams[i].onePlusTwoPlus);									  
*/				
				
				
				i++;
				if(i == lig->numOfTeams)
				break;
				
			}

		fclose(fp);
		return 1;
		
	}
		
	
	// if the file is present read line by line until the team name is found
	// when found read in one by one stat 
}

void updateTeamsStats(league* lig, pair* allRoundPairs)
{
	int i = 0, j = 0;
	int cmpResult;
	int hit;
	int indexes[2];

	//needs to be done for all teams when the round processing is finished
	while(i < allRoundPairs[0].numPairsFoundInRound)
	{	
		j = 0;
		hit = 0;
		do
		{
			// INSIDE THIS WHILE CHECK BOTH HOME AND AWAY
			cmpResult = strcmp(allRoundPairs[i].homeTeam, lig->teams[j].name);
			if( cmpResult == 0)
			{
				lig->teams[j].played++;
				lig->teams[j].playedAsHost++;
				
				hit++;
				indexes[0] = j;
			}
				
			cmpResult = strcmp(allRoundPairs[i].awayTeam, lig->teams[j].name);
			if(cmpResult == 0)
			{
				lig->teams[j].played++;
				lig->teams[j].playedAsGuest++;
				
				hit++;
				indexes[1] = j;
			}
			
			j++;
				
		// Two hits necesarry while traversing through all teams, one for the host and one for the guest		
		}while(hit < 2 && j < lig->numOfTeams);
		
		if(hit < 2)
		{
			printf("\nCant find this Team\n");
		}
		else
		{
			updateLegacyStats(lig->teams, allRoundPairs[i].halftimeResult, allRoundPairs[i].result, indexes[0], indexes[1]);
			
			updateWinsLosses(lig->teams, allRoundPairs[i].result[0], allRoundPairs[i].result[2], indexes[0], indexes[1]);
			updateGoalsStats(lig->teams, allRoundPairs[i].result[0], allRoundPairs[i].result[2], indexes[0], indexes[1]);
			
		}		
		//Go to the next pair
		i++;
	}
}

void updateLegacyStats(team* tim, char* halftime, char* result, int hostIndex, int guestIndex)
{
	int ht;
	int ft;
	
	ft = result[0] - '0' + result[2] - '0';
	ht = halftime[0] - '0' + halftime[2] - '0';
	
	int homeFT;
	int awayFT;
	
	int homeHT;
	int awayHT;
	
	if(halftime[0] - '0' >= 1)
	{
		tim[hostIndex].htScoresAtLeastOne++;
		tim[guestIndex].htConceedesAtLeastOne++;
	}
	if(halftime[2] - '0' >=1 )
	{
		tim[guestIndex].htScoresAtLeastOne++;
		tim[hostIndex].htConceedesAtLeastOne++;
	}
	/***********************************************************************/
	if(ht > (ft - ht))
	{
		tim[hostIndex].moreInFirst++;
		tim[guestIndex].moreInFirst++;
	}
			
	if(ht >= 1)
	{
		tim[hostIndex].numAtLeastOne++;
		tim[guestIndex].numAtLeastOne++;
		if(ft >= 2)
		{
			tim[hostIndex].onePlusTwoPlus++;
			tim[guestIndex].onePlusTwoPlus++;
		}
	}
	
	if(ht >= 2)
	{
		tim[hostIndex].twoPlusTotal++;
		tim[guestIndex].twoPlusTotal++;
		
		tim[hostIndex].twoPlusAsHost++;
		tim[guestIndex].twoPlusAsGuest++;
	}

}

// ovde imam indekse domacina i gosta u listi svih timova
// 

void updateWinsLosses(team* tim, char ft1, char ft2, int hostIndex, int guestIndex)
{
	if(ft1 > ft2)
	{
		tim[hostIndex].wonAsHost++;
		tim[guestIndex].lostAsHost++;
	}
	else if(ft1 < ft2)
	{
		tim[guestIndex].wonAsGuest++;
		tim[hostIndex].lostAsHost++;
	}
	else
	{
		tim[hostIndex].drawAsHost++;
		tim[guestIndex].drawAsGuest++;
	} 
}

void updateGoalsStats(team* tim, char ft1, char ft2, int hostIndex, int guestIndex)
{
	int allGoals = ft1 - '0' + ft2 - '0';
	if(allGoals > 2)
	{
		tim[hostIndex].threePlusAsHost++;
		tim[guestIndex].threePlusAsGuest++;
	}
	else
	{
		tim[hostIndex].zeroToTwoAsHost++;
		tim[guestIndex].zeroToTwoAsGuest++;
	}
	
	if(ft1 - '0' && ft2 - '0')
	{
		tim[hostIndex].GGAsHost++;
		tim[guestIndex].GGAsGuest++;
	}
}

void printTeamsStats(league* lig)
{
	int i = 0;
	for(i = 0; i < lig->numOfTeams; i++)
	{
		printf("\n%s played %d as host %d as guest %d\n", lig->teams[i].name, lig->teams[i].played, lig->teams[i].playedAsHost, lig->teams[i].playedAsGuest);
		/************************** Legacy Stats ********************************************************************************************************/
		printf("\n|2+HT %d|   |2+HT_D %d|   |2+HT_G %d|\n", lig->teams[i].twoPlusTotal, lig->teams[i].twoPlusAsHost, lig->teams[i].twoPlusAsGuest);
		printf("\n|1+HT %d|   |1+2+ %d|     |I>II %d|\n", lig->teams[i].numAtLeastOne, lig->teams[i].onePlusTwoPlus, lig->teams[i].moreInFirst);
		printf("\nscores 1+ht %d conceedes 1+ht %d\n", lig->teams[i].htScoresAtLeastOne, lig->teams[i].htConceedesAtLeastOne);
		/************************************************************************************************************************************************/
		printf("\nWon as host %d as guest %d\n",lig->teams[i].wonAsHost, lig->teams[i].wonAsGuest);
		printf("\n3+ as host %d as guest %d\n",lig->teams[i].threePlusAsHost, lig->teams[i].threePlusAsGuest);
		printf("\n0-2 as host %d as guest %d\n",lig->teams[i].zeroToTwoAsHost, lig->teams[i].zeroToTwoAsGuest);
		printf("\nGG as host %d as guest %d\n",lig->teams[i].GGAsHost, lig->teams[i].GGAsGuest);

	}
}

void saveTeamsStats(league* lig)
{
	int i;
	FILE* fp;
	char str[30] = "../DATA/";
	strcat(str, lig->subdir);
	strcat(str, "/stats.lg");
	fp = fopen(str, "w");
	fprintf(fp, "%d\n", lig->roundsPlayed);
	for(i = 0; i < lig->numOfTeams; i++)
	{
		//
		fprintf(fp, "%s\n", lig->teams[i].name);
		
		// Plyed Games 
		fprintf(fp, "Ph %d Pg %d ", lig->teams[i].playedAsHost, lig->teams[i].playedAsGuest);
		
		// Game Outcome Stats
		fprintf(fp, "Wh %d Wg %d Dh %d Dg %d Lh %d Lg %d ", lig->teams[i].wonAsHost, lig->teams[i].wonAsGuest,
		 lig->teams[i].drawAsHost,lig->teams[i].drawAsGuest, lig->teams[i].lostAsHost, lig->teams[i].lostAsGuest);
		 
		// Goal Stats
		 fprintf(fp, "GGh %d GGg %d 3+h %d 3+g %d 02h %d 02g %d ", lig->teams[i].GGAsHost, lig->teams[i].GGAsGuest,
		                                                          lig->teams[i].threePlusAsHost, lig->teams[i].threePlusAsGuest,
																  lig->teams[i].zeroToTwoAsHost, lig->teams[i].zeroToTwoAsGuest);
																  
		// Legacy Stats														  
	    fprintf(fp, "ht1+ %d I>II %d ht2+H %d ht2+g %d 1+2+ %d\n", lig->teams[i].numAtLeastOne, lig->teams[i].moreInFirst,
		                                                          lig->teams[i].twoPlusAsHost, lig->teams[i].twoPlusAsGuest,
																  lig->teams[i].onePlusTwoPlus);															  
		 
	}
	fclose(fp);
	
}

void saveRoundResults(pair* allRoundPairs, league* lig)
{
	FILE* fp;
	char str[254] = "../DATA/";
	strcat(str, lig->subdir);
	strcat(str, "/results.lg");
	fp = fopen(str, "a");
	if(fp == NULL)
	{
		perror("Error opening file");
    return;
	}
	fprintf(fp, "%d\n", lig->roundsPlayed);
	int i = 0;
	for(i = 0; i < allRoundPairs[0].numPairsFoundInRound; i++)
	{
		fprintf(fp, "%s %s %s %s\n", allRoundPairs[i].homeTeam, allRoundPairs[i].awayTeam, allRoundPairs[i].result, allRoundPairs[i].halftimeResult);
		
	}
	fprintf(fp, "_________________________________________________\n\n");
	fclose(fp);
}
