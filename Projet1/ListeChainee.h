#ifndef __LISTE_CHAINEE_H__
#define __LISTE_CHAINEE_H__

#include "Reseau.h"

/* Retourne le noeud du reseau R correspondant aux coordonnees (x, y) en le cherchant directement dans R->noeuds.
   Si un tel noeud n'existe pas, la fonction se chargera de le creer, de l'ajouter au reseau R avant de le retourner  */
Noeud* rechercheCreeNoeudListe(Reseau *R, double x, double y);

/* Reconstruit et retourne le reseau a partir des chaines C */
Reseau* reconstitueReseauListe(Chaines *C);

#endif