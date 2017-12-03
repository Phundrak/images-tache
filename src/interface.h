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

#define ESCAPE 27
#define SHIFTQ 81
#define LOWQ 113

/**
 *  \brief Fonction OpenGL gérant le clavier
 *  \param[in] key Touche pressée lors de l’exécution de la fonction
 *  \param[in] x Position horizontale de la souris
 *  \param[in] y Position verticale de la souris
 */
void Keyboard(unsigned char key, int x, int y);

/**
 *  \brief Fonction OpenGL gérant les interactions souris
 *  \param[in] button Bouton cliqué de la souris
 *  \param[in] state État du clic
 *  \param[in] x Position horizontale de la souris
 *  \param[in] y Position verticale de la souris
 */
void Mouse(int button, int state, int x, int y);

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

/**
 *  \brief Rafraîchissement de l'affichage
 *
 *  Renvoie 0 si le rafraîchissement de l’affichage s’est correctement effectué
 *
 *  \return Retourne 0 en cas de succès
 */
int ReInit();

/**
 *  \brief Affichage de l’image
 */
void Display();

#endif /* IMGTACHES_SRC_INTERFACE_H_ */
