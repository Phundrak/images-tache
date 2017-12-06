#ifndef IMGTACHES_SRC_ALGORITHM_H_
#define IMGTACHES_SRC_ALGORITHM_H_

#include "utilities.h"

void generate_segment(Zone_t zone, Pixel_t pix);
void generate_zone(Pixel_t pix);
void make_zones();
void change_color(Pixel_t pix, unsigned char R, unsigned char G,
                  unsigned char B);
void invert_color(Pixel_t pix);
void black_border();

#endif /* IMGTACHES_SRC_ALGORITHM_H_ */
