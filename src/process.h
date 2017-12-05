#ifndef IMGTACHES_SRC_PROCESS_H_
#define IMGTACHES_SRC_PROCESS_H_


/*****************************************************************************/
/*                           FUNCTION DECLARATIONS                           */
/*****************************************************************************/


/**
 * \brief Fonction principale de l'algo
 *
 * parcour les pixels de l'image test si il on une zone attribuee
 * si ce n'est le cas lance la fonction de mapping de la zone
 *
 * \param[in] img struct Image
 */
 void process(struct Image *img);


/**
 *    \brief Creation d'une nouvelle zone et lancement de running_area
 *
 *  la fonction cree une nouvelle zone avec les valeur du pixel passez
 *  en parametre ajoute cette zone a la liste des zone dans la struct Image
 *  lance la fonction running_area
 *
 *  \param[in] pix \ref Pixel contenant les information du pixel
 *  \param[in] img \ref Image contenant les données de l'image
 */
 void map_area(struct Pixel *pix, struct Image *img);


/**
 *   \brief Parcour les pixels adjacent au pixel de la appartenant a la zone
 *
 * test si le pixel appartien a une zone 
 *   test si le pixel appartien a la zone passez en parametre
 *     si c'est le cas s'appel recursivement avec les coordonnees des pixels
 *     adjacant
 *     si non stop son execution
 *   si le pixel n'appartien pas deja a une zone la fonction test si les
 *   les couleurs du pixel sont inferieur au seuil de tolerance
 *     si c'est le cas alors la fonction ajoute la zone au pixel et inversement
 *
 *     \param[in] pix struct Pixel contenant les information du Pixel
 *     \param[in] img struct Image contenant les donees de l'Image
 *     \param[in] zt struct Zone contenant les information de la zone
 */
 void running_area(struct Pixel *pix, struct Image *img, struct Zone *zt);


/**
 * \brief Test si le pixel est dans la tolerance de la zone en parametre
 *
 * la fonction calcule chaque diferance de % des valeur R, G, B du Pixel
 * par rapport a la zone en parametre 
 *
 * \param[in] pix struct Pixel contenant les donnees du pixel
 * \param[in] zt struct Zone contenant les information sur la Zone
 * \return renvoie `true` si la diferance est inferieur a la tolerance
 *                 `false` sinon
 */
 bool pix_to_add(struct Pixel *pix, struct Zone *zt);

/**
 * \brief Test si le pointeur zone du pixel est null
 *
 * \param[in] pix struct pixel contenant les donnees du Pixel
 */
 bool test_exist(struct Pixel *pix);

#endif
