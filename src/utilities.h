/**
 *   \file utilities.h
 *   \brief Fichier d'en-tête des fonctions d'utilité
 *
 *  Ce fichier d'en-tête contient des fonctions utilitaires, tels que des
 *  comparaisons de strings C, un affichage d'aide, et des fonctions de
 *  manipulation d'image, de pixels et de zones. La définition des fonctions
 *  peut être trouvée dans le fichier \ref utilities.c
 *
 */

#ifndef IMGTACHES_SRC_UTILITIES_H_
#define IMGTACHES_SRC_UTILITIES_H_

#include <GL/gl.h>
#include <stdbool.h>
#include <stdio.h>

/*****************************************************************************/
/*                             DEFINE DIRECTIVES                             */
/*****************************************************************************/

/**
 * `DEBUG` et `PDEB` sont des fonctions de débug qui sont compilés ou non
 *  suivant les paramètres de compilation.\n`DEBUG` permet d’activer ou de
 *  désactiver automatiquement des blocs de code de débug, `PDEB` spécialise
 *  `printf` dans l’affichage d’information dans les compilations de
 *  debug.\n
 *  Afin d’obtenir une compilation de débug, il suffit d’aller dans le
 *  dossier `./build` du projet et d’y taper la commande\n
 *  `cmake -DCMAKE_BUILD_TYPE=Debug ..`\n
 *  puis d’exécuter depuis le même dossier la commande `make`. Afin d’avoir la
 *  configuration de publication (release), il faut exécuter dans le même
 *  dossier la commande\n `cmake -DCMAKE_BUILD_TYPE=Release ..`\n dans le même
 *  dossier, puis d’exécuter `make`.
 */
#ifdef Debug
#define DEBUG if (1)
#define PDEB                                                                   \
  if (1)                                                                       \
  printf
#else
#define DEBUG if (0)
#define PDEB                                                                   \
  if (0)                                                                       \
  printf
#endif

/**
 * Nombre maximal de zones détectables et taille de `image->zones`
 */
#define NBCOLORSMAX 100000
/**
 * Nombre maximal de segments par zones
 */
#define NBSEGMAX 1000000

/*****************************************************************************/
/*                     FORWARD DECLARATIONS AND TYPEDEFS                     */
/*****************************************************************************/

struct Image;
typedef struct Image Image;
typedef struct Image *Image_t;
struct Pixel;
typedef struct Pixel Pixel;
typedef struct Pixel *Pixel_t;
struct Zone;
typedef struct Zone Zone;
typedef struct Zone *Zone_t;
struct Segment;
typedef struct Segment Segment;
typedef struct Segment *Segment_t;

/*****************************************************************************/
/*                             STRUCT DECLARATIONS                           */
/*****************************************************************************/

/**
 *  \brief Conteneur d'une image
 *
 *  Contient les données d'une image : sa taille, ses données, la liste de ses
 *  pixels et de ses zones.
 */
struct Image {
  unsigned long sizeX; /*!< Largeur de l'image (en pixels) */
  unsigned long sizeY; /*!< Hauteur de l'image (en pixels) */
  GLubyte *data;   /*!< Données brutes de l'image (vecteur unidimensionnel) */
  Pixel_t *pixels; /*!< Données raffinées de l'image, voir \ref Pixel */
  Zone_t zones[NBCOLORSMAX]; /*!< Vecteur de vecteurs de segments, regroupés
 *                                par couleur */
  unsigned long nb_zones;
};

/**
 *  \brief Conteneur d'un pixel
 *
 *  Conteneur de données raffinées d'une image, contient les informations
 *  relatives à un pixel. Ses valeurs RGB sont des pointeurs plutôt que des
 *  valeurs afin de pouvoir modifier les valeurs brutes de l'image directement
 *  plutôt que d'avoir à passer par des fonctions de conversion.
 */
struct Pixel {
  unsigned char *R;  /*!< Pointeur vers la valeur R du pixel */
  unsigned char *G;  /*!< Pointeur vers la valeur G du pixel */
  unsigned char *B;  /*!< Pointeur vers la valeur B du pixel */
  unsigned long x;   /*!< Positionnement en largeur dans l'image du pixel */
  unsigned long y;   /*!< Positionnement en hauteur dans l'image du pixel */
  bool processed;    /*!< Est-ce que le pixel a déjà été traité */
};

/**
 * \brief Conteneur d’une zone
 *
 * Conteneur de zone contenant les couleurs de base de la zone, un vecteur de
 * segments appartenant à ladite zone, et un compteur de segments réellement
 * stockés dans ledit vecteur.
 */
