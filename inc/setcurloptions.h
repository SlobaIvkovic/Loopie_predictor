#ifndef SETCURLOPTIONS_H
#define SETCURLOPTIONS_H
#include <curl/curl.h>
//#include "datastructs.h"

/*
struct chunk {
  char *ptr;
  size_t len;
};

typedef struct chunk chunk;
*/

int setCurlOptions(CURL *curl, chunk* s);
int setCurlOptions1(CURL *curl);
void init_chunk(chunk *s);
size_t writefunc(void *ptr, size_t size, size_t nmemb, chunk *s);


#endif
