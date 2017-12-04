#ifndef IMGTACHES_SRC_BLACKBORDER_H_
#define IMGTACHES_SRC_BLACKBORDER_H_

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
 * \brief Fonction d'initialisation de couleur de Pixel
 *
 * La fonction initialise les couleur R, G, B du Pixel
 *
 * \param[in] pix struct Pixel contenant les donnees du Pixel
 * \param[in] r char correspondant a la valeur R a apposer au pixel
 * \param[in] g char correspondant a la valeur G a apposer au pixel
 * \param[in] b char correspondant a la valeur B a apposer au pixel
 */
 void put_pix_color(struct Pixel *pix, char r, char g, char b);

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
 void pix_is_border(struct Image *img, struct Pixel *pix, struct Zone *z);

#endif
