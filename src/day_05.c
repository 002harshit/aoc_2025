#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct {
  long start, end;
} range_t;

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
  long part_two = 0;

  size_t range_cap = 4;
  size_t range_len = 0;
  range_t* range_list = malloc(sizeof(range_t) * range_cap);

  char buffer[2024];

  while (fgets(buffer, sizeof(buffer), input_file) && buffer[0] != '\n') {
    buffer[strcspn(buffer, "\n")] = '\0';
    if (range_len >= range_cap) {
      range_cap *= 2;
      range_list = realloc(range_list, range_cap * sizeof(range_t));
    }

    sscanf(buffer, "%ld-%ld", &range_list[range_len].start, &range_list[range_len].end);
    range_len++;
  }

  size_t id_cap = 4;
  size_t id_len = 0;
  long* id_list = malloc(sizeof(long) * id_cap);

  while (fgets(buffer, sizeof(buffer), input_file) && buffer[0] != '\n') {
    buffer[strcspn(buffer, "\n")] = '\0';

    if (id_len >= id_cap) {
      id_cap *= 2;
      id_list = realloc(id_list, id_cap * sizeof(long));
    }

    sscanf(buffer, "%ld", &id_list[id_len]);
    id_len++;
  }

  for (size_t i = 0; i < id_len; i++) {
    size_t id = id_list[i];
    for (size_t r = 0; r < range_len; r++) {
      range_t range = range_list[r];
      if (id >= range.start && id <= range.end) {
        part_one++;
        break;
      }
    }
  }

  for (size_t a = 0; a < range_len; a++) {
    range_t ra = range_list[a];
    if (ra.start == -1) {
      continue;
    }

    for (size_t b = 0; b < range_len; b++) {
      range_t rb = range_list[b];
      if (a == b || rb.start == -1) {
        continue;
      }

      if (ra.start >= rb.start && ra.end <= rb.end) {
        //  sb --------- eb ----
        // --- sa --- ea -------
        ra.start = -1;
      }
      else if (ra.start >= rb.start && ra.start <= rb.end) {
        // sb ------ eb --------
        // ---- sa ------- ea --
        ra.start = rb.end+1;
      }
      else if (ra.end >= rb.start && ra.end <= rb.end) {
        // ---- sb ------- eb --
        // sa ------ ea --------
        ra.end = rb.start - 1;
      }
    }
    range_list[a] = ra;
    if (ra.start == -1) {
      continue;
    }
    long count = ra.end - ra.start + 1;
    part_two += count;
  }

  printf("part one: %d\n", part_one);
  printf("part two: %ld\n", part_two);
}
