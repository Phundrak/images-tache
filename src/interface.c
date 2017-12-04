/**
 *   \file interface.c
 *   \brief Fichier d'implémentation des fonctions d'interface graphique
 *
 *  Fichier d'implémentation des fonctions d'interface graphique pour OpenGL.
 *  Leur déclaration se trouve dans \ref interface.h
 *
 */

#include "interface.h"
#include "ppm.h"
#include <stdio.h>

extern Image_t image;

int Init(char *s) {
  image = (Image_t)malloc(sizeof(Image));
  if (!image) {
    fprintf(stderr, "Out of memory\n");
    return -1;
  }
  if (ImageLoad_PPM(s, image) == -1)
    return -1;
  printf("Tailles: %d %d\n", (int)image->sizeX, (int)image->sizeY);

  return 0;
}
