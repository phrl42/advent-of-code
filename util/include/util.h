#ifndef _UTIL_H_
#define _UTIL_H_

#include <string.h>
#include <stdio.h>

#define LOG(x) printf(x)

typedef struct
{
  char *data;
  size_t size;
} UString;

void util_string_replace(const char *text, UString string)
{
  string.data = (char*)text;
  string.size = strlen(text);
}

void util_string_copy(char* dest, UString string, size_t count)
{
  if(count > string.size)
  {
    LOG("count > string.size");
    return;
  }

  if(count > strlen(dest))
  {
    LOG("count > strlen(dest)");
    return;
  }
  
  for(int i = 0; i < count; i++)
  {
    dest[i] = string.data[i];
  }
}


#endif
