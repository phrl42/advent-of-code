#include <stdio.h>
#include "util.h"

#define LENGTH 1500
#define SIZE 300

int main()
{
  UString file_string;
  util_string_from_file(&file_string, "list.txt");

  UString string;

  string = file_string;

  // parse string to specific characters

  

  util_string_free(&string);

  return 0;
}
