#ifndef TEAM_H
#define TEAM_H

#define TEAMS_LIST_MAX_SIZE 28


struct chunk {
  char *ptr;
  size_t len;
};


typedef struct chunk chunk;

struct team
{
	int index;
	char name[100];
	char allResults[300];
	int played;
	int playedAsHost;
	int playedAsGuest;
	
	int htScoredConceeded;
	int htAverage;
	int numGamesScoCon;
	
	int htScoresAtLeastOne;
	float htScoresAtLeastOnePCT;
	int htConceedesAtLeastOne;
	
	int numAtLeastOne;
	int moreInFirst;
	int twoPlusTotal;
	int twoPlusAsHost;
	int twoPlusAsGuest;
	int onePlusTwoPlus;
	float onePlusTwoPlusPCT;
	
	int inefficientGames;
	
	int mfInd;                     // index associated with games played with more goals in the first half
};

typedef struct team team;

struct pair
{
	char homeTeam[100];
	char awayTeam[100];
	char result[5];
	char halfTimeResult[5];
	
	float totalCoeff;
	float homeAwayCoeff;
	
	float coefficient;
	
	int bothAbove;
	
	
	
};

typedef struct pair pair;

#endif

