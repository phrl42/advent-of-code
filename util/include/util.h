#ifndef _UTIL_H_
#define _UTIL_H_

#include <string.h>
#include <stdio.h>

#define LOG(x) printf(x)

// because I want my programs to be memory-safe
#define MAX_STRING_SIZE 10000
#define MAX_LINE_SIZE 10000

typedef struct
{
  char data[MAX_STRING_SIZE];
  size_t size;
} UString;

typedef struct
{
  char data[MAX_STRING_SIZE];
  size_t size;
} Line;

typedef struct
{
  Line line[MAX_LINE_SIZE];
  size_t size;
} FString;

void util_string_init(UString *string)
{
  memset(string->data, 0, MAX_STRING_SIZE);
  string->size = 1;
}

void util_fstring_init(FString *fstring)
{
  fstring->size = 0;

  for(int i = 0; i < MAX_LINE_SIZE; i++)
  {
    memset(fstring->line[i].data, 0, MAX_STRING_SIZE);
    fstring->line[i].size = 1;
  }
}

void util_string_replace(const char *text, UString *string)
{
  string->size = strlen(text);

  for(int i = 0; i < string->size; i++)
  {
    string->data[i] = text[i];
  }
}

void util_string_copy(char* dest, UString string, size_t count)
{
  if(count > string.size)
  {
    LOG("count > string.size\n");
    return;
  }

  if(count > strlen(dest))
  {
    LOG("count > strlen(dest)\n");
    return;
  }
  
  for(int i = 0; i < count; i++)
  {
    dest[i] = string.data[i];
  }
}

void util_fstring_from_file(FILE *file, FString *fstring)
{
  char current_char = 0;
  int line_index = 0;
  int char_index = 0;
  while(current_char != EOF)
  {
    if(line_index > MAX_LINE_SIZE)
    {
      LOG("line_index > MAX_LINE_SIZE\n");
      return;
    }
    if(char_index > MAX_STRING_SIZE)
    {
      LOG("char_index > MAX_STRING_SIZE\n");
      return;
    }

    current_char = fgetc(file);

    fstring->line[line_index].data[char_index] = current_char;
    char_index += 1;
    
    if(current_char == '\n')
    {
      fstring->line[line_index].size = char_index + 1;
      line_index += 1;
      char_index = 0;
    }
  }
  fstring->size = line_index + 1;
}

#endif
