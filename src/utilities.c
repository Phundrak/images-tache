#include "utilities.h"
#include <stdio.h>

void printhelp() {
  printf("Usage: images-tache [options...]\n\n"
         "Options:\n"
         "\t-h, --help\n"
         "\t\tDisplay this.\n"
         "\t-i <file>, --input-file <file>\n"
         "\t\tFile to be processed. Unless specified, the default name is "
         "\"input.bmp\"\n"
         "\t-o, --output-file\n"
         "\t\tOutput file. Unless specified, default name is \"output.bmp\"\n"
         "\t-t <value>, --tolerance <value>\n"
         "\t\tTolerance on the creation of the color regions, indicated by "
         "percentage (0 - 100)\n");
}

bool strcomp(char *str1, char *str2) {
  for (; *str1 == *str2 && str1 && str2; ++str1, ++str2)
    ;
  return str1 == str2;
}
