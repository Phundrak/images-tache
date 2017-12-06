#ifndef IMGTACHES_SRC_PROCESS_H_
#define IMGTACHES_SRC_PROCESS_H_


/*****************************************************************************/
/*                           FUNCTION DECLARATIONS                           */
/*****************************************************************************/


/**
 * \brief Fonction principale de l'algorithme
 *
 * Parcours les pixels de l’image et teste s’ils ont une zone déjà attribée.
 * Si ce n’est pas le cas, lance la fonction de mapping de zone `map_area`.
 *
 * \param[in] img \ref Image traitée
 */
 void process(struct Image *img);


/**
 * \brief Création d’une nouvelle zone basée sur le pixel courant
 *
 * La fonction créé une nouvelle zone vierge dont la couleur de référence se
 * base sur le pixel courant. Ce dernier sera également ajouté dans la liste
 * des pixels de la zone, et le pointeur de zone du pixel est initialisé vers
 * la nouvelle zone. La zone sera ajoutée à la liste de zones de l’image
 * traitée.
 *
 * \param[in] pix \ref Pixel courant
 * \param[in] img \ref Image traitée
 */
 void map_area(struct Pixel *pix, struct Image *img);


/**
 * \brief Parcours des pixels adjacents au pixel courant
 *
 * Pour chaque pixel adjacent au pixel courant, un test est réalisé pour savoir
 * si le pixel appartient déjà à une zone. Si ce n’est pas le cas, un test est
 * réalisé pour savoir si la couleur du pixel est tolérée par la couleur de
 * référence de la zone courante. Si c’est le cas, la fonction `running_area`
 * est appelée sur ce pixel qui sera ajouté à la liste de pixels de la zone, et
 * le pixel référencera la zone courante comme étant la zone à laquelle il
 * appartient.
 *
 * \param[in] pix \ref Pixel courant
 * \param[in] img \ref Image traitée
 * \param[in] zt \ref Zone courante
 */
 void running_area(struct Pixel *pix, struct Image *img, struct Zone *zt);


/**
 * \brief Teste si la couleur du pixel est compatible avec la zone
 *
 * La fonction calcule la différence en pourcentage de la couleur du pixel
 * passé en arguments avec la couleur de référence de la zone passée en
 * arguments. Si le pourentage obtenu est inférieur ou égal à la tolérance
 * disponible en variable globale externe, alors la valeur `true` est renvoyée,
 * sinon la valeur `false` l’est.
 *
 * \param[in] pix \ref Pixel dont la couleur doit être testée
 * \param[in] zt \ref Zone dont la couleur référence doit être testée
 * \return Renvoie `true` si `pix` est compatible avec la couleur de `zt`,
 *         `false` sinon.
 */
 bool tolerated(struct Pixel *pix, struct Zone *zt);

/**
 * \brief Teste si le pixel appartient déjà à une zone
 *
 * Le pixel n’appartient à une zone que si son pointeur de zone contient une
 * valeur autre que `NULL`.
 *
 * \param[in] pix \ref Pixel à tester
 * \return Renvoie `true` si le pixel appartient déjà à une zone, `false` sinon
 */
 bool in_a_zone(struct Pixel *pix);

#endif
