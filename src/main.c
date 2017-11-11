#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define bool _Bool
#define DEBUG if (1)
#define PDEB                                                                   \
  if (1)                                                                       \
  printf

void printhelp();
int strcomp(char *, char *);

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

int strcomp(char *str1, char *str2) {
  for (; *str1 == *str2 && str1 && str2; ++str1, ++str2)
    ;
  return str1 == str2;
}

int main(int argc, char *argv[]) {
  char *input_filename = NULL;
  char *default_inname = "input.bmp";
  char *output_filename = NULL;
  char *default_outname = "output.bmp";
  FILE *input_file;
  FILE *output_file;

  int tolerance;
  bool do_help = false;
  bool if_invalid = false;
  if (argc < 2) { // no arguments, default values
    tolerance = 0;
  } else { // processing arguments
    while (1) {
      int option_index = 0;
      static struct option long_options[] = {
          {"help", no_argument, NULL, 'h'},
          {"input-file", required_argument, NULL, 'i'},
          {"output-file", required_argument, NULL, 'o'},
          {"tolerance", required_argument, NULL, 't'},
          {0, 0, 0, 0}};
      int c = getopt_long(argc, argv, "i:o:t:h", long_options, &option_index);
      if (c == -1)
        break;
      switch (c) {
      case 0:
        DEBUG {
          printf("\noption %s", long_options[option_index].name);
          if (optarg)
            printf(" with arg %s\n", optarg);
        }
        break;
      case 'h':
        do_help = true;
        break;
      case 'i':
        PDEB("\nFrom main - Option --input-file with value '%s'\n", optarg);
        input_filename = (char*) malloc(sizeof(optarg));
        strcpy(input_filename, optarg);
        break;
      case 'o':
        PDEB("\nFrom main - Option --output-file with value '%s'\n", optarg);
        output_filename = (char*) malloc(sizeof(optarg));
        strcpy(output_filename, optarg);
        break;
      case 't':
        tolerance = atoi(optarg);
        PDEB("\nFrom main - Option --tolerance with value %d\n", tolerance);
        break;
      case ':': // missing option argument
        fprintf(stderr, " option %s requires an argument.\n", argv[1]);
        if_invalid = true;
        break;
      case '?':
      default:
        fprintf(stderr, "option %s is invalid: ignored\n", argv[1]);
        if_invalid = true;
        break;
      }
    }
  } // finished processing arguments

  if (!input_filename) {
    input_filename = default_inname;
  }
  if (!output_filename)
    output_filename = default_outname;
  input_file = fopen(input_filename, "r");
  if (!input_file) {
    printf("Could not open file '%s'.\n", input_filename);
    return 1;
  }
  output_file = fopen(output_filename, "w");
  if (!output_file) {
    printf("Could not open file '%s'.\n", output_filename);
    fclose(input_file);
    return 1;
  }

  if (true == if_invalid || true == do_help) {
    printhelp();
    if (input_file)
      fclose(input_file);
    if (output_file)
      fclose(output_file);
    return 0;
  }

  if (input_file)
    fclose(input_file);
  if (output_file)
    fclose(output_file);
  return 0;
}
