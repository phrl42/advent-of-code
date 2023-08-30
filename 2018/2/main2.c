#include <stdio.h>
#include <string.h>
#include <stdint.h>
#define ARR_LENGTH 15000
#define LINES 1000

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

typedef struct 
{
  char content[100];
  int char_index;
} Line;


int check_for_occurences(Line line_one, Line line_two)
{
  int occurences = 0;
  for(int i = 0; i <= line_one.char_index; i++)
  {
    for(int j = 0; j <= line_two.char_index; j++)
    {
      if(line_one.content[i] == line_two.content[j])
      {
        occurences += 1;
      }
    }
  }
  return occurences;
}

int main()
{
  file = fopen("list.txt", "r");
  
  int filecontents_size = 0;

  char filecontents[ARR_LENGTH];
  memset(filecontents, 0, ARR_LENGTH);
 
  Line lines[LINES];
  int lines_index = 0;

  // init line structs
  for(int i = 0; i < LINES; i++)
  {
    lines[i].char_index = 0;
    memset(lines[i].content, 0, sizeof(char) * 100);
  }

  for(int i = 0; i < ARR_LENGTH; i++)
  {
    filecontents[i] = fgetc(file);
    if(filecontents[i] == EOF)
    {
      filecontents[i] = '\0';
      filecontents_size = i;
      break;
    }
  }

  char unique_chars[filecontents_size];
  int unique_chars_count = 0;

  memset(unique_chars, 0, filecontents_size);

  for(int i = 0; i < filecontents_size; i++)
  {
    lines[lines_index].content[lines[lines_index].char_index] = filecontents[i];
    lines[lines_index].char_index += 1;

    if(filecontents[i] == '\n')
    {
      lines_index += 1;
      continue;
    }

    if(!array_has_dup(unique_chars, filecontents_size, filecontents[i]))
    {
      unique_chars[unique_chars_count] = filecontents[i];
      unique_chars_count += 1;
    }
  }

  /*int count_twice = 0;
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
  }*/

  int occurence_count = 0;
  int most_occurence_line_index[2] = {0, 0};
  for(int i = 0; i <= lines_index; i++)
  {
    for(int j = 0; j <= lines_index; j++)
    {
      int temp_val = check_for_occurences(lines[i], lines[j]);
      if(temp_val >= occurence_count && i != j)
      {
        occurence_count = temp_val;
        printf("line %d and %d with %d\n", i, j, occurence_count);
        most_occurence_line_index[0] = i;
        most_occurence_line_index[1] = j;
      }
    }
  }
  printf("%d and %d\n", most_occurence_line_index[0], most_occurence_line_index[1]);
  
  char sol_string[50];
  int sol_string_index = 0;
  memset(sol_string, 0, sizeof(char) * 50);

  for(int i = 0; i <= lines[most_occurence_line_index[0]].char_index; i++)
  {
    printf("%c", lines[most_occurence_line_index[0]].content[i]);
  }
  for(int i = 0; i <= lines[most_occurence_line_index[1]].char_index; i++)
  {
    printf("%c", lines[most_occurence_line_index[1]].content[i]);
  }  
 
  for(int i = 0; i <= lines[most_occurence_line_index[0]].char_index; i++)
  {
    if(lines[most_occurence_line_index[0]].content[i] != lines[most_occurence_line_index[1]].content[i])
    {
      
    }
    else
    {
      sol_string[sol_string_index] = lines[most_occurence_line_index[0]].content[i];
      sol_string_index += 1;
    }
  }

  for(int i = 0; i <= sol_string_index; i++)
  {
    printf("%c", sol_string[i]);
  }
  printf("\n");

  //printf("%d * %d = %d\n", count_twice, count_thrice, count_twice * count_thrice);

  return 0;
}
