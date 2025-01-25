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
	
	int htScoresAtLeastOne;        //
	float htScoresAtLeastOnePCT;
	int htConceedesAtLeastOne;     //
	
	int numAtLeastOne;            // 
	int moreInFirst;               //
	int twoPlusTotal;             //
	int twoPlusAsHost;             //
	int twoPlusAsGuest;            //
	int onePlusTwoPlus;            //
	float onePlusTwoPlusPCT;
	
	int inefficientGames;
	
	int mfInd;                     // index associated with games played with more goals in the first half
	
	// New variables after refactor
	unsigned short wonAsHost;
	unsigned short lostAsHost;
	unsigned short drawAsHost;
	
	unsigned short wonAsGuest;
	unsigned short lostAsGuest;
	unsigned short drawAsGuest;
	
	unsigned short wonTotal;
	unsigned short lostTotal;
	unsigned short drawTotal;
	
	unsigned short GGAsHost;
	unsigned short GGAsGuest;
	unsigned short GGTotal;
	
	unsigned short threePlusAsHost;
	unsigned short threePlusAsGuest;
	unsigned short threePlusTotal;
	
	unsigned short zeroToTwoAsHost;
	unsigned short zeroToTwoAsGuest;
	unsigned short zeroToTwoTotal;
	
	//Add zeroToOne and that is it for now
};

typedef struct team team;

struct league
{
	char* firstRoundAddr;
	char* currentRoundAddr;
	char  subdir[7];
	int   numOfTeams;
	int   roundsPlayed;
	team* teams;
};

typedef struct league league;

struct pair
{
	char homeTeam[100];
	char awayTeam[100];
	char result[5];
	char halftimeResult[5];
	
	float totalCoeff;
	float homeAwayCoeff;
	
	float coefficient;
	
	int bothAbove;
	
	
	
	
	int numPairsFoundInRound;
};

typedef struct pair pair;

#endif

