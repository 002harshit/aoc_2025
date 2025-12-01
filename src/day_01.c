#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int parse_line(FILE* input_file, int* amount, int* direction)
{
  char buffer[256];
  if (fgets(buffer, sizeof(buffer), input_file)) {
    buffer[strcspn(buffer, "\n")] = '\0';
    *amount = atoi(&buffer[1]);
    *direction = 1;
    if (buffer[0] == 'L') {
      *direction *= -1;
    }
    return 1;
  }
  return 0;
}

int main(int argc, char** argv)
{
  if (argc < 2) {
    printf("ERROR: Provide a input filepath.\n");
  }
  char* input_path = argv[1];
  FILE* input_file = fopen(input_path, "r");
  if (!input_file) {
    printf("ERROR: File not found.\n");
  }
  int amount, direction;
  int dial = 50;
  int part_one = 0;
  int part_two = 0;
  while (parse_line(input_file, &amount, &direction)) {
    // TODO: there might be better 'mathamatical way to do this stuff without a for loop'
    for (int i = 0; i < amount; i++) {
      dial += direction;
      if (dial < 0) dial = 99;
      if (dial > 99) dial = 0;
      if (dial == 0) {
        part_two++;
      }
    }
    if (dial == 0) {
      part_one++;
    }
  }
  printf("part one: %d\n", part_one);
  printf("part two: %d\n", part_two);
}
