#include <stdio.h>
#include "util.h"

#define LENGTH 1500
#define SIZE 100

void zero(char* ptr, size_t n)
{
  for(size_t i = 0; i < n; i++)
  {
    ptr[i] = '\0';
  }
}

int main()
{

  UString file_string;
  util_string_from_file(&file_string, "list.txt");

  // put file into string arr
  UString string[LENGTH];

  size_t line_count = util_string_line_count(file_string);

  char line[SIZE] = {0};
  
  for(size_t i = 0; i < line_count; i++)
  {
    util_string_get_line(file_string, line, SIZE);
    util_string_from_cstr(&string[i], line);
    util_string_remove_line(&file_string);
  }

  // prepare strings

  for(size_t i = 0; i < line_count; i++)
  {
    while(string[i].data[0] != '@')
    {
      string[i].data++;
    }
    string[i].data += 2;
  }


  // 1000 height and 1000 width

  int space[1000][1000] = {{0}, {0}};

  int x = 0;
  int y = 0;
  
  int w = 0;
  int h = 0;

  for(size_t i = 0; i < line_count; i++)
  {
    // X
    char current_value_string[SIZE] = {0};
    int index = 0;
    // save line properties
    while(string[i].data[0] != ',')
    {
      current_value_string[index] = string[i].data[0];

      index += 1;

      string[i].data++;
    }
    x = atoi(current_value_string);
    // Y

    string[i].data++;

    zero(current_value_string, index+1);

    index = 0;
    while(string[i].data[0] != ':')
    {
      current_value_string[index] = string[i].data[0];
      index += 1;
      string[i].data++;
    }
    y = atoi(current_value_string);

    // w
    string[i].data += 2;

    zero(current_value_string, index+1);
    index = 0;
    
    while(string[i].data[0] != 'x')
    {
      current_value_string[index] = string[i].data[0];
      index += 1;
      string[i].data++;
    }

    w = atoi(current_value_string);

    // h
    string[i].data++;
    zero(current_value_string, index+1);
    index = 0;
    while(string[i].data[0] != 0)
    {
      current_value_string[index] = string[i].data[0];
      index += 1;
      string[i].data++;
    }

    h = atoi(current_value_string);


    printf("[%d] X: %d | Y: %d | W: %d | H: %d\n", i, x, y, w, h);
  }

  
  for(size_t i = 0; i < line_count; i++)
  {
    util_string_free(&string[i]);
  }
  

  return 0;
}
