/**
 *   \file ppm.h
 *   \brief Fichier d'en-tête pour les fonctions de manipulation d'images ppm
 *
 *  En-tête contenant la déclaration de fonctions de lecture et d'écriture de
 *  fichiers au format ppm. La définition des fonction se trouve dans \ref ppm.c
 *
 */

#ifndef IMGTACHES_SRC_PPM_H_
#define IMGTACHES_SRC_PPM_H_

#include "utilities.h"

/**
 *  \brief Ouverture et lecture de l’image d’entrée
 *
 *  Ouvre le fichier image avec son nom de fichier passé par le paramètre
 *  `filename` et charge ses informations et données dans l'objet `img` dans
 *  lequel les données et l'image seront manipulables. Retourne la valeur 1 en
 *  cas de succès.
 *
 *  \param[in] filename Nom du fichier image à ouvrir
 *  \param[out] img Objet \ref Image manipulable
 *  \return Retourne 1 en cas de succès
 */
int ImageLoad_PPM(char *filename, Image *img);

/**
 *  \brief Ouverture et écriture de l'image de sortie
 *
 *  Ouvre le fichier image avec son nom de fichier passé par le paramètre
 *  `filename` et y écrit les informations trouvées dans l’objet `img`.
 *
 *  \param[in] filename Nom du fichier image à ouvrir
 *  \param[in] img Objet \ref Image à écrire
 */
void imagesave_PPM(char *filename, Image *img);

#endif /* IMGTACHES_SRC_PPM_H_ */
