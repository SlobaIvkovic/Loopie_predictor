#include<stdio.h>
#include<stdlib.h>

#include "../inc/datastructs.h"
#include "../inc/setcurloptions.h"


int setCurlOptions(CURL *curl, chunk* s)
{
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, s);
    
	struct curl_slist *headers = NULL;
    
    curl_easy_setopt(curl, CURLOPT_ACCEPT_ENCODING, "");
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/131.0.0.0 Safari/537.36");
    
    // Set headers
curl_easy_setopt(curl, CURLOPT_CAINFO, "../EXECUTABLE/cacert-2024-11-26.pem");
//    headers = curl_slist_append(headers, "x-requested-with: XMLHttpRequest");
//    headers = curl_slist_append(headers, "sec-ch-ua: \"Google Chrome\";v=\"131\", \"Chromium\";v=\"131\", \"Not_A Brand\";v=\"24\"");
    headers = curl_slist_append(headers, "sec-ch-ua-mobile: ?0");
    headers = curl_slist_append(headers, "sec-ch-ua-platform: \"Windows\"");
//    headers = curl_slist_append(headers, "referer: https://int.soccerway.com/national/germany/bundesliga/20242025/regular-season/r81840/");
    headers = curl_slist_append(headers, "accept: text/javascript, text/html, application/xml, text/xml, */*");
//    headers = curl_slist_append(headers, "accept-encoding: gzip, deflate, br, zstd");

    headers = curl_slist_append(headers, "accept-language: en-US,en;q=0.9");
	headers = curl_slist_append(headers, "accept-language: en-US,en;q=0.9");
    headers = curl_slist_append(headers, "cookie: sw_l10m=int; sw_l10org=RS; _ga=GA1.3.628960041.1732956082; ...");

    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
}

int setCurlOptions1(CURL *curl)
{
	if(curl == NULL)
	{
		printf("ERROR curl handle set to NULL.");
		return 1;
	}

	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
	curl_easy_setopt(curl, CURLOPT_ACCEPT_ENCODING, "");
    
    struct curl_slist *headers = NULL;
	curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/131.0.0.0 Safari/537.36");
    headers = curl_slist_append(headers, "x-requested-with: XMLHttpRequest");
    headers = curl_slist_append(headers, "sec-ch-ua: \"Google Chrome\";v=\"131\", \"Chromium\";v=\"131\", \"Not_A Brand\";v=\"24\"");
    headers = curl_slist_append(headers, "sec-ch-ua-mobile: ?0");
    headers = curl_slist_append(headers, "sec-ch-ua-platform: \"Windows\"");
    headers = curl_slist_append(headers, "referer: https://int.soccerway.com/national/germany/bundesliga/20242025/regular-season/r81840/");
    headers = curl_slist_append(headers, "accept: text/javascript, text/html, application/xml, text/xml, */*");
//    headers = curl_slist_append(headers, "accept-encoding: gzip, deflate, br, zstd");
    headers = curl_slist_append(headers, "accept-language: en-US,en;q=0.9");
    headers = curl_slist_append(headers, "cookie: sw_l10m=int; sw_l10org=RS; _ga=GA1.3.628960041.1732956082; ...");

    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    
    return 0;
}


void init_chunk(chunk *s) {
  s->len = 0;
  s->ptr = malloc(s->len+1);
  if (s->ptr == NULL) {
    fprintf(stderr, "malloc() failed\n");
    exit(EXIT_FAILURE);
  }
  s->ptr[0] = '\0';
}

size_t writefunc(void *ptr, size_t size, size_t nmemb, chunk *s)
{
  size_t new_len = s->len + size*nmemb;
  s->ptr = realloc(s->ptr, new_len+1);
  if (s->ptr == NULL) {
    fprintf(stderr, "realloc() failed\n");
    exit(EXIT_FAILURE);
  }
  memcpy(s->ptr+s->len, ptr, size*nmemb);
  s->ptr[new_len] = '\0';
  s->len = new_len;

  return size*nmemb;
}