struct Zone {
  unsigned char R;  /*!< Valeur R du pixel d’origine du segment */
  unsigned char G;  /*!< Valeur G du pixel d’origine du segment */
  unsigned char B;  /*!< Valeur B du pixel d’origine du segment */
  Segment_t segment[NBSEGMAX]; /*!< Liste des segments de la zone */
  unsigned long nb_segment;
};

/**
 *  \brief Conteneur de segments de couleur
 *
 *  Contient un segment de couleur RGB sur la ligne y, allant de xg (extrême
 *  gauche) à xd (extrême droit).
 */
struct Segment {
  unsigned long y;  /*!< Ligne sur laquelle se trouve le segment */
  unsigned long xg; /*!< extrême gauche du segment */
  unsigned long xd; /*!< extrême droit du segment */
};

/*****************************************************************************/
/*                           FUNCTION DECLARATIONS                           */
/*****************************************************************************/

/**
 * \brief Retourne la valeur absolue du paramètre x
 * @param x Valeur dont on souhaite obtenir la valeur absolue
 * @return Retourne la valeur absolue du paramètre x
 */
int abs(int x);

/**
 * \brief Teste si la couleur du pixel est dans la zone de tolérance de la zone
 *
 * La fonction calcule une estimation de la différence de couleur entre celle
 * du pixel passé en argument et la couleur de référence de la zone. Si le
 * pourcentage obtenu est moindre que la tolérance globale, alors la fonction
 * renverra `true`, sinon elle renverra `false`.
 *
 * \param[in] pix \ref Pixel testé
 * \param[in] zt \ref Zone contenant la couleur de référence
 * \return Renvoie `true` si le pixel est toléré, `false` sinon
 */
bool tolerated(Pixel_t pix, Zone_t zt);

/**
 *  \brief Ajoute une zone à une image
 *
 *  Ajoute la zone passée en argument à l'image passée en argument. Cela
 *  incrémente le membre `nb_zones` de l’image de 1 et ajoute la zone après la
 *  dernière ajoutée, ou en première position s’il n’y en a pas d’autre qui
 *  furent rajoutées avant.
 *
 *  \param[in] zone \ref Zone à ajouter à l'image
 */
void img_add_zone(Zone_t zone);

void zone_add_segment(Zone_t zone, Segment_t segment);

/**
 *  \brief Créé un nouveau pixel
 *
 *  Créé un nouveau pixel référençant les valeurs RGB du vecteur `data` de la
 *  structure d'image. Ses coordonnées sont également initialisées à un
 *  équivalent à deux dimensions du tableau `data`. Il est automatiquement
 *  marqué comme non-traité (`processed=false`).
 *
 *  \param[in] R Pointeur vers la valeur R dans le tableau `data`
 *  \param[in] G Pointeur vers la valeur G dans le tableau `data`
 *  \param[in] B Pointeur vers la valeur B dans le tableau `data`
 *  \param[in] x Coordonnées en abscisse (équivalence)
 *  \param[in] y Coordonnées en ordonnée (équivalence)
 *  \return Renvoie un pointeur \ref Pixel_t vers un nouveau \ref Pixel
 */
Pixel_t new_pixel(unsigned char *R, unsigned char *G, unsigned char *B,
                  unsigned long x, unsigned long y);

/**
 *  \brief Retourne le pixel correspondant à img[y][x]
 *
 *  Retourne le pixel correspondant à img[y][x] dans le cas où les données
 *  seraient stockées dans un vecteur à deux dimensions (une pour la hauteur de
 *  l'image, une pour la longueur) au lieu du vecteur unidimensionnel réel.
 *
 *  \param[in] x Position en abscisse du pixel
 *  \param[in] y Position en ordonnée du pixel
 *  \return Pointeur sur le \ref Pixel voulu, `NULL` si les coordonnées sont
 *          hors image.
 */
Pixel_t pix_at_img(unsigned long x, unsigned long y);

/**
 *  \brief Créé et initialise une zone
 *
 *  Créé une nouvelle zone qui sera ajoutée à la variable globale `image`. Les
 *  valeurs RGB de la zone seront basées sur les valeurs RGB du \ref Pixel
 *  passé en argument. Tous les éléments du vecteur membre `segment` sont
 *  initialisés à `NULL`.
 *
 *  \param[in] pix Pixel de base de la zone
 *  \return Retourne un pointeur sur la nouvelle zone
 */
Zone_t new_zone(Pixel_t pix);

/**
 *  \brief Suppression sécurisé d'un objet \ref Image
 *
 *  Supprime la variable globale de l’image ainsi que toutes les zones mémoire
 *  dynamiquement allouées contenues en son sein.
 */
void delete();
/**
 *  \brief Affichage de l'aide
 *
 *  Affiche le texte d'aide à l'utilisation du programme, incluant les arguments
 *  possibles
 */
void printhelp();

#endif /* IMGTACHES_SRC_UTILITIES_H_ */
