#include <stdio.h>
#include "util.h"

#define LENGTH 1500
#define SIZE 300

int main()
{
  UString file_string;
  util_string_from_file(&file_string, "list.txt");
  // put file into string arr
  UString string[LENGTH];

  size_t line_count = util_string_line_count(file_string);

  util_string_separate_by_line(file_string, string, line_count);
  
  for(size_t i = 0; i < line_count; i++)
  {
    util_string_print(string[i]);
  }

  for(size_t i = 0; i < line_count; i++)
  {
    util_string_free(&string[i]);
  }
  util_string_free(&file_string);

  return 0;
}
