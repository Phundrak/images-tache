/**
 *   \file interface.h
 *   \brief Fichier d'en-tête des fonctions d'interface graphique
 *
 *  Fichier de déclaration des fonctions d'interface graphique pour OpenGL. Leur
 *  implémentation se trouve dans \ref interface.c
 */

#ifndef IMGTACHES_SRC_INTERFACE_H_
#define IMGTACHES_SRC_INTERFACE_H_

#include "utilities.h"
#include <GL/glu.h>
#include <GL/glut.h>

/**
 *  \brief Initialisation de l’image
 *
 *  Initialisation de l’image, création de sa structure. Le fichier ouvert sera
 *  celui désigné par le nom de fichier passé en argument avec l’argument
 *  `s`.\nSi l’initialisation se déroule correctement, alors la fonction renvoie
 *  0 ; sinon elle renvoie -1 après avoir affiché un message d'erreur.
 *
 *  \param s Nom du fichier image à ouvrir
 *  \return Retourne -1 en cas d'échec, 0 en cas de succès
 */
int Init(char *s);

#endif /* IMGTACHES_SRC_INTERFACE_H_ */
