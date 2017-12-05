#include "utilities.h"
#include <stdio.h>

unsigned long nb_appels;

extern int tolerance;

bool in_a_zone(struct Pixel *pix) { return !pix->zone ? false : true; }

bool tolerated(struct Pixel *pix, struct Zone *zt) {
  int diff_R, diff_G, diff_B;
    bool res;
  diff_R = (abs((int)zt->R - (int)*pix->R) * 100) / 255;
  diff_G = (abs((int)zt->G - (int)*pix->G) * 100) / 255;
  diff_B = (abs((int)zt->B - (int)*pix->B) * 100) / 255;
  res =  ((diff_R + diff_G + diff_B) / 3) <= tolerance;
    return res;
}

void running_area(Pixel_t pix, Image_t img, Zone_t zt) {
  Pixel_t pix_eval;
//  PDEB("%lu: debut du running area (%lu zones)\n", ++nb_appels, img->nb_zones);

  /* si le pixel n'est pas dans la zone courante, on cesse l’évaluation */
//  if (!in_zone(pix, zt)) {
//    return;
//  }

  /* si la couleur du pixel est tolérable pour la zone, on l’y ajoute et on
   * évalue les pixels voisins, sinon le pixel n'est pas éligible et
   * l’évaluation du pixel courant cesse
   */
  if (!tolerated(pix, zt))
    return;
  zone_add_pix(zt, pix);

  DEBUG {
    printf("x = %lu\n", (*pix).x);
    printf("y = %lu\n", (*pix).y);
    printf("sizeX = %lu\n", (*img).sizeX);
    printf("sizeY = %lu\n", (*img).sizeY);
    printf("x - 1 = %lu\n", (*pix).x - 1);
    printf("x + 1 = %lu\n", (*pix).x + 1);
    printf("y - 1 = %lu\n", (*pix).y - 1);
    printf("y + 1 = %lu\n", (*pix).y + 1);
  }

  /* Évaluation pixel droit */
  pix_eval = pix_at_img(img, pix->x + 1, pix->y);
  if (pix_eval && !in_a_zone(pix_eval))
    running_area(pix_eval, img, zt);

  /* évaluation pixel gauche */
  pix_eval = pix_at_img(img, pix->x - 1, pix->y);
  if (pix_eval && !in_a_zone(pix_eval))
    running_area(pix_eval, img, zt);

  /* évaluation pixel haut */
  pix_eval = pix_at_img(img, pix->x, pix->y + 1);
  if (pix_eval && !in_a_zone(pix_eval))
    running_area(pix_eval, img, zt);

  /* évaluation pixel bas */
  pix_eval = pix_at_img(img, pix->x, pix->y - 1);
  if (pix_eval && !in_a_zone(pix_eval))
    running_area(pix_eval, img, zt);

  PDEB("in_a_zone de running_area ne segfault pas\n");
}

void map_area(struct Pixel *pix, struct Image *img) {
  struct Zone *zt;

    if(in_a_zone(pix))
        return;

  PDEB("Création zone numéro %lu\n", img->nb_zones);
  zt = new_zone(img, pix);
  PDEB("apres la creation de la zone\n");
  running_area(pix, img, zt);
  PDEB("fin running_area\n");
}

void process(struct Image *img) {
  unsigned long x, y;

  nb_appels = 0;
  PDEB("debut du parcour du tableau\n");
  for (y = 0; y < (*img).sizeY; y++) {
    PDEB("parcoure de la ligne %lu : \n", y);
    for (x = 0; x < (*img).sizeX; x++) {
      PDEB("parcour du pixel %lu : \n", x);
      if (!in_a_zone(pix_at_img(img, x, y))) {
        PDEB("in_a_zone ne segfault pas\n");
        map_area(pix_at_img(img, x, y), img);
        PDEB("fin du mapping\n");
      }
    }
  }
}
