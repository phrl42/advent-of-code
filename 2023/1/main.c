#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "util.h"

#define LENGTH 1500
#define SIZE 100

void replace_numbers(UString *string, uint8_t size, const char* pos, char val)
{
  size_t start = pos - string->data;

  char arr[LENGTH] = {0};

  size_t original_index = 0;
  for(size_t i = 0; i < string->size+1;i++)
  {
    if(i == start)
    {
      arr[i] = val;
      continue;
    }
    arr[i] = string->data[original_index];

    original_index++;
  }

  util_string_free(string);
  util_string_from_cstr_size(string, arr, string->size+1);
}

void place_numbers(UString *string)
{
  for(uint8_t i = 1; i <= 9; i++)
  {
    const char* p;
    int size = 0;
    char val = '-';
    
    switch(i)
    {
    case 1:
      p = strstr(string->data, "one");
      val = '1';
      size = 3;
      break;

    case 2:
      p = strstr(string->data, "two");
      val = '2';
      size = 3;
      break;

    case 3:
      p = strstr(string->data, "three");
      val = '3';
      size = 4;  
      break;

    case 4:
      p = strstr(string->data, "four");
      val = '4';
      size = 4;
      break;

    case 5:
      p = strstr(string->data, "five");
      val = '5';
      size = 4;
      break;

    case 6:
      p = strstr(string->data, "six");
      val = '6';
      size = 3;
      break;

    case 7:
      p = strstr(string->data, "seven");
      val = '7';
      size = 5;
      break;
    case 8:
      p = strstr(string->data, "eight");
      val = '8';
      size = 5;
      break;

    case 9:
      p = strstr(string->data, "nine");
      val = '9';
      size = 4;
      break;

    default:
      printf("I think something went wrong\n");
      break;
    }
    
    if(p == NULL)
    {
      continue;
    }

    replace_numbers(string, size, p, val);
  }
}


int main()
{
  UString file_string;
  util_string_from_file(&file_string, "test2.txt");

  // put file into string arr
  UString string[LENGTH];

  size_t line_count = util_string_line_count(file_string);

  char line[SIZE] = {0};
  
  for(size_t i = 0; i < line_count; i++)
  {
    util_string_get_line(file_string, line, SIZE);
    util_string_from_cstr(&string[i], line);
    util_string_remove_line(&file_string);
  }

  // prepare strings
  int result = 0;
  
  for(size_t i = 0; i < line_count; i++)
  {
    char tkey[100] = {0};
    int tkey_index = 0;

    place_numbers(&string[i]);

    printf("%s\n", string[i].data);
    for(size_t l = 0; l < string[i].size; l++)
    {
      if(isdigit(string[i].data[l]))
      {
	tkey[tkey_index] = string[i].data[l];
	tkey_index++;
      }
    }
    char number[10] = {0};
    int number_index = 0;

    number[0] = tkey[0];
    number[1] = tkey[tkey_index-1];

    printf("number: %s\n", number);
    result += atoi(number);
  }

  printf("%d\n", result);
  
  for(size_t i = 0; i < line_count; i++)
  {
    util_string_free(&string[i]);
  }
  

  return 0;
}
