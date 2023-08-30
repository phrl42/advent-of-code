#include <stdio.h>
#include <string.h>
#include <stdint.h>
#define ARR_LENGTH 15000

FILE *file;

int8_t array_has_dup(char* arr, size_t count, char dup_char)
{
  for(int i = 0; i < count; i++)
  {
    if(arr[i] == dup_char)
    {
      return 42;
    }
  }
  return 0;
}

int main()
{
  file = fopen("list.txt", "r");
  
  int filecontents_size = 0;

  char filecontents[ARR_LENGTH];
  memset(filecontents, 0, ARR_LENGTH);
  
  for(int i = 0; i < ARR_LENGTH; i++)
  {
    filecontents[i] = fgetc(file);
    if(filecontents[i] == EOF)
    {
      filecontents[i] = '\0';
      filecontents_size = i;
      break;
    }
    printf("%c", filecontents[i]);
  }

  char unique_chars[filecontents_size];
  int unique_chars_count = 0;

  memset(unique_chars, 0, filecontents_size);

  for(int i = 0; i < filecontents_size; i++)
  {
    if(filecontents[i] == '\n')
    {
      continue;
    }

    if(!array_has_dup(unique_chars, filecontents_size, filecontents[i]))
    {
      unique_chars[unique_chars_count] = filecontents[i];
      unique_chars_count += 1;
    }
  }
  
  int count_twice = 0;
  int count_thrice = 0;
  int pos = 0;
  int check_pos = 0;
  while(check_pos < filecontents_size)
  {
    int8_t twice_found = 0;
    int8_t thrice_found = 0;
    for(int c = 0; c < unique_chars_count; c++)
    {
      int dup_count = 0;
      for(int f = pos; f < filecontents_size; f++)
      {
        if(filecontents[f] == '\n')
        {
          break;
        }

        if(unique_chars[c] == filecontents[f])
        {
          dup_count += 1;
        }
      }
      if(dup_count == 2 && !twice_found)
      {
        twice_found = 1;
        count_twice += 1;
      }
      if(dup_count == 3 && !thrice_found)
      {
        thrice_found = 1;
        count_thrice += 1;
      }
    }

    for(int i = pos; i <= filecontents_size; i++)
    {
      if(filecontents[i] == '\n')
      {
        filecontents[i] = 0;
        pos = i + 1;
        break;
      }
      else
      {
        filecontents[i] = 0;
      }
      check_pos += 1;
    }
  }

  printf("%d * %d = %d\n", count_twice, count_thrice, count_twice * count_thrice);

  return 0;
}
