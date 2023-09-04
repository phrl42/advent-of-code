#include "util.h"

UString string;

int main()
{
  string = util_string_from_file("bad.txt");

  util_string_print(string);
  return 0;
}
