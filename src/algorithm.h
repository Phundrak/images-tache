#ifndef IMGTACHES_SRC_ALGORITHM_H_
#define IMGTACHES_SRC_ALGORITHM_H_

#include "utilities.h"

/**
 * \brief créé les segments d’une zone
 *
 * Créé un segment horizontal sur lequel se situe `pix` contenant de façon
 * continue la couleur référence contenue dans `zone`. Ce segment est ensuite
 * ajouté à `zone`. Chacun des pixels de ce segment sont marqués comme ayant
 * été traités. Puis pour chaque pixel de ce segment, si un pixel se situant
 * en dessus de ce dernier existe (que l’on n’est pas sortis de l’image), que
 * le pixel n’a pas encore été traité (qu’ils n’appartiennent à aucun segment
 * existant) et que la couleur du pixel est dans la zone de tolérance de la
 * couleur référence de la zone, alors on appelle `generate_segment` sur ce
 * pixel avec la zone courante. Cette dernière étape est ensuite répétée sur
 * les pixels en dessous de chaque pixel du segment courant.
 *
 * \param[out] zone \ref Zone à laquelle on ajoute les \ref Segment, contenant
 *                  la couleur référence
 * \param[in] pix \ref Pixel à partir duquel le segment courant est créé
 */
void generate_segment(Zone_t zone, Pixel_t pix);

/**
 * \brief Créé une zone à partir du pixel courant
 *
 * Créé une zone vierge contenant pour couleurs de référence la couleur du
 * pixel courant. La zone est ensuite ajoutée à la variable globale de l’image.
 * Le pixel n’est pas modifié au sein de cette fonction. À partir de ce pixel,
 * la fonction `generate_segment` est appelée.
 *
 * \param[in] pix \ref Pixel de référence
 */
void generate_zone(Pixel_t pix);

/**
 * \brief Pour chaque pixel non-traité, on génère une zone.
 *
 * Via l’appel de la fonction `generate_zone`, pour chaque pixel détecté comme
 * étant non-traité on génère une zone à partir de celui-ci.
 */
void make_zones();

/**
 * \brief Change les couleurs d’un pixel suivant les couleurs RGB passées en
 *        argument
 *
 * \param pix \ref Pixel dont la couleur doit être changée
 * \param R Nouvelle valeur pour le sous-pixel rouge
 * \param G Nouvelle valeur pour le sous-pixel vert
 * \param B Nouvelle valeur pour le sous-pixel bleu
 */
void change_color(Pixel_t pix, unsigned char R, unsigned char G,
                  unsigned char B);

/**
 * \brief Inverse la couleur du pixel passé en argument
 * \param pix \ref Pixel dont on doit inverser les couleurs
 */
void invert_color(Pixel_t pix);

/**
 * \brief Créé les bordures des zones
 *
 * Pour chaque segment de chaque zone, les deux pixels en extrémité de segment
 * voient leur couleur inversée.
 */
void black_border();

#endif /* IMGTACHES_SRC_ALGORITHM_H_ */
