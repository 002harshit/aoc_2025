#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>

static int noffsets[8][2] = {
  {1, 0}, {-1, 0}, {0, 1}, {0, -1},
  {1, 1}, {-1, 1}, {-1, -1}, {1, -1},
};

int remove_rolls(char** vector, int vector_size, int row_size)
{
  int result = 0;
  for (int y = 0; y < vector_size; y++) {
    for (int x = 0; x < row_size; x++) {
      // printf("%llu, %llu\n", x, y);
      if (vector[y][x] == '.') {
        printf("..");
        continue;
      }
      int counter = 0;
      for (int n = 0; n < 8; n++) {
        int nx = x + noffsets[n][0];
        int ny = y + noffsets[n][1];
        if (nx < 0 || ny < 0 || nx >= row_size || ny >= vector_size)
          continue;
        if (vector[ny][nx] == '@' || vector[ny][nx] == 'x')
          counter++;
      }
      if (counter < 4) {
        printf("xx");
        vector[y][x] = 'x';
        result++;
      } else {
        printf("@@");
      }
    }
    printf("\n");
  }
  for (int y = 0; y < vector_size; y++) {
    for (int x = 0; x < row_size; x++) {
      if (vector[y][x] != '@') {
        vector[y][x] = '.';
      }
    }
  }
  return result;
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

  int part_one = 0;
  int part_two = 0;

  char buffer[1024];
  char* vector[256]; // just setting static size cuz i feel too lazy to implement dynamic array
  int vector_size = 0;
  int row_size = -1;
  while (fgets(buffer, sizeof(buffer), input_file) && *buffer != '\n') {
    buffer[strcspn(buffer, "\n")] = '\0';
    row_size = strlen(buffer);
    char* row = malloc(sizeof(char) * row_size);
    memcpy(row, buffer, row_size);
    vector[vector_size++] = row;
    // printf("%d %s\n", vector_size, buffer);
  }
  assert(vector_size <= 256);
  assert(row_size > 0 && row_size <= 1024);

  int curr_count = remove_rolls(vector, vector_size, row_size);
  part_one = curr_count;
  do {
    usleep(1000*100);
    printf("\033[%dA", vector_size); 
    printf("\033[%dD", row_size);

    part_two += curr_count;
    curr_count = remove_rolls(vector, vector_size, row_size);
  } while (curr_count != 0);

  printf("part one: %d\n", part_one);
  printf("part two: %d\n", part_two);

  // kids, always free the malloced memory, else linus will probably ruin your career
  for (int y = 0; y < vector_size; y++) {
    free(vector[y]);
  }
}
