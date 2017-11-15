#include "utils.h"
#include <stdlib.h>

void free_image(Image_t image) {
  free(image->pixels);
  free(image);
}
