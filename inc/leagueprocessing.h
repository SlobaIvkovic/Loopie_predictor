#ifndef LEAGUEPROCESSING_H
#define LEAGUEPROCESSING_H

//#include "datastructs.h"

//int processLeague(CURL *curl, chunk* s, int startRound, int endRound, char* addr, team* teams, char* filename, int numTeams);
int processLeague(CURL *curl, chunk* s, int startRound, int endRound, league* lig);

int findSeq(char* str1, char* str2);
int formatLink(char* str1, char* jumpAdr);

int getRoundGamesLinks(char* str1, char links[][1000], int numLinks);
void getTeams(char* str1, char* team1, char* team2);
void getResult(char* str1, char* result, char* halftime);


void visitAllLinks(char links[][1000], team* teams, team* teamsWhole);
int visitLink(char* address, team* teams, team* teamsWhole);
void changeRoundAddress(char* leagueAddress1, int round);

#endif
