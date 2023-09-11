#ifndef _UTIL_H_
#define _UTIL_H_

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_STRING_SIZE 10000

void util_assert(bool condition, const char *msg)
{
  if(condition)
  {
    printf("%s\n", msg);
    exit(-1);
  }
}

typedef struct
{
  char* data;
  size_t size;
} UString;

void util_string_print(UString string)
{
  for(size_t i = 0; i < string.size; i++)
  {
    printf("%c", string.data[i]);
  }
  printf("\n");
}

void util_string_from_cstr(UString *string, const char* c_str)
{
  size_t size = strlen(c_str);
  
  string->data = malloc(sizeof(char) * size);
  string->size = strlen(c_str);

  for(int i = 0; i < size; i++)
  {
    string->data[i] = c_str[i];
  }
}

void util_string_from_cstr_size(UString *string, const char* c_str, size_t n)
{
  string->size = n;
  string->data = malloc(sizeof(char) * n);

  util_assert(strlen(c_str) < n, "c_str < n");
  
  for(int i = 0; i < n; i++)
  {
    string->data[i] = c_str[i];
  }
}

// temporary solution
#define MAX_FILE_SIZE 10000

void util_string_from_file(UString *string, const char* path)
{
  FILE *file = fopen(path, "r");
  util_assert(file == NULL, "Could not find file");

  string->data = malloc(sizeof(char) * MAX_FILE_SIZE);
  int current_char = 0;
  int i = 0;
  while(current_char != EOF)
  {
    current_char = fgetc(file);
    string->data[i] = current_char;
    i++;
  }
  string->size = i-1;

  fclose(file);
}


void util_string_free(UString *string)
{
  free(string->data);
}

#endif
