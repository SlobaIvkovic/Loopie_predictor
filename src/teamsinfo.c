#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "../inc/datastructs.h"

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

void printNames(league* lig)
{
	int i = 0;
	printf("All teams in this league:\n");
	while(i < lig->numOfTeams)
	{
		printf("%s\n", lig->teams[i++].name);
	}
}

void initStats(league* lig)
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
