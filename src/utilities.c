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

/* printhelp *****************************************************************/

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

/* strcomp *******************************************************************/

bool strcomp(char *str1, char *str2) {
  for (; *str1 == *str2 && str1 && str2; ++str1, ++str2)
    ;
  return str1 == str2;
}

/* img_add_zone **************************************************************/

void img_add_zone(Image_t img, Zone_t zone) {
  (*img).zones[img->nb_zones++] = zone;
}

/* in_zone *******************************************************************/

bool in_zone(Pixel_t pix, Zone_t zt) { return pix->zone == zt; }

/* new_zone ******************************************************************/

Zone_t new_zone(Image_t img, Pixel_t pix) {
  Zone_t zone;

  /* création et initialisation de la zone */

  PDEB("malloc pour la zone numéro %lu\n", img->nb_zones);

  zone = (struct Zone *)malloc(sizeof(struct Zone));
  PDEB("Malloc performed\n");
  (*zone).R = *pix->R;
  (*zone).G = *pix->G;
  (*zone).B = *pix->B;

  PDEB("Deuxième malloc\n");
  (*zone).pixels = (Pixel_t *)malloc(sizeof(Pixel_t));
  (*zone).pixels[0] = pix;
  (*zone).nb_pixels = 1;
  (*zone).capacity = 1;

  /* ajout de zone à pix */
  (*pix).zone = zone;

  PDEB("Zone %lu créée, ajout à img\n", img->nb_zones);

  /* ajout de zone à img */
  img_add_zone(img, zone);

  return zone;
}

/* zone_add_pix **************************************************************/
void zone_add_pix(Zone_t zone, Pixel_t pix) {
  Pixel_t *temp;
  unsigned long i;

  if (zone->nb_pixels >= zone->capacity) {
    (*zone).capacity *= 2;
    temp = zone->pixels;
    (*zone).pixels = NULL;
    (*zone).pixels = (Pixel_t *)malloc(zone->capacity * sizeof(Pixel_t));
    for (i = 0; i < zone->nb_pixels; i++)
      (*zone).pixels[i] = temp[i];
    free(temp);
  }

  (*zone).pixels[zone->nb_pixels++] = pix;
  (*pix).zone = zone;
}

/* pix_at_img ****************************************************************/

Pixel_t pix_at_img(Image_t img, unsigned long x, unsigned long y) {
  if (x >= img->sizeX || y >= img->sizeY)
    return NULL;
  return img->pixels[x + y * img->sizeX];
}

/* new_pixel *****************************************************************/

Pixel_t new_pixel(unsigned char *R, unsigned char *G, unsigned char *B,
                  unsigned long x, unsigned long y) {
  Pixel_t pixel;
  pixel = (Pixel_t)malloc(sizeof(struct Pixel));
  (*pixel).R = R;
  (*pixel).G = G;
  (*pixel).B = B;
  (*pixel).x = x;
  (*pixel).y = y;
  (*pixel).zone = NULL;
  return pixel;
}

int abs(int x) { return (x < 0) ? -x : x; }

/* delete ********************************************************************/

void delete (Image_t img) {
  unsigned long i, size;
  size = img->sizeX * img->sizeY;
  for (i = 0; i < size; i++)
    free(img->pixels[i]);
  for (i = 0; i < img->nb_zones; i++)
    free(img->zones[i]);
  free(img->data);
  free(img);
}
