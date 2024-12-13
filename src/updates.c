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
	
//	printf("%s", s->ptr);
	
	buff = s->ptr;
//	printf("%s", buff);
//	char buff1[50];
//	strcpy(buff1, "page_dropdown");
	
	
	while((searchResult = findSeq(&buff[i++], "page_dropdown")) != 1 && buff[i] != '\0');
	while((searchResult = findSeq(&buff[i++], "d\">")) != 1 && buff[i] != '\0');
	
	if(searchResult == 1)
	{
		i += 2;
		while(buff[i] != ' ')
		{
			round[j++] = buff[i++];
		}
		round[j] = '\0';
		
		
		if(j == 1)
		{
			return round[0] - 48;
		}
		else
		{
			return round[1] - 48 + (round[0] - 48) * 10;
		}
		
		return 0;
	}
	
	printf("Found kurac!! %s\n", round);
	return 1;
}

int findLastRound(char* subdir)
{
	char str[30] = "../DATA/";
	strcat(str, subdir); 
	// Check the directory existance
	DIR* dir = opendir(str);
	if(dir)
	{
		closedir(dir);
		// Placeholder here the file should be used to find the last round
	}
	// if doesnt exist create one return 0
	else
	{
		_mkdir(str);
		return 0;
	}
	
	
}
