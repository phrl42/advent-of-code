#ifndef _UTIL_H_
#define _UTIL_H_

#include <string.h>
#include <stdio.h>

#define MAX_STRING_SIZE 10000

typedef struct
{
  const char* data;
  size_t size;
} UString;


UString util_string_from_cstr(const char* c_str);
UString util_string_from_file(const char* path_to_file);

void util_string_chop_left(UString *string, size_t n);

void util_string_print(UString string);

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
  string.size = strlen(c_str);
  string.data = c_str;
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


#endif
