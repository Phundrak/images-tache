#ifndef IMGTACHES_SRC_BLACKBORDER_H_
#define IMGTACHES_SRC_BLACKBORDER_H_

void black_border(struct Image *img, struct Zone *z);
void put_pix_color(struct Pixel *pix, char r, char g, char b);
void pix_is_border(struct Image*img, struct Pixel *pix, struct Zone *z);

#endif
