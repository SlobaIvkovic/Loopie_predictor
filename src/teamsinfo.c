#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "../inc/datastructs.h"
#include "../inc/teamsinfo.h"

/*************************
Šta bude ako u prvom kolu bude odložena utakmica
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

void updateTeamsStats(league* lig, pair* allRoundPairs)
{
	int i = 0, j = 0;
	int cmpResult;
	int hit;

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
			}
				
			cmpResult = strcmp(allRoundPairs[i].awayTeam, lig->teams[j].name);
			if(cmpResult == 0)
			{
				lig->teams[j].played++;
				lig->teams[j].playedAsGuest++;
				hit++;
			}
			
			j++;
				
		// Two hits necesarry while traversing through all teams, one for the host and one for the guest		
		}while(hit < 2 && j < lig->numOfTeams);
		
		if(hit < 2)
		{
			printf("\nCant find this Team\n");
		}		
		//Go to the next pair
		i++;
	}
}

void printTeamsStats(league* lig)
{
	int i = 0;
	for(i = 0; i < lig->numOfTeams; i++)
	{
		printf("%s played %d as host %d as guest %d\n", lig->teams[i].name, lig->teams[i].played, lig->teams[i].playedAsHost, lig->teams[i].playedAsGuest);
	}
}
