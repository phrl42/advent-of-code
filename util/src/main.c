#include "util.h"

int main()
{
  UString string;

  util_string_from_file(&string, "test");

  util_string_print(string);

  util_string_free(&string);
  return 0;
}
