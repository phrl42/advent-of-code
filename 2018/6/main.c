#include <stdio.h>
#include "util.h"

#define LENGTH 1500
#define SIZE 500
#define TMP 10
void get_x(UString string, int *x)
{

  char number_string[TMP] = {0};
  int index = 0;
  while(string.data[0] != ',')
  {
    number_string[index] = string.data[0];
    string.data++;
    index += 1;
  }
  *x = atoi(number_string);
}

void get_y(UString string, int *y)
{
  char number_string[TMP] = {0};
  int index = 0;
  while(string.data[0] != ' ')
  {
    string.data++;
  }
  *y = atoi(string.data); 
}

int main()
{
  UString file_string;
  util_string_from_file(&file_string, "list.txt");
  // put file into string arr
  UString string[LENGTH];

  size_t line_count = util_string_line_count(file_string);

  util_string_separate_by_line(file_string, string, line_count);
  
  int x[SIZE] = {0};
  int y[SIZE] = {0};

  for(size_t i = 0; i < line_count; i++)
  {
    get_x(string[i], &x[i]);
    get_y(string[i], &y[i]);
    //util_string_print(string[i]);
  }

  
  for(size_t i = 0; i < line_count; i++)
  {
    util_string_free(&string[i]);
  }
  util_string_free(&file_string);

  return 0;
}
