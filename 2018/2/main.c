#include "util.h"

#define LENGTH 100

bool array_contains(char *arr, size_t size, char comp)
{
  for(size_t i = 0; i < size; i++)
  {
    if(arr[i] == comp)
    {
      return true;
    }
  }
  return false;
}

int main()
{
  UString string;

  util_string_from_file(&string, "list.txt");

  char unique[LENGTH] = {0};
  int unique_index = 0;
  
  char line[LENGTH] = {0};

  for(size_t i = 0; i < util_string_line_count(string); i++)
  {
    util_string_get_line(string, line, LENGTH);

    for(size_t j = 0; j < util_string_line_char_count(string); j++)
    {
      if(!array_contains(unique, LENGTH, line[j]))
      {
	unique[unique_index] = line[j];
	unique_index += 1;
      }
    }
    util_string_remove_line(&string);
  }

  int count_two = 0;
  int count_three = 0;
  
  for(size_t i = 0; i < util_string_line_count(string); i++)
  {
    util_string_get_line(string, line, LENGTH);

    for(size_t j = 0; j < util_string_line_char_count(string); j++)
    {
      
    }
    util_string_remove_line(&string);
  }

  printf("%s\n", unique);
  return 0;
}
