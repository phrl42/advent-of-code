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

UString util_string_from_cstr(const char* c_str);
UString util_string_from_cstr_size(const char* c_str, size_t n);
UString util_string_from_file(const char* path_to_file);

void util_string_chop_left(UString *string, size_t n);

void util_string_print(UString string);

void util_string_free(UString *string);

void util_string_print(UString string)
{
  for(size_t i = 0; i < string.size; i++)
  {
    printf("%c", string.data[i]);
  }
  printf("\n");
}

UString util_string_from_cstr(const char* c_str)
{
  UString string;

  string.data = malloc(sizeof(char) * strlen(c_str));
  string.size = strlen(c_str);
  
  return string;
}

UString util_string_from_cstr_size(const char* c_str, size_t n)
{
  UString string;
  bool null_terminator = false;
 
  string.size = n;
  string.data = malloc(sizeof(char) * (n+1));

  util_assert(strlen(c_str) < n, "c_str < n");
  
  for(int i = 0; i < n; i++)
  {
    string.data[i] = c_str[i];
  }

  string.data[n] = '\0'; 
  
  return string;
}

UString util_string_from_file(const char* path_to_file)
{
  FILE *file = fopen(path_to_file, "r");

  char file_string[MAX_STRING_SIZE] = {0};
  int file_string_index = 0;
    
  int current_char = 0;
  while((current_char = fgetc(file)) != EOF)
  {
    if(file_string_index >= MAX_STRING_SIZE)
    {
      printf("File size bigger than MAX_STRING_SIZE. Stopping now");
      break;
    }
    file_string[file_string_index] = current_char;
    file_string_index += 1;
  }
  file_string[file_string_index - 1] = '\0';
  UString string = util_string_from_cstr(file_string);
  
  return string;
}

void util_string_chop_left(UString *string, size_t n)
{
  string->size -= n;
  string->data += n;
}

void util_string_free(UString *string)
{
  free(string);
}

#endif
