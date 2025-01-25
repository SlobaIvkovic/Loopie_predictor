#ifndef TEAMSINFO_H
#define TEAMSINFO_H

int initAllTeams(league* lig, pair* allPairs);
int initAllTeamsNames(league* lig, pair* allPairs);
void initAllTeamsStats(league* lig);

void printAllRoundResults(pair* allRoundPairs);
void printNames(league* lig);
void saveNames(league* lig);

void updateTeamsStats(league* lig, pair* allRoundPairs);
void updateLegacyStats(team* tim, char* halftime, char* result, int hostIndex, int guestIndex);
void updateWinsLosses(team* tim, char ft1, char ft2, int hostIndex, int guestIndex);
void updateGoalsStats(team* tim, char ft1, char ft2, int hostIndex, int guestIndex);
void printTeamsStats(league* lig);
void saveTeamsStats(league* lig);
void saveRoundResults(pair* allRoundPairs, league* lig);

int loadTeams(league* lig, char* subdir);

#endif
