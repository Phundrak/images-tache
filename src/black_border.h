#ifndef IMGTACHES_SRC_BLACKBORDER_H_
#define IMGTACHES_SRC_BLACKBORDER_H_

#include "utilities.h"

/**
 * \brief Fonction détectant si le pixel est une bordure de la zone courante
 *
 * La fonction teste chacun des pixels adjacents au pixel courant. Si au moins
 * l’un d’entre eux n’existe pas (le pixel courant est en bord d’image) ou
 * fait partie d’une zone différente, alors le pixel est un pixel de bordure
 * de la zone courante et la fonction renvoie `true`. Dans le cas contraire,
 * la fonction renvoie `false`.
 *
 * \param[in] img \ref Image traitée
 * \param[in] pix \ref Pixel courant
 * \param[in] z \ref Zone courante
 * \return Renvoie `true` si le pixel borde la zone, `false` sinon
 */
bool pix_is_border(Image_t img, Pixel_t pix, Zone_t z);

/**
 * \brief Change la couleur RGB d’un pixel
 * \param[out] pix \ref Pixel dont la couleur doit être changée
 * \param[in] r Nouvelle valeur R du sous-pixel rouge du pixel
 * \param[in] g Nouvelle valeur G du sous-pixel rouge du pixel
 * \param[in] b Nouvelle valeur B du sous-pixel rouge du pixel
 */
void put_pix_color(Pixel_t pix, unsigned char r, unsigned char g, unsigned char b);

/**
 * \brief Inversion de la couleur du pixel courant
 * \param[out] pix \ref Pixel dont la couleur doit être inversée
 */
void invert_color(Pixel_t pix);

/**
 * \brief Inverse la couleur des pixels d’une zone se trouvant sur sa bordure
 *
 * Teste chaque pixel de la zone et inverse la couleur des pixels de la zone se
 * trouvant sur la bordure de cette dernière.
 *
 * \param[in] img Image contenant la zone
 * \param[out] z Zone à gérer
 */
void invert_border(Image_t img, Zone_t z);

#endif
