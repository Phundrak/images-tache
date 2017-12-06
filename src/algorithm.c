#include "algorithm.h"
#include <stdlib.h>

extern Image_t image;

unsigned long iter;

void generate_segment(Zone_t zone, Pixel_t pix) {
  unsigned long xg, xd, i;
  Segment_t segment;
  Pixel_t pixel;

  /* création du segment basé sur pix */
  segment = (Segment_t)malloc(sizeof(Segment));
  for (xg = pix->x; xg < image->sizeX && pix_at_img(xg, pix->y) &&
                    tolerated(pix_at_img(xg, pix->y), zone);
       xg--)
    ;
  xg++;
  for (xd = pix->x; xd < image->sizeX && pix_at_img(xd, pix->y) &&
                    tolerated(pix_at_img(xd, pix->y), zone);
       xd++)
    ;
  xd--;

  segment->y = pix->y;
  segment->xg = xg;
  segment->xd = xd;
  zone_add_segment(zone, segment);

  PDEB("iter: %lu\nnb zones: %lu\nnb segments: %lu\n", iter++, image->nb_zones,
       zone->nb_segment);

  for (i = xg; i < xd; i++) {
    pixel = pix_at_img(i, pix->y);
    pixel->processed = true;
  }

  /* pour chaque pixel supérieur aux pixels du segment */
  for (i = xg; i < xd; i++) {
    pixel = pix_at_img(i, pix->y + 1);
    /* si le pixel existe, qu'il est non-traité et qu'il est de la bonne couleur
     */
    if (pixel && !pixel->processed && tolerated(pixel, zone))
      generate_segment(zone, pixel);
  }
  /* pour chaque pixel inférieur aux pixels du segment */
  for (i = xg; i < xd; i++) {
    pixel = pix_at_img(i, pix->y - 1);
    /* si le pixel existe, qu'il est non-traité et qu'il est de la bonne couleur
     */
    if (pixel && !pixel->processed && tolerated(pixel, zone))
      generate_segment(zone, pixel);
  }
}

void generate_zone(Pixel_t pix) {
  Zone_t zone;
  zone = new_zone(pix);
  img_add_zone(zone);
  generate_segment(zone, pix);
}

void make_zones() {
  iter = 0;
  unsigned long i, size;
  size = image->sizeX * image->sizeY;
  for (i = 0; i < size; i++)          /* pour chaque pixel */
    if (!image->pixels[i]->processed) /* si le pixel n'a pas été traité */
      generate_zone(image->pixels[i]);
}

void change_color(Pixel_t pix, unsigned char R, unsigned char G,
                  unsigned char B) {
  *pix->R = R;
  *pix->G = G;
  *pix->B = B;
}

void invert_color(Pixel_t pix) {
  *pix->R = (unsigned char)(255 - *pix->R);
  *pix->G = (unsigned char)(255 - *pix->G);
  *pix->B = (unsigned char)(255 - *pix->B);
}

void black_border() {
  unsigned long i, j, k;
  Pixel_t pix1, pix2;
  Segment_t seg;

  for (i = 0; image->zones[i]; i++) {
    for (j = 0; image->zones[i]->segment[j]; j++) {
      seg = image->zones[i]->segment[j];

      invert_color(pix_at_img(seg->xd, seg->y));
      invert_color(pix_at_img(seg->xg, seg->y));
    }
  }
}
