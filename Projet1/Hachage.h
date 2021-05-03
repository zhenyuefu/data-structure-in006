#ifndef __HACHAGE_H__
#define __HACHAGE_H__
#include "Reseau.h"

#define functionClef(X, Y) Y + ((X + Y) * (X + Y + 1)/2 )

#define GOLDEN ((sqrt(5) - 1) / 2.0)

#define functionHachage(x, M) floor( (M) * ( (x * GOLDEN) - floor(x * GOLDEN) ) ) 

typedef struct tableHachage TableHachage;
typedef struct nodeHachage NodeHachage;

struct nodeHachage {
  Noeud *node;
  NodeHachage *suiv;
};

struct tableHachage {
  int size;
  int nb_elements;
  NodeHachage **nodes;
};

/* Reconstruit et retourne le reseau a partir des chaines C en utilisant une SDA Table de Hachage de taille size */
Reseau *reconstitueReseauHachage(Chaines *C, int size);

/* Retourne le noeud du reseau R correspondant aux coordonnees (x, y) en le cherchant dans la table de hachage H.
   Si un tel noeud n'existe pas, la fonction se chargera de le creer, de l'ajouter a la table de hachage et au 
   reseau R avant de le retourner  */
Noeud *rechercheCreeNoeudHachage(Reseau *R, TableHachage *H, double x,
                                 double y);
void liberer_hash(TableHachage *hash);

#endif