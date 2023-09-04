#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "util.h"

int8_t array_has_dupe(const char* arr, size_t n, char check)
{
  for(int i = 0; i < n; ++i)
  {
    if(arr[i] == check)
    {
      return 1;
    }
  }
  return 0;
}

UString find_unique_chars(UString string)
{
  char uniques[100] = {0};
  int unique_index = 0;
  
  for(int i = 0; i < string.size; i++)
  {
    if(string.data[i] == '\n' || string.data[i] == ' ') continue;

    if(!array_has_dupe(uniques, 100, string.data[i]))
    {
      uniques[unique_index] = string.data[i];
      unique_index += 1;
    }
  }

  printf("manual printing: \n");
  for(int i = 0; i <= unique_index; i++)
  {
    printf("%c", uniques[i]);
  }
  printf("\n");

  UString ustring = util_string_from_cstr(uniques);

  return ustring;
}


int main()
{
  UString string = util_string_from_file("test.txt");

  UString uniques = find_unique_chars(string);

  util_string_print(uniques);

  
  return 0;
}
