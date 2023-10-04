#ifndef _UTIL_H_
#define _UTIL_H_

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_STRING_SIZE 10000

typedef struct
{
  char* data_bak;
  char* data;
  size_t size;
} UString;

// random functions
void util_string_print(UString string);
size_t util_string_line_count(UString string);
size_t util_string_line_char_count(UString string);
void util_string_save_to_file(UString string, const char* file_name);

// init functions
void util_string_from_cstr(UString* string, const char* c_str);
void util_string_from_cstr_size(UString* string, const char* c_str, size_t n);
void util_string_from_file(UString* string, const char* path);

// edit functions
void util_string_remove_line(UString *string);
void util_string_get_line(UString string, char *dest, size_t n);
void util_string_remove_index(UString *string, size_t index);

// deinit functions
void util_string_free(UString *string);

void util_assert(bool condition, const char *msg)
{
  if(condition)
  {
    printf("%s\n", msg);
    exit(-1);
  }
}

void util_string_print(UString string)
{
  for(size_t i = 0; i < string.size; i++)
  {
    printf("%c", string.data[i]);
  }
  printf("\n");
}

void util_string_save_to_file(UString string, const char* file_name)
{
  FILE *file;
  file = fopen(file_name, "w");

  fprintf(file, "%s\n", string.data);
  fclose(file);
}

size_t util_string_line_count(UString string)
{
  size_t count = 1;

  for(size_t i = 0; i < string.size; i++)
  {
    if(string.data[i] == '\n')
    {
      count += 1;
    }
  }

  return count;
}
/*
void util_string_remove_index(UString *string, size_t index)
{
  string->data[index] = ' ';
  string->size -= 1; 
  // move everything to the left
  for(size_t i = index; i < string->size; i++)
  {
    string->data[i] = string->data[i+1];
  }
  char *new_location = malloc(sizeof(char) * string->size);
  memmove(new_location, string->data, sizeof(char) * string->size);
 
  free(string->data_bak);
  string->data = new_location;
  string->data_bak = new_location;
}
*/
void util_string_remove_index(UString *string, size_t index)
{
  string->data[index] = ' ';
  string->size -= 1; 
  // move everything to the left
  for(size_t i = index; i < string->size; i++)
  {
    string->data[i] = string->data[i+1];
  }
  string->data[string->size] = '\0';
}

size_t util_string_line_char_count(UString string)
{
  size_t count = 1;

  while(string.data[count] != '\n')
  {
    count += 1;
    util_assert(count >= string.size, "no line found");
  }

  return count;
}


void util_string_remove_line(UString *string)
{
  // also skip newline
  size_t length = util_string_line_char_count(*string) + 1;
  for(size_t i = 0; i < length; i++)
  {
    string->data++;
  }
}
void util_string_get_line(UString string, char *dest, size_t n)
{
  size_t length = util_string_line_char_count(string);
  util_assert(string.size < length, "no line found");
  util_assert(n < length, "destination < line");

  for(size_t i = 0; i < length; i++)
  {
    dest[i] = string.data[i];
  }
  dest[length] = '\0';
}

void util_string_from_cstr(UString *string, const char* c_str)
{
  size_t size = strlen(c_str)+1;
  
  string->data = malloc(sizeof(char) * size);
  string->size = size-1;

  string->data_bak = string->data;

  for(int i = 0; i < size; i++)
  {
    string->data[i] = c_str[i];
  }
}

// init functions
void util_string_from_cstr_size(UString *string, const char* c_str, size_t n)
{
  string->size = n;
  string->data = malloc(sizeof(char) * n);
  string->data_bak = string->data;
  
  util_assert(strlen(c_str) < n, "c_str < n");
  
  for(int i = 0; i < n; i++)
  {
    string->data[i] = c_str[i];
  }
}

// temporary solution
#define MAX_FILE_SIZE 50000

void util_string_from_file(UString *string, const char* path)
{
  FILE *file = fopen(path, "r");
  util_assert(file == NULL, "Could not find file");

  string->data = malloc(sizeof(char) * MAX_FILE_SIZE);
  string->data_bak = string->data;

  int current_char = fgetc(file);
  int i = 0;
  while(current_char != EOF)
  {
    string->data[i] = current_char;
    current_char = fgetc(file);
    i++;
  }
  string->size = i-1;

  fclose(file);
}


void util_string_free(UString *string)
{
  free(string->data_bak);
}

#endif
