#include <stdio.h>
#include "util.h"

#define LENGTH 1500
#define SIZE 300

void solve(UString *string)
{
  // parse string to specific characters
  bool found_sth = true;
  while(found_sth)
  {
    bool actual_found = false;
    for(size_t i = 0; i < string->size-1; i++)
    {
      char current_char = string->data[i];
      char next_char = string->data[i+1];

      if(toupper(current_char) != toupper(next_char))
      {
	continue;
      }
      
      if(islower(current_char) && isupper(next_char))
      {
	util_string_remove_index(string, i);
	util_string_remove_index(string, i);
	actual_found = true;
      }

      if(isupper(current_char) && islower(next_char))
      {
	util_string_remove_index(string, i);
	util_string_remove_index(string, i);
	actual_found = true;
      }
    }
    found_sth = actual_found;
  }
}

void cut(UString *string, char curr)
{
  // parse string to specific characters
  bool found_sth = true;
  while(found_sth)
  {
    bool actual_found = false;
    for(size_t i = 0; i < string->size; i++)
    {
      char current_char = string->data[i];

      if(curr == toupper(current_char))
      {
	actual_found = true;
	util_string_remove_index(string, i);
      }
    }
    found_sth = actual_found;
  }
}
int main()
{
  UString file_string;
  util_string_from_file(&file_string, "list.txt");

  UString string;
  util_string_from_cstr_size(&string, file_string.data, file_string.size);

  // parse string to specific characters
  int lowest_count = string.size;
  for(char comp = 65; comp <= 90; comp++)
  {
    // first cut the desired characters away
    cut(&string, comp);
    // then solve
    solve(&string);
    //util_string_print(string);

    if(string.size < lowest_count)
    {
      lowest_count = string.size;
    }

    util_string_from_cstr_size(&string, file_string.data, file_string.size);
  }
  
  printf("lowest count: %d\n", lowest_count);
  util_string_free(&string);

  return 0;
}
