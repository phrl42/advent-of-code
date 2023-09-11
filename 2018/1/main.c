#include "util.h"

int main()
{
  UString string;

  util_string_from_file(&string, "list.txt");

  int value = 0;

  int pos_arr[1000] = {0};
  int neg_arr[1000] = {0};

  for(int i = 0; i < util_string_line_count(string); i++)
  {
    char line[1000] = {0};
    util_string_get_line(string, line, 1000);
    printf("%s", line);
  }

  printf("%d\n", value);

  return 0;
}
