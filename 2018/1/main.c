#include "util.h"

int main()
{
  UString string;

  util_string_from_file(&string, "list.txt");
  int value = 0;

  int pos_arr[1000] = {0};
  int neg_arr[1000] = {0};
  char line[10] = {0};

  printf("%d\n", util_string_line_count(string));
  for(size_t i = 0; i < util_string_line_count(string); i++)
  {
    util_string_get_line(string, line, 10);
    printf("%d: %s\n", i, line);
    util_string_remove_line(&string);
  }

  return 0;
}
