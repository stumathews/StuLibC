#include "libstring.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void upper_case(char *src)
{
        while (*src != '\0') {
                if (islower(*src)) *src &= ~0x20;
                src++;
        }
}



char *rtrim(const char *s)
{
  while( isspace(*s) || !isprint(*s) ) ++s;
  return strdup(s);
}

char *ltrim(const char *s)
{
  char *r = strdup(s);
  if (r != NULL)
  {
    char *fr = r + strlen(s) - 1;
    while( (isspace(*fr) || !isprint(*fr) || *fr == 0) && fr >= r) --fr;
    *++fr = 0;
  }
  return r;
}

char *trim(const char *s)
{
  char *r = rtrim(s);
  char *f = ltrim(r);
  free(r);
  return f;
}

int startsWith(const char* container, const char* target)
{
  size_t clen = strlen(container), tlen = strlen(target);
  if (clen < tlen)
    return 0;
  return strncmp(container, target, tlen) == 0;
}

int endsWith(const char* container, const char* target)
{
  size_t clen = strlen(container), tlen = strlen(target);
  if (clen < tlen)
    return 0;
  return strncmp(container + clen - tlen, target, tlen) == 0;
}

int doesContain(const char* container, const char* target)
{
  return strstr(container, target) != 0;
}

size_t byte_length(char* string)
{
	size_t length = 0;

	  const char *p = string;
	  while (*p++ != '\0') length++;

	  return length;
}

char* concat(const char *s1, const char *s2)
{
  char *s0 = malloc(strlen(s1)+strlen(s2)+1);
  strcpy(s0, s1);
  strcat(s0, s2);
  return s0;
}



