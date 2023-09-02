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
  Line lines[MAX_LINE_SIZE];
  size_t size;
} FString;

void util_string_init(UString string)
{
  string.size = 0;
  string.data = {0};
}

void util_fstring_init(FString fstring)
{
  fstring.size = 0;

  for(int i = 0; i < MAX_LINE_SIZE; i++)
  {
    fstring.line[i].data = {0};
    fstring.line[i].size = 0;
  }
}

void util_string_replace(const char *text, UString string)
{
  string.size = strlen(text);

  for(int i = 0; i < string.size; i++)
  {
    string.data[i] = text[i];
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

void util_fstring_from_file(FILE *file, FString fstring)
{
  char current_char;
  int line_index = 0;
  int char_index = 0;
  while(current_char = fgetc(file); current_char != EOF)
  {
    if(line_index > MAX_LINE_SIZE)
    {
      // todo:// try the macro trick here
      LOG("line_index > MAX_LINE_SIZE\n");
      return;
    }
    if(char_index > MAX_STRING_SIZE)
    {
      LOG("char_index > MAX_STRING_SIZE\n");
      return;
    }
    
    if(current_char == '\n')
    {
      line_index += 1;
      char_index = 0;
    }
    fstring.line[line_index].data[char_index] = current_char;
    char_index += 1;
  }
  // check if this is right
  fstring.line[line_index].data[char_index] = '\0';
}


#endif
