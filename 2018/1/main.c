#include "util.h"

int main()
{
  UString string;

  util_string_from_file(&string, "list.txt");
  int value = 0;

  int log[10000] = {0};
  char line[10] = {0};

  int length = util_string_line_count(string);

  bool found = false;
  int stat = 0;
  while(!found)
  {
    stat += 1;
    string.data = string.data_bak;
    printf("iteration: %d\n", stat);
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
      for(int j = 0; j <= i; j++)
      {
	for(int h = 0; h <= i; h++)
	{
	  if(log[j] == log[h] && h != j)
	  {
	    printf("found value twice: %d\n", log[h]);
	    found = true;
	  }
	}
      }
      util_string_remove_line(&string);
    }
  }
  return 0;
}
