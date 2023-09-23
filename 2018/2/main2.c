#include "util.h"

#define LENGTH 400

int main()
{
  UString file_string;

  util_string_from_file(&file_string, "list.txt");

  UString string_tmp = file_string;

  UString string[LENGTH];
  
  int line_count = util_string_line_count(string_tmp);

  char line[LENGTH] = {0};
  for(size_t i = 0; i < line_count; i++)
  {
    util_string_get_line(string_tmp, line, LENGTH);
    util_string_from_cstr(&string[i], line);
    util_string_remove_line(&string_tmp);
  }

  int highest_match = 0;
  int highest_match_index[2] = {0};
  
  for(size_t i = 0; i < line_count; i++)
  {
    for(size_t h = 0; h < line_count; h++)
    {
      int match = 0;
      for(size_t j = 0; j < string[i].size; j++)
      {
	if(string[i].data[j] == string[h].data[j] && h != i)
	{
	  match += 1;
	}
      }
      if(match > highest_match)
      {
	highest_match = match;
	highest_match_index[0] = i;
	highest_match_index[1] = h;
      }
    }
  }

  char final_string[LENGTH] = {0};
  int str_index = 0;
  for(size_t i = 0; i < string[highest_match_index[0]].size; i++)
  {
    if(string[highest_match_index[0]].data[i] == string[highest_match_index[1]].data[i])
    {
      final_string[str_index] = string[highest_match_index[0]].data[i];
      str_index += 1;
    }
  }

  printf("%d and %d\n", highest_match_index[0], highest_match_index[1]);
  
  util_string_print(string[highest_match_index[0]]);
  util_string_print(string[highest_match_index[1]]);
  
  for(size_t i = 0; i < line_count; i++)
  {
    util_string_free(&string[i]);
  }

  printf("%s\n", final_string);  

  return 0;
}
