#include <stdio.h>
#include <curl/curl.h>
#include <string.h>

#include "inc/datastructs.h"

#include "./inc/setcurloptions.h"

#include "inc/leagueprocessing.h"

#include "inc/updates.h"

// Addreses of the first round
char leagueAddress1ITA24[] = "https://int.soccerway.com/a/block_competition_matches_summary?block_id=page_competition_1_block_competition_matches_summary_10&callback_params=%7B%22page%22%3A15%2C%22block_service_id%22%3A%22competition_summary_block_competitionmatchessummary%22%2C%22round_id%22%3A82869%2C%22outgroup%22%3Afalse%2C%22view%22%3A1%2C%22competition_id%22%3A13%7D&action=changePage&params=%7B%22page%22%3A0%7D";
char leagueAddress1ENG24[] = "https://int.soccerway.com/a/block_competition_matches_summary?block_id=page_competition_1_block_competition_matches_summary_10&callback_params=%7B%22page%22%3A14%2C%22block_service_id%22%3A%22competition_summary_block_competitionmatchessummary%22%2C%22round_id%22%3A81780%2C%22outgroup%22%3Afalse%2C%22view%22%3A1%2C%22competition_id%22%3A8%7D&action=changePage&params=%7B%22page%22%3A0%7D";
char leagueAddress1GER24[] = "https://int.soccerway.com/a/block_competition_matches_summary?block_id=page_competition_1_block_competition_matches_summary_10&callback_params=%7B%22page%22%3A12%2C%22block_service_id%22%3A%22competition_summary_block_competitionmatchessummary%22%2C%22round_id%22%3A81840%2C%22outgroup%22%3Afalse%2C%22view%22%3A1%2C%22competition_id%22%3A9%7D&action=changePage&params=%7B%22page%22%3A0%7D";


// Addresses of the current round
char currentRoundAddr1ITA[] = "https://int.soccerway.com/national/italy/serie-a/20242025/regular-season/r82869/";
char currentRoundAddr1ENG[] = "https://int.soccerway.com/national/england/premier-league/20242025/regular-season/r81780/";
char currentRoundAddr1GER[] = "https://int.soccerway.com/national/germany/bundesliga/20242025/regular-season/r81840/";

#define CURRENT_ROUND_ADDR_ITA1 currentRoundAddr1ITA
#define CURRENT_ROUND_ADDR_ENG1 currentRoundAddr1ENG
#define CURRENT_ROUND_ADDR_GER1 currentRoundAddr1GER

#define FIRST_ROUND_ADDR_ITA1_24     leagueAddress1ITA24
#define NUM_TEAMS_ITA1              20
#define FIRST_ROUND_ADDR_ENG1_24    leagueAddress1ENG24
#define NUM_TEAMS_ENG1              20
#define FIRST_ROUND_ADDR_GER1_24     leagueAddress1GER24
#define NUM_TEAMS_GER1              18


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


void initLeague(league* lig, char* currentRoundAddr, char* firstRoundAddr, int numTeams, char* subdir);

int main(void)
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
	
	league* italy1   = malloc(sizeof(league));
	league* england1 = malloc(sizeof(league));
	league* germany1 = malloc(sizeof(league));
	
	initLeague(italy1, CURRENT_ROUND_ADDR_ITA1, FIRST_ROUND_ADDR_ITA1_24, NUM_TEAMS_ITA1, "ita1");
	initLeague(england1, CURRENT_ROUND_ADDR_ENG1, FIRST_ROUND_ADDR_ENG1_24, NUM_TEAMS_ENG1, "eng1");
	initLeague(germany1, CURRENT_ROUND_ADDR_GER1, FIRST_ROUND_ADDR_GER1_24, NUM_TEAMS_GER1, "ger1");
	
	
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
		
		int currentRound, lastRound;
		
		currentRound = findCurrentRound(curl, &s, currentRoundAddr1ITA);
		lastRound = findLastRound("ita1");
		printf("last round %d", lastRound);
		system("pause");
		printf("Current round %d", currentRound);
		processLeague(curl, &s, lastRound, currentRound-1, italy1);
	
		
		currentRound = findCurrentRound(curl, &s, currentRoundAddr1ENG);
		lastRound = findLastRound("eng1");
		processLeague(curl, &s, lastRound, currentRound-1, england1);		

		currentRound = findCurrentRound(curl, &s, currentRoundAddr1GER);
		lastRound = findLastRound("ger1");
		printf("Current round %d", currentRound);
		processLeague(curl, &s, lastRound, currentRound-1, germany1);
		
		
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

#ifdef LEAGUE_INIT_TEST
{
	
	printf("%s\n %s\n %d\n %s\n", england1->currentRoundAddr, england1->firstRoundAddr, england1->numOfTeams, england1->filename);
	system("pause");

	strcpy(england1->teams[1].name, "Brighton and Hove Albion");
	printf("%s", england1->teams[1].name);
	system("pause");
}

#endif
