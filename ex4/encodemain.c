#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "compress.h"

int check_args(char *flag, char *input_file);
char *change_extension(char *file_name, char *new_extension);
int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("Invalid number of arguments\n");
    printf("Usage: digitcompress <flag> <input file>\n");
    return 1;
  }

  char *flag = argv[1];
  char *input_file = argv[2];
  if (!check_args(flag, input_file)) {
    return 1;
  }
  char *out_file_name;
  FILE *in;
  FILE *out;
  if (strcmp(flag, "-c") == 0) {
    printf("Compressing %s\n", input_file);
    out_file_name = change_extension(input_file, ".bin");
    printf("Output file: %s\n", out_file_name);
    in = fopen(input_file, "r");
    out = fopen(out_file_name, "wb");
    if (in == NULL || out == NULL) {
      fprintf(stderr, "Error opening file\n");
      free(out_file_name);
      exit(1);
    }
    compress_data(in, out);
  } else {
    printf("Decompressing %s\n", input_file);
    out_file_name = change_extension(input_file, ".txt");
    printf("Output file: %s\n", out_file_name);
    in = fopen(input_file, "rb");
    out = fopen(out_file_name, "w");
    if (in == NULL || out == NULL) {
      fprintf(stderr, "Error opening file\n");
      free(out_file_name);
      exit(1);
    }
    decompress_data(in, out);
  }

  free(out_file_name);
  fclose(in);
  fclose(out);
  printf("Done\n");
  return 0;
}

char *change_extension(char *file_name, char *new_extension) {
  char *new_file_name = malloc(strlen(file_name) + 1);
  strcpy(new_file_name, file_name);
  char *dot = strrchr(new_file_name, '.');
  if (dot) {
    *dot = '\0';
  }
  strcat(new_file_name, new_extension);
  return new_file_name;
}

int ends_with(char *str, char *suffix) {
  if (!str || !suffix) return 0;
  size_t len = strlen(str);
  size_t suf_len = strlen(suffix);
  if (suf_len > len) return 0;
  return strncmp(str + len - suf_len, suffix, suf_len) == 0;
}

int check_args(char *flag, char *input_file) {
  if (strcmp(flag, "-c") != 0 && strcmp(flag, "-d") != 0) {
    printf("Invalid flag\n");
    printf("flag must be -c or -d\n");
    printf("Usage: digitcompress <flag> <input file>\n");
    return 0;
  }

  if (!ends_with(input_file, ".txt") && !ends_with(input_file, ".bin")) {
    printf("Invalid input file\n");
    printf("input file must be a .txt or .bin file\n");
    printf("Usage: digitcompress <flag> <input file>\n");
    return 0;
  }

  if (strcmp(flag, "-c") == 0 && ends_with(input_file, ".bin")) {
    printf("Invalid input file\n");
    printf("input file must be a .txt file for compression\n");
    return 0;
  }
  if (strcmp(flag, "-d") == 0 && ends_with(input_file, ".txt")) {
    printf("Invalid input file\n");
    printf("input file must be a .bin file for decompression\n");
    return 0;
  }
  return 1;
}