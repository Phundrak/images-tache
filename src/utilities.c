/**
 *   \file utilities.c
 *   \brief Fichier d'implémentation des fonctions d'utilité
 *
 *  Fichier contenant l'implémentation des fonctions d'ulitité déclarées dans le
 *  fichier \ref utilities.h
 */

#include "utilities.h"
#include <stdio.h>
#include <stdlib.h>

extern Image_t image;
extern int tolerance;

int abs(int x) {
  return (x < 0) ? -x : x;
}

bool tolerated(Pixel_t pix, Zone_t zt) {
  int diff_R, diff_G, diff_B;
  bool res;
  diff_R = (abs((int)zt->R - (int)*pix->R) * 100) / 255;
  diff_G = (abs((int)zt->G - (int)*pix->G) * 100) / 255;
  diff_B = (abs((int)zt->B - (int)*pix->B) * 100) / 255;
  res =  ((diff_R + diff_G + diff_B) / 3) <= tolerance;
  return res;
}

void img_add_zone(Zone_t zone) {
  image->zones[image->nb_zones++] = zone;
}

void zone_add_segment(Zone_t zone, Segment_t segment) {
  zone->segment[zone->nb_segment++] = segment;
}

Pixel_t pix_at_img(unsigned long x, unsigned long y) {
  if (x >= image->sizeX || y >= image->sizeY)
    return NULL;
  return image->pixels[x + y * image->sizeX];
}

Pixel_t new_pixel(unsigned char *R, unsigned char *G, unsigned char *B,
                  unsigned long x, unsigned long y) {
  Pixel_t pixel;
  pixel = (Pixel_t)malloc(sizeof(struct Pixel));
  (*pixel).R = R;
  (*pixel).G = G;
  (*pixel).B = B;
  (*pixel).x = x;
  (*pixel).y = y;
  (*pixel).processed = false;
  return pixel;
}

Zone_t new_zone(Pixel_t pix) {
  Zone_t zone;
  unsigned long i;

  zone = (Zone_t)malloc(sizeof(Zone));
  zone->R = *pix->R;
  zone->G = *pix->G;
  zone->B = *pix->B;
  zone->nb_segment = 0;
  for(i = 0; i < NBSEGMAX; i++) {
    zone->segment[i] = NULL;
  }

  return zone;
}

void delete () {
  unsigned long i, size;
  size = image->sizeX * image->sizeY;
  for (i = 0; i < size; i++)
    free(image->pixels[i]);
  i = 0;
  while(image->zones[i]) {
    free(image->zones[i]);
    i++;
  }
  free(image->data);
  free(image);
}

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
