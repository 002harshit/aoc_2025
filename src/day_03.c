#include <string.h>
#include <stdlib.h>
#include <stdio.h>

size_t find_max_jolt(char* buffer, size_t buffer_size, int r)
{
  int last_max_index = -1;
  size_t jolt = 0;
  size_t jolt_p1 = 0;
  for (int i = 0; i < r; i++) {
    int max_index = -1;
    char max_digit = '0';
    for (int j = last_max_index+1; j < buffer_size - r + i+1; j++) {
      char digit = buffer[j];
      if (digit > max_digit) {
        max_index = j;
        max_digit = digit;
      }
    }
    jolt = jolt * 10 + (max_digit - '0');
    last_max_index = max_index;
  }
  return jolt;
}

int main(int argc, char** argv)
{
  if (argc < 2) {
    printf("ERROR: Provide a input filepath.\n");
    return -1;
  }

  char* input_path = argv[1];
  FILE* input_file = fopen(input_path, "r");
  if (!input_file) {
    printf("ERROR: File not found.\n");
    return -2;
  }

  size_t part_one = 0;
  size_t part_two = 0;

  const int r = 12;
  char buffer[1024];
  while (fgets(buffer, sizeof(buffer), input_file) && *buffer != '\n') {
    buffer[strcspn(buffer, "\n")] = '\0';
    size_t buffer_size = strlen(buffer);
    part_one += find_max_jolt(buffer, buffer_size, 2);
    part_two += find_max_jolt(buffer, buffer_size, 12);
  }

  printf("part one: %llu\n", part_one);
  printf("part two: %llu\n", part_two);
}
