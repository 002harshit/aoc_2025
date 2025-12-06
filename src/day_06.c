#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

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

  long part_one = 0;
  size_t part_two = 0;

  // variable names are kinda shit
  size_t data_len = 0;
  size_t slen = 0;
  char* data[8];

  size_t num_len = 0;
  size_t num_cap = 4;
  size_t row_len = 0;
  long* num_list = malloc(num_cap * sizeof(long));

  size_t op_len = 0;
  size_t op_cap = 4;
  char* op_list = malloc(op_cap * sizeof(char));

  char buffer[4096];

  while (fgets(buffer, sizeof(buffer), input_file) && *buffer != '\n') {
    buffer[strcspn(buffer, "\n")] = '\0';
    
    if (buffer[0] != ' ' && (buffer[0] < '0' || buffer[0] > '9')) {
      break;
    }
    slen = strlen(buffer);
    char* dup = malloc(slen * sizeof(char));
    memcpy(dup, buffer, slen);
    data[data_len++] = dup;

    char* start = buffer;
    char* end = NULL;
    long n = strtol(start, &end, 10);
    row_len = 0;
    do {
      long n = strtol(start, &end, 10);
      if (num_len >= num_cap) {
        num_cap *= 2;
        num_list = realloc(num_list, num_cap * sizeof(num_list[0]));
      }
      num_list[num_len++] = n;
      row_len++;
      for (start = end; *start && *start == ' '; start++) { }
    } while (*start);
  }

  for (char* op = buffer; *op != '\0'; op++) {
    if (*op == ' ') {
      continue;
    }
    if (op_len >= op_cap) {
      op_cap *= 2;
      op_list = realloc(op_list, op_cap * sizeof(op_list[0]));
    }
    op_list[op_len++] = *op;
  }

  int w = row_len;
  int h = num_len / row_len;
  assert(w == op_len);

  for (int x = 0; x < w; x++) {
    char op = op_list[x];
    long result = op == '*';
    for (int y = 0; y < h; y++) {
      long n = num_list[x + y * w];
      result = op == '*' ? result * n : result + n;
    }
    part_one += result;
  }

  int iop = 0;
  long result = op_list[iop] == '*';
  int is_prev_empty = 0;
  for (int y = 0; y < slen; y++) {
    long n = 0;
    for (int x = 0; x < data_len; x++) {
      char c = data[x][y];
      assert(c != '0');
      if (c == ' ')
        continue;

      n = n * 10 + (c - '0');
    }
    if (n != 0) {
      is_prev_empty = 0;
      result = op_list[iop] == '*' ? result * n : result + n;
    }

    if (n == 0 || y == slen-1) {
     assert(is_prev_empty != 1);
     assert(iop < op_len);
     is_prev_empty = 1;
     part_two += result;
     iop++;
     if (iop < op_len)
      result = op_list[iop] == '*';
    }
  }

  printf("part one: %ld\n", part_one);
  printf("part two: %zu\n", part_two);

  free(op_list);
  free(num_list);
  for (int i = 0; i < data_len; i++) {
    free(data[i]);
  }
  fclose(input_file);
} 
