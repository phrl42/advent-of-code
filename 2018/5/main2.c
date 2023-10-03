#include <stdio.h>
#include "util.h"

#define LENGTH 1500
#define SIZE 300

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


int get_id(UString string)
{
  // get id string
  while(string.data[0] != '#')
  {
    string.data++;
  }
  string.data++;
  char id_string[10] = {0};
  int index = 0;
  while(string.data[0] != ' ')
  {
    id_string[index] = string.data[0];
    index += 1;
    string.data++;
  }

  return atoi(id_string);
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
  // go till month
  while(line.data[0] != ' ')
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

  int slept_minutes;

  int start_times[SIZE];
  int start_size;
  
  int end_times[SIZE];
  int end_size;

  int minute[SIZE];
  int count[SIZE];
  int size;
} Guard_default = {0};

typedef struct Guard_s Guard;

void save_count(size_t val, Guard *guard)
{
  size_t size = guard->size;
  for(size_t i = 0; i < size; i++)
  {
    if(guard->minute[i] == val)
    {
      guard->count[i] += 1;
      return;
    }
  }
  guard->count[size] += 1;
  guard->minute[size] = val;
  
  guard->size += 1;
}

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
      if(get_hour(string[i]) < get_hour(string[j]) && i != j && get_month(string[i]) == get_month(string[j]) && get_day(string[i]) == get_day(string[j]))
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
      if(get_minute(string[i]) < get_minute(string[j]) && get_hour(string[i]) == get_hour(string[j]) && i != j && get_month(string[i]) == get_month(string[j]) && get_day(string[i]) == get_day(string[j]))
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
  Guard guards[SIZE] = {Guard_default};
  size_t guard_index = 0;

  int current_guard_index = 0;
  int current_start_value = 0;
  int current_end_value = 0;
  
  for(size_t i = 0; i < line_count; i++)
  {
    if(strstr(string[i].data, "Guard") != NULL)
    {
      int id = get_id(string[i]);
      bool found = false;
      for(size_t j = 0; j < SIZE; j++)
      {
	if(guards[j].id == id)
	{
	  current_guard_index = j;
	  found = true;
	  break;
	}
      }

      if(!found)
      {
	guards[guard_index].id = id;
	current_guard_index = guard_index;
	guard_index += 1;
      }

      current_start_value = 0;
      current_end_value = 0;
      continue;
    }

    if(strstr(string[i].data, "falls") != NULL)
    {
      current_start_value = get_minute(string[i]);
      guards[current_guard_index].start_times[guards[current_guard_index].start_size] = current_start_value;
      guards[current_guard_index].start_size += 1;
      continue;
    }

    if(strstr(string[i].data, "wakes") != NULL)
    {
      current_end_value = get_minute(string[i]);
      guards[current_guard_index].slept_minutes += (current_end_value - current_start_value);
      guards[current_guard_index].end_times[guards[current_guard_index].end_size] = current_end_value;
      guards[current_guard_index].end_size += 1;
      continue;
    }
  }

  for(size_t i = 0; i < SIZE; i++)
  {
    if(guards[i].start_size != guards[i].end_size)
    {
      printf("sorting went wrong\n");
    }
  }

  for(size_t g = 0; g < SIZE; g++)
  {
    int start_size = guards[g].start_size;
    for(size_t i = 0; i < start_size; i++)
    {
      for(size_t s = guards[g].start_times[i]; s < guards[g].end_times[i]; s++)
      {
	save_count(s, &guards[g]);
      }
    }
  }

  int highest_count = 0;
  int index = 0;
  int min = 0;
  for(size_t i = 0; i < SIZE; i++)
  {
    for(size_t j = 0; j < guards[i].size; j++)
    {
      if(guards[i].count[j] > highest_count)
      {
	highest_count = guards[i].count[j];
	index = i;
	min = guards[i].minute[j];
      }
    }
  }

  printf("count: %d\nminute: %d\nid: %d\n", highest_count, min, guards[index].id);

  for(size_t i = 0; i < line_count; i++)
  {
    util_string_free(&string[i]);
  }
  

  return 0;
}
