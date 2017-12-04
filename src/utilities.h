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
  Zone_t *zones;   /*!< Liste des zones de l'image, voir \ref Zone */
  unsigned long nb_zones; /*!< Nombre de zones dans le membre `zones` */
  unsigned long capacity; /*!< Capacité de stockage du membre `zones` */
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
  unsigned char *R; /*!< Pointeur vers la valeur R du pixel */
  unsigned char *G; /*!< Pointeur vers la valeur G du pixel */
  unsigned char *B; /*!< Pointeur vers la valeur B du pixel */
  unsigned long x;  /*!< Positionnement en largeur dans l'image du pixel */
  unsigned long y;  /*!< Positionnement en hauteur dans l'image du pixel */
  Zone_t zone;      /*!< \ref Zone d'appartenance du pixel */
};

/**
 *  \brief Conteneur pour une zone d'image
 *
 *  Conteneur de zone d'image, contenant la couleur du pixel d'origine et la
 *  liste des pixels appartenant à la zone.
 */
struct Zone {
  char R;                  /*!< Valeur R du pixel d'origine */
  char G;                  /*!< Valeur G du pixel d'origine */
  char B;                  /*!< Valeur B du pixel d'origine */
  Pixel_t *pixels;         /*!< Liste des pixels de la zone */
  unsigned long nb_pixels; /*!< Nombre de pixels dans la zone */
  unsigned long capacity;  /*!< Capacité du membre `nb_pixels` */
};

/*****************************************************************************/
/*                           FUNCTION DECLARATIONS                           */
/*****************************************************************************/

/**
 *  \brief Affichage de l'aide
 *
 *  Affiche le texte d'aide à l'utilisation du programme, incluant les arguments
 *  possibles
 */
void printhelp();

/**
 *  \brief Comparateur de chaîne de caractères
 *
 *  Compare deux chaînes de caractères C (`char*`). La fonction ne
 *  modifie pas les deux chaînes de caractères.
 *
 *  \param[in] str1 Première chaîne de caractères
 *  \param[in] str2 Seconde chaîne de caractères
 *  \return Renvoie `true` si les deux chaînes de caractères sont identiques,
 *          `false` sinon
 */
bool strcomp(char *str1, char *str2);

int abs(int x);

/**
 *  \brief Ajoute une zone à une image
 *
 *  Ajoute la zone passée en argument à l'image passée en argument. Si
 *  nécessaire, le vecteur contenant les pointeurs de zones verra sa capacité
 *  doublée.
 *
 *  \param[out] img \ref Image à laquelle ajouter la zone
 *  \param[in] zone \ref Zone à ajouter à l'image
 */
void img_add_zone(Image_t img, Zone_t zone);

/**
 *  \brief Créé et initialise une zone
 *
 *  Créé une nouvelle zone qui sera ajoutée à la structure \ref Image passée en
 *  premier argument. Les valeurs RGB de la zone seront basées sur les valeurs
 *  RGB du \ref Pixel. La zone sera également définie comme étant la zone
 *  d'appartenance du pixel. La fonction renvoie un pointeur sur la zone
 *  nouvellement créée.
 *
 *  \param[out] img Image à laquelle la zone doit être ajoutée
 *  \param[in] pix Pixel de base de la zone
 *  \return Retourne un pointeur sur la nouvelle zone
 */
Zone_t new_zone(Image_t img, Pixel_t pix);

/**
 *  \brief Ajoute à une zone un pixel
 *
 *  Ajoute à la \ref Zone passée en argument le \ref Pixel passé en argument. La
 *  zone sera également définie comme étant la zone du pixel.
 *
 *  \param[out] zone \ref Zone à laquelle le pixel sera ajouté
 *  \param[in] pix \ref Pixel ajouté à la zone
 */
void zone_add_pix(Zone_t zone, Pixel_t pix);

/**
 *  \brief Retourne le pixel correspondant à img[y][x]
 *
 *  Retourne le pixel correspondant à img[y][x] dans le cas où les données
 *  seraient stockées dans un vecteur à deux dimensions (une pour la hauteur de
 *  l'image, une pour la longueur) au lieu du vecteur unidimensionnel réel.
 *
 *  \param[in] img \ref Image dans laquelle nous souhaitons récupérer un pixel.
 *  \param[in] x Position en abscisse du pixel
 *  \param[in] y Position en ordonnée du pixel
 *  \return Pointeur sur le \ref Pixel voulu, `NULL` si les dimensions sont hors
 *          image.
 */
Pixel_t pix_at_img(Image_t img, unsigned long x, unsigned long y);

/**
 *  \brief Créé un nouveau pixel
 *
 *  Créé un nouveau pixel référençant les valeurs RGB du vecteur `data` de la
 *  structure d'image. Ses coordonnées sont également initialisées à un
 *  équivalent à deux dimensions du tableau `data`, et son pointeur de zone est
 *  initialisé à `NULL`.
 *
 *  \param[in] R Pointeur vers la valeur R dans le tableau `data`
 *  \param[in] G Pointeur vers la valeur G dans le tableau `data`
 *  \param[in] B Pointeur vers la valeur B dans le tableau `data`
 *  \param[in] x Coordonnées en abscisse (équivalence)
 *  \param[in] y Coordonnées en ordonnée (équivalence)
 *  \return Renvoie un pointeur vers un nouveau \ref Pixel
 */
Pixel_t new_pixel(unsigned char *R, unsigned char *G, unsigned char *B,
                  unsigned long x, unsigned long y);

/**
 *  \brief Suppression sécurisé d'un objet \ref Image
 *
 *  Supprime un objet \ref Image ainsi que tous les objets référencés par
 *  pointeurs au sein de l'objet.
 *
 *  \param[in] img Objet \ref Image à supprimer.
 */
void delete(Image_t img);

#endif /* IMGTACHES_SRC_UTILITIES_H_ */
