#ifndef TEAMSINFO_H
#define TEAMSINFO_H

int initAllTeams(league* lig, pair* allPairs);
int initAllTeamsNames(league* lig, pair* allPairs);
void initAllTeamsStats(league* lig);

void printAllRoundResults(pair* allRoundPairs);
void printNames(league* lig);

void updateTeamsStats(league* lig, pair* allRoundPairs);
void printTeamsStats(league* lig);

#endif
