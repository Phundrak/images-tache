#include "utilities.h"

bool pix_is_border(struct Image *img, struct Pixel *pix, struct Zone *z) {
  Pixel *p;
  if (pix->x < img->sizeX + 1) {
    p = pix_at_img(img, pix->x + 1, pix->y);
    return p->zone->R == z->R && p->zone->G == z->G && p->zone->B == z->B;
  }
  if (pix->x > 0) {
    p = pix_at_img(img, pix->x - 1, pix->y);
    if (p->zone->R != z->R)
      return false;
    if (p->zone->G != z->G)
      return false;
    if (p->zone->B != z->B)
      return false;
  }
  if (pix->y < img->sizeY + 1) {
    p = pix_at_img(img, pix->x, pix->y + 1);
    if (p->zone->R != z->R)
      return false;
    if (p->zone->G != z->G)
      return false;
    if (p->zone->B != z->B)
      return false;
  }
  if (pix->y > 0) {
    p = pix_at_img(img, pix->x, pix->y - 1);
    if (p->zone->R != z->R)
      return false;
    if (p->zone->G != z->G)
      return false;
    if (p->zone->B != z->B)
      return false;
  }
  return true;
}

void put_pix_color(struct Pixel *pix, unsigned char r, unsigned char g,
                   unsigned char b) {
  *pix->R = r;
  *pix->G = g;
  *pix->B = b;
}

void black_border(struct Image *img, struct Zone *z) {
  unsigned long x, y;

  for (y = 0; y < img->sizeY; y++) {
    for (x = 0; x < img->sizeX; x++) {
      if (pix_is_border(img, pix_at_img(img, x, y), z))
        put_pix_color(pix_at_img(img, x, y), 0, 0, 0);
    }
  }
}
