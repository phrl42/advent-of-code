#include "util.h"

int main()
{
  UString string;

  util_string_from_file(&string, "list.txt");
  int value = 0;

  int log[10000] = {0};
  char line[10] = {0};

  int length = util_string_line_count(string);
  for(int i = 0; i <= length; i++)
  {
    util_string_get_line(string, line, 10);
    if(line[0] == '+')
    {
      char *data = line;
      data++;
      value += atoi(line);
    }
    else if(line[0] == '-')
    {
      char *data = line;
      data++;
      value -= atoi(data);
    }
    else
    {
      printf("no prefix found\n");
    }
    
    log[i] = value;

    util_string_remove_line(&string);
  }
  int count = 0;
  for(int j = 0; j <= length; j++)
  {
    for(int h = 0; h <= length; h++)
    {
      if(log[j] == log[h] && h != j)
      {
	count += 1;
      }
      if(count == 2)
      {
	printf("found value twice: %d\n", log[h]);
	return 0;
      }
    }
  }

  return 0;
}
