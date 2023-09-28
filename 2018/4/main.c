#include <stdio.h>
#include "util.h"

#define LENGTH 1500
#define SIZE 100

void zero(char* ptr, size_t n)
{
  for(size_t i = 0; i < n; i++)
  {
    ptr[i] = '\0';
  }
}

size_t get_month(UString line)
{
  char current_value[3] = {0};
  // skip year
  while(line.data[0] != '-')
  {
    line.data++;
  }
  line.data++;

  current_value[0] = line.data[0];
  current_value[1] = line.data[1];

  return (size_t)atoi(current_value);
 
}

size_t get_day(UString line)
{
  char current_value[3] = {0};
  // skip year
  while(line.data[0] != '-')
  {
    line.data++;
  }
  line.data++;
    
  // skip day
  while(line.data[0] != '-')
  {
    line.data++;
  }
  line.data++;

  current_value[0] = line.data[0];
  current_value[1] = line.data[1];

  return (size_t)atoi(current_value);

}

size_t get_hour(UString line)
{
  char current_value[3] = {0};
  // skip year
  while(line.data[0] != '-')
  {
    line.data++;
  }
  line.data++;
    
  // skip day
  while(line.data[0] != '-')
  {
    line.data++;
  }
  line.data++;

  current_value[0] = line.data[0];
  current_value[1] = line.data[1];

  return (size_t)atoi(current_value);

}


size_t get_minute(UString line)
{
  char current_value[3] = {0};
  // skip year
  while(line.data[0] != '-')
  {
    line.data++;
  }
  line.data++;
    
  // skip day
  while(line.data[0] != '-')
  {
    line.data++;
  }
  line.data++;

  // skip hour
  while(line.data[0] != ':')
  {
    line.data++;
  }
  line.data++;

  current_value[0] = line.data[0];
  current_value[1] = line.data[1];

  return (size_t)atoi(current_value);

}

struct Guard_s
{
  int id;
  
  int sleep_start;
  int sleep_end;
} Guard_default = {0};

typedef struct Guard_s Guard;

int main()
{

  UString file_string;
  util_string_from_file(&file_string, "list.txt");

  // put file into string arr
  UString string[LENGTH];

  size_t line_count = util_string_line_count(file_string);

  char line[SIZE] = {0};

  // init string
  for(size_t i = 0; i < line_count; i++)
  {
    util_string_get_line(file_string, line, SIZE);
    util_string_from_cstr(&string[i], line);

    util_string_remove_line(&file_string);
  }


  for(size_t i = 0; i < line_count; i++)
  {
    for(size_t j = 0; j < line_count; j++)
    {
      UString temp = string[i];
      if(get_month(string[i]) < get_month(string[j]) && i != j)
      {
	string[i] = string[j];
	string[j] = temp;
      }
    }
  }

  for(size_t i = 0; i < line_count; i++)
  {
    for(size_t j = 0; j < line_count; j++)
    {
      UString temp = string[i];
      if(get_day(string[i]) < get_day(string[j]) && i != j && get_month(string[i]) == get_month(string[j]))
      {
	string[i] = string[j];
	string[j] = temp;
      }
    }
  }

   for(size_t i = 0; i < line_count; i++)
  {
    for(size_t j = 0; j < line_count; j++)
    {
      UString temp = string[i];
      if(get_minute(string[i]) < get_minute(string[j]) && i != j && get_month(string[i]) == get_month(string[j]) && get_day(string[i]) == get_day(string[j]))
      {
	string[i] = string[j];
	string[j] = temp;
      }
    }
  }

     for(size_t i = 0; i < line_count; i++)
  {
    for(size_t j = 0; j < line_count; j++)
    {
      UString temp = string[i];
      if(get_hour(string[i]) > get_hour(string[j]) && get_minute(string[i]) < get_minute(string[j]) && i != j && get_month(string[i]) == get_month(string[j]) && get_day(string[i]) == get_day(string[j]))
      {
	string[i] = string[j];
	string[j] = temp;
      }
    }
  }

 
 
  for(size_t i = 0; i < line_count; i++)
  {
    util_string_print(string[i]);
  }
  
  Guard guards[300] = {Guard_default};

  size_t guard_count = 0;

  for(size_t i = 0; i < line_count; i++)
  {
    if(strstr(string[i].data, "Guard") != NULL)
    {
      guard_count += 1;
    }
  }

  for(size_t i = 0; i < line_count; i++)
  {
    util_string_free(&string[i]);
  }
  

  return 0;
}
