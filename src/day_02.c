#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

int is_invalid_p1(size_t n, char* n_str)
{
  size_t n_len = strlen(n_str);
  size_t left, right, mid;
  left = 0;
  right = n_len / 2;
  mid = right - 1;

  if (n_len % 2 == 1) {
    return 0;
  }

  while (left <= mid && right < n_len) {
    if (n_str[left++] != n_str[right++]) {
      return 0;
    }
  }
  return 1;
}

int is_invalid_p2(size_t n, char* n_str)
{
  size_t n_len = strlen(n_str);
  size_t wnd_len = 1;
  while (wnd_len <= n_len / 2) {
    int is_valid = 0;
    for (size_t i = wnd_len; i < n_len; i += wnd_len) {
      for (size_t j = 0; j < wnd_len; j++) {
        char a = n_str[j];
        char b = n_str[i + j];
        if (a != b) {
          is_valid = 1;
          break;
        }
      }
      if (is_valid) break;
    }
    if (!is_valid) return 1;
    wnd_len++;
  }
  return 0;
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

  char buffer[1024];
  if (!fgets(buffer, sizeof(buffer), input_file)) {
    printf("ERROR: Unable to read or file is empty\n");
    return -3;
  }
  buffer[strcspn(buffer, "\n")] = '\0';
  char* tok = strtok(buffer, ",");

  char n_str[64];
  size_t part_one = 0;
  size_t part_two = 0;

  while (tok) {
    size_t start, end;
    sscanf(tok, "%llu-%llu", &start, &end);
    tok = strtok(NULL, ",");
    assert(start < end);
    assert(start > 0 && end > 0);
    
    for (size_t n = start; n <= end; n++) {
      sprintf(n_str, "%llu", n);
      if (is_invalid_p2(n, n_str)) {
        part_two += n;
      }

      if (is_invalid_p1(n, n_str)) {
        part_one += n;
      }
    }
  }

  printf("part one: %llu\n", part_one);
  printf("part two: %llu\n", part_two);
}
