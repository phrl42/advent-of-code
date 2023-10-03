#include <stdio.h>
#include "util.h"

#define LENGTH 1500
#define SIZE 300

int main()
{
  UString file_string;
  util_string_from_file(&file_string, "test.txt");

  UString string;

  string = file_string;

  // parse string to specific characters
  bool found_sth = true;
  while(found_sth)
  {
    bool actual_found = false;
    for(size_t i = 0; i < string.size-1; i++)
    {
      char current_char = string.data[i];
      char next_char = string.data[i+1];

      if(toupper(current_char) != toupper(next_char))
      {
	continue;
      }
      
      if(islower(current_char) && isupper(next_char))
      {
	util_string_remove_index(&string, i);
	util_string_remove_index(&string, i);
	actual_found = true;
      }

      if(isupper(current_char) && islower(next_char))
      {
	util_string_remove_index(&string, i);
	util_string_remove_index(&string, i);
	actual_found = true;
      }
    }
    found_sth = actual_found;
  }
  util_string_print(string);
  printf("units: %d\n", string.size);
  util_string_free(&string);

  return 0;
}
