#include "util.h"

#define LENGTH 200

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


  for(size_t i = 0; i < line_count; i++)
  {
    util_string_print(string[i]);
    util_string_free(&string[i]);
  }


  return 0;
}
