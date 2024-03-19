#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct data_ {
  unsigned char upper : 4;
  unsigned char lower : 4;
} data;

#define LOWER_MASK 0b00001111
#define UPPER_MASK 0b11110000

/*
this function will compress the data from the input file and write the
compressed data to the output file.
the input file is a .txt file that contains a string of digits.
the output file is a .bin file that contains the compressed data.
the compressed data is a sequence of 4-bit values, where each value
represents the not of the digit in the input file.

@param in: the input file. text file that open in read mode.
@param out: the output file. binary file that open in write mode.
*/
void compress_data(FILE* in, FILE* out) {
  char lower, upper;
  data d;

  while ((lower = fgetc(in)) != EOF) {
    if ((upper = fgetc(in)) == EOF) {
      upper = '0';
    }
    d.lower = ~(lower - '0');
    d.upper = ~(upper - '0');

    if (fwrite(&d, sizeof(data), 1, out) != 1) {
      fprintf(stderr, "Error writing to file\n");
      exit(1);
    }
  }
}

/*
this function will decompress the data from the input file and write the
decompressed data to the output file.
the input file is a .bin file that contains the compressed data.
the output file is a .txt file that contains the decompressed data.
the compressed data is a sequence of 4-bit values, where each value
represents the not of the digit in the input file.

@param in: the input file. binary file that open in read mode.
@param out: the output file. text file that open in write mode.
*/
void decompress_data(FILE* in, FILE* out) {
  char number;

  while (fread(&number, sizeof(char), 1, in) == 1) {
    number = ~number;
    char lower = number & LOWER_MASK;
    char upper = (number & UPPER_MASK) >> 4;
    fprintf(out, "%d%d", upper, lower);
  }
}