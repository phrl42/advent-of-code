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
  UString file_string;

  util_string_from_file(&file_string, "list.txt");


  UString string = file_string;
  char unique[LENGTH] = {0};
  int unique_index = 0;
  
  char line[LENGTH] = {0};
  int line_count = util_string_line_count(string);
  for(size_t i = 0; i < line_count; i++)
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

  string = file_string;
  
  printf("%s\n", unique);
  line_count = util_string_line_count(string);
  
  for(size_t i = 0; i < line_count; i++)
  {
    bool two_done = false;
    bool three_done = false;
    util_string_get_line(string, line, LENGTH);
    printf("%s\n", line);
    for(size_t u = 0; u < unique_index; u++)
    {
      int count = 0;
      int char_count = util_string_line_char_count(string);
      for(size_t j = 0; j < char_count; j++)
      {
	if(line[j] == unique[u])
	{
	  count += 1;
	}
      }
      if(count == 2 && !two_done)
      {
	two_done = true;
	printf("granted two in line %d\n", i);
	count_two += 1;
      }
      if(count == 3 && !three_done)
      {
	three_done = true;
	printf("granted three in line %d\n", i);
	count_three += 1;
      }
    }
    
    
    util_string_remove_line(&string);
  }

  printf("%d * %d = %d\n", count_two, count_three, count_two * count_three);
  return 0;
}
