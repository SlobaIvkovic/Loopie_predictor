#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include<direct.h>
#include<string.h>

#include<curl/curl.h>
#include"../inc/datastructs.h"
#include"../inc/leagueprocessing.h"

#define FOUND 1

int findCurrentRound(CURL *curl, chunk* s, char* addr)
{
	int searchResult;
	int i = 0;
	int j = 0;
	char* buff;
	char round[3];
	
	curl_easy_setopt(curl, CURLOPT_URL, addr);
	curl_easy_perform(curl);
	
	buff = s->ptr;
	
	while((searchResult = findSeq(&buff[i++], "page_dropdown")) != 1 && buff[i] != '\0');
	while((searchResult = findSeq(&buff[i++], "d\">")) != 1 && buff[i] != '\0');
	
	if(searchResult == 1)
	{
		i += 2;
		round[0] = buff[i];
		round[1] = buff[i+1];
		round[2] = '\0';
		
		if(round[1] < 58 && round[1] > 47)
		{
			return round[1] - 48 + (round[0] - 48) * 10;
		}
		else
		{
			return round[0] - 48;
		}
		
		return 0;
	}
	
	printf("Found kurac!! %s\n", round);
	return 1;
}

int findLastRound(char* subdir)
{
	FILE* fp;
	int lr;
	char str[50] = "../DATA/";
//	strcat(str, subdir); 
	// Check the DATA directory existance
	DIR* dir = opendir(str);
	if(dir)
	{
		closedir(dir);
		// Check sub directory existence
		strcat(str, subdir);
		dir = opendir(str);
		if(dir)
		{
			strcat(str, "/stats.lg");
			fp = fopen(str, "r");
			if(fp == NULL)
			{
				printf("Error opening file %s", str);
				return 0;
			}
			
// 	CHECK FILE INTEGRITY HERE IF EVERYTHING OK, LOAD THE TEAMS WITH THE LAST STATS SAVED			
			
			fscanf(fp, "%d", &lr);
			printf("sTIGo %d", lr);
			return lr;
			
			// Read stats here
		}
		else
		{
			_mkdir(str);
			return 0;
		}
		// Placeholder here the file should be used to find the last round
		return 0;
	}
	// Case when DATA dir doesn't exist, create one and create the subdir for the league processed
	else
	{
		_mkdir(str);
		strcat(str, subdir);
		_mkdir(str);
		return 0;
	}
	
	
}
