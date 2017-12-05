#ifndef IMGTACHES_SRC_BLACKBORDER_H_
#define IMGTACHES_SRC_BLACKBORDER_H_

#include "utilities.h"

/**
 * \brief Fonction detectant si le pixel est une bordure de la Zone
 *
 * La fonction test la zone des pixel adjacant a le zone du pixel reference
 * si a un moment les valeur ne corresponde pas entre les zone des pixel
 * et la zone du pixel reference alors la fonction return false
 *
 * \param[in] img struct Image contenant les information de l'Image
 * \param[in] pix struct Pixel contenant les donnees du Pixel
 * \param[in] z struct Zone contenant les information de la Zone
 */
bool pix_is_border(Image_t img, Pixel_t pix, Zone_t z);

/**
 * \brief Fonction d'initialisation de couleur de Pixel
 *
 * La fonction initialise les couleur R, G, B du Pixel
 *
 * \param[in] pix struct Pixel contenant les donnees du Pixel
 * \param[in] r char correspondant a la valeur R a apposer au pixel
 * \param[in] g char correspondant a la valeur G a apposer au pixel
 * \param[in] b char correspondant a la valeur B a apposer au pixel
 */
void put_pix_color(Pixel_t pix, unsigned char r, unsigned char g, unsigned char b);

/**
 *  \brief Enversion de al couleur d’un \ref Pixel
 *  \param[out] pix \ref Pixel dont la couleur doit être inversée
 */
void invert_color(Pixel_t pix);

/**
 * \brief Fonction principal de la modification des bordure en noir
 *
 * Parcour les pixel de struct Image si le pixel est une bordure l'initialise
 * en noir
 *
 * \param[in] img struct Image contenant les information de l'Image
 * \param[in] z struct Zone contenant les donnees de la Zone
 */
void black_border(struct Image *img, struct Zone *z);

/**
 *  \brief Inverse la couleur des pixels d’une zone se trouvant sur sa bordure
 *
 *  Teste chaque pixel de la zone et inverse la couleur des pixels de la zone se
 * trouvant sur la bordure de cette dernière.
 *
 *  \param[in] img Image contenant la zone
 *  \param[out] z Zone à gérer
 */
void invert_border(Image_t img, Zone_t z);

#endif
