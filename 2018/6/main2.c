#include <stdio.h>
#include "util.h"

#define LENGTH 1500
#define SIZE 300

int main()
{
  UString file_string;
  util_string_from_file(&file_string, "list.txt");
  
  util_string_free(&file_string);

  return 0;
}
