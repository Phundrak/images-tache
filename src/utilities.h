#ifndef IMGTACHES_SRC_UTILITIES_H_
#define IMGTACHES_SRC_UTILITIES_H_

#include <stdbool.h>
#include <GL/gl.h>

/*****************************************************************************/
/*                             DEFINE DIRECTIVES                             */
/*****************************************************************************/

#ifdef Debug
#define DEBUG if (1)
#define PDEB                                                                   \
  if (1)                                                                       \
  printf
#else
#define DEBUG if (0)
#define PDEB                                                                   \
  if (0)                                                                       \
  printf
#endif

/*****************************************************************************/
/*                     FORWARD DECLARATIONS AND TYPEDEFS                     */
/*****************************************************************************/

struct Image;
typedef struct Image Image;
typedef struct Image *Image_t;
struct Pixel;
typedef struct Pixel Pixel;
typedef struct Pixel *Pixel_t;
struct Zone;
typedef struct Zone Zone;
typedef struct Zone *Zone_t;;

/*****************************************************************************/
/*                             STRUCT DECLARATIONS                           */
/*****************************************************************************/

struct Image {
  unsigned long sizeX;
  unsigned long sizeY;
  GLubyte *data;
  struct Pixel *pixels;
  struct Zone *zones;
};

struct Pixel {
  char R;
  char G;
  char B;
  unsigned long x;
  unsigned long y;
  struct Zone *zone;
};

struct Zone {
  char R;
  char G;
  char B;
  struct Pixel *pixels;
};

/*****************************************************************************/
/*                           FUNCTION DECLARATIONS                           */
/*****************************************************************************/

void printhelp();
bool strcomp(char*, char*);

#endif /* IMGTACHES_SRC_UTILITIES_H_ */
