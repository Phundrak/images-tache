#include "black_border.h"

//extern Image_t image;

//bool pix_is_border(Image_t img, Pixel_t pix, Zone_t z) {
//  /* teste si un pixel adjacent est en dehors de l'image */
//  if (pix->x - 1 >= img->sizeX || pix->y - 1 >= img->sizeY ||
//      pix->x + 1 >= img->sizeX || pix->y + 1 >= img->sizeY)
//    return true;
//
//  /* teste si le pixel à droite fait partie de la zone */
//  if (!in_zone(pix_at_img(pix->x + 1, pix->y), z))
//    return true;
//
//  /* teste si le pixel à gauche fait partie de la zone */
//  if (!in_zone(pix_at_img(pix->x - 1, pix->y), z))
//    return true;
//
//  /* teste si le pixel en haut fait partie de la zone */
//  if (!in_zone(pix_at_img(pix->x, pix->y + 1), z))
//    return true;
//
//  /* teste si le pixel en bas fait partie de la zone */
//  if (!in_zone(pix_at_img(pix->x, pix->y - 1), z))
//    return true;
//
//  return false;
//}
//
//void put_pix_color(Pixel_t pix, unsigned char r, unsigned char g,
//                   unsigned char b) {
//  *pix->R = r;
//  *pix->G = g;
//  *pix->B = b;
//}
//
//void invert_color(Pixel_t pix) {
//  *pix->R = (unsigned char) (255 - *pix->R);
//  *pix->G = (unsigned char) (255 - *pix->G);
//  *pix->B = (unsigned char) (255 - *pix->B);
//}
//
//void black_border(Image_t img, Zone_t z) {
//  unsigned long x, y;
//
//  for (y = 0; y < img->sizeY; y++) {
//    for (x = 0; x < img->sizeX; x++) {
//      if (pix_is_border(img, pix_at_img(x, y), z))
//        put_pix_color(pix_at_img(x, y), 0, 0, 0);
//    }
//  }
//}
//
//void invert_border(Image_t img, Zone_t z) {
//  unsigned long i;
//  for (i = 0; i < z->nb_pixels; i++)
//    if (pix_is_border(img, z->pixels[i], z))
//      invert_color(z->pixels[i]);
//}
