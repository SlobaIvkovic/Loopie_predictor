#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "../inc/datastructs.h"
#include "../inc/teamsinfo.h"

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

void printAllRoundResults(pair* allRoundPairs, int numPairs)
{
	int i = 0;
	for(i = 0; i < numPairs; i++)
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
	int cmpResult = 1;
	//needs to be done for all teams when the round processing is finished
	while(i < lig->numOfTeams/2)
	{
		//for every pair find corresponding teams
		// strcmp with all teams in the league both host and guest
		
		//find in the list of teams
		// when found update its stats
		
		while(cmpResult != 0 && j < lig->numOfTeams)
		{
			cmpResult = strcmp(allRoundPairs[i].homeTeam, lig->teams[j].name);
			j++;	
		}
		if(cmpResult == 0)
		{
			j--;
			lig->teams[j].played++;
			lig->teams[j].playedAsHost++;
			//update stats team index, host guest, ht ft
		}
		else
		{
			printf("\nCant find this host\n");
		}
		j = 0;
		cmpResult = 1;
		while(cmpResult != 0 && j < lig->numOfTeams)
		{
			cmpResult = strcmp(allRoundPairs[i].awayTeam, lig->teams[j].name);
			j++;
		}
		if(cmpResult == 0)
		{
			j--;
			lig->teams[j].played++;
			lig->teams[j].playedAsGuest++;
		}
		else
		{
			printf("\nCant find this guest\n");
		}
		

		//Go to the next pair
		i++;
		j = 0;
		cmpResult = 1;
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
