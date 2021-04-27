#ifndef __ARBRE_QUATERNAIRE_H__
#define __ARBRE_QUATERNAIRE_H__

#include <float.h>
#include "Reseau.h"
/* Arbre quaternaire contenant les noeuds du reseau */
typedef struct arbreQuat {
    double xc, yc;          /* Coordonnees du centre de la cellule */
    double coteX;           /* Longueur de la cellule */
    double coteY;           /* Hauteur de la cellule */
    Noeud* noeud;           /* Pointeur vers le noeud du reseau */
    struct arbreQuat *so;   /* Sous-arbre sud-ouest, pour x < xc et y < yc */
    struct arbreQuat *se;   /* Sous-arbre sud-est, pour x >= xc et y < yc */
    struct arbreQuat *no;   /* Sous-arbre nord-ouest, pour x < xc et y >= yc */
    struct arbreQuat *ne;   /* Sous-arbre nord-est, pour x >= xc et y >= yc */
} ArbreQuat;


/* Stocke (par adresse) dans xmin, ymin, xmax, ymax, les coordonnees minimales 
   et maximales des points constituant les differentes chaines du reseau  */
void chaineCoordMinMax(Chaines* C, double *xmin, double *ymin, double *xmax, double *ymax);

/* Cree et retourne  une cellule de l'arbre quaternaire de centre (xc, yc) de 
   longueur coteX et de hauteur coteY; les sous-arbres sont initialises a NULL*/
ArbreQuat* creerArbreQuat(double xc, double yc, double coteX, double coteY);

/* Insere le noeud n dans le sous-arbre dont l'adresse de la racine est stockee dans une
   variable dont l'adresse a. Le noeud-racine de cet sous-arbre ayant pour parent le noeud
   d'adresse parent. */
void insererNoeudArbre(Noeud* n, ArbreQuat** a, ArbreQuat* parent);

/* Retourne le noeud du reseau R correspondant aux coordonnees (x, y) dans l'arbre quaternaire.
   SI un tel noeud n'existe pas, la fonction se chargera de le creer, de l'ajouter a l'arbre et
   de le retourner  */
Noeud* rechercheCreeNoeudArbre(Reseau* R, ArbreQuat**a, ArbreQuat* parent, double x, double y);

/* Reconstruit et retourne le reseau a partir des chaines C en utilisant une SDA Arbre quaternaire */
Reseau* reconstitueReseauArbre(Chaines* C);

/* Libere la memoire occupee par l'arbre quaternaire A */ 
void libererArbre(ArbreQuat* A);

#endif