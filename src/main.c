/*****************************************************************************/
/*                             INCLUDE DIRECTIVES                            */
/*****************************************************************************/

#include "interface.h"
#include "ppm.h"
#include "utilities.h"
#include <getopt.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*****************************************************************************/
/*                             DEFINE DIRECTIVES                             */
/*****************************************************************************/

#define bool _Bool

/*****************************************************************************/
/*                              GLOBAL VARIABLES                             */
/*****************************************************************************/

Image_t image;

/*****************************************************************************/
/*                               MAIN FUNCTION                               */
/*****************************************************************************/

int main(int argc, char *argv[]) {
  char *input_filename = NULL;
  char *default_inname = "input.bmp";
  char *output_filename = NULL;
  char *default_outname = "output.bmp";
  int tolerance;
  int option_index;
  bool do_help;
  bool if_invalid;

  do_help = false;
  if_invalid = false;

  if (argc < 2) { // no arguments, default values
    tolerance = 0;
  } else { // processing arguments
    while (1) {
      option_index = 0;
      static struct option long_options[] = {
          /* --help or -h requires no argument */
          {"help", no_argument, NULL, 'h'},
          /* --input-file or -i requires one argument */
          {"input-file", required_argument, NULL, 'i'},
          /* --output-file or -o requires one argument */
          {"output-file", required_argument, NULL, 'o'},
          /* --tolerance or -t requires one argument */
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
      case 'h': /* help */
        do_help = true;
        break;
      case 'i': /* input */
        PDEB("\nFrom main - Option --input-file with value '%s'\n", optarg);
        input_filename = (char *)malloc(sizeof(optarg));
        strcpy(input_filename, optarg);
        break;
      case 'o': /* output */
        PDEB("\nFrom main - Option --output-file with value '%s'\n", optarg);
        output_filename = (char *)malloc(sizeof(optarg));
        strcpy(output_filename, optarg);
        break;
      case 't': /* tolerance (0-100) */
        tolerance = atoi(optarg);
        PDEB("\nFrom main - Option --tolerance with value %d\n", tolerance);
        break;
      case ':': /* missing option argument */
        fprintf(stderr, " option %s requires an argument.\n", argv[1]);
        if_invalid = true;
        break;
      case '?': /* invalid option */
      default:
        fprintf(stderr, "option %s is invalid: ignored\n", argv[1]);
        if_invalid = true;
        break;
      }
    }
  } /* finished processing arguments */

  if (true == if_invalid || true == do_help) {
    printhelp();
    if (input_filename)
      free(input_filename);
    if (output_filename)
      free(output_filename);
    return (int)if_invalid;
  }

  /* applying defaults if not set by arguments */

  if (!input_filename)
    input_filename = default_inname;
  if (!output_filename)
    output_filename = default_outname;

  /* finished applying defaults */

  /***************************************************************************/
  /*                              DO STUFF HERE                              */
  /***************************************************************************/

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
  glutInitWindowSize(640, 480);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("VPUP8");

  Init(argv[1]);

  /***************************************************************************/
  /*                                                                         */
  /***************************************************************************/

  free(input_filename);
  free(output_filename);
  return 0;
}
