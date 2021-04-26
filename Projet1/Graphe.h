#ifndef __GRAPHE_H__
#define __GRAPHE_H__
#include <stdio.h>
#include <stdlib.h>

#include "Reseau.h"
#include "Struct_Liste.h"

typedef struct {
  int u, v; /* Numeros des sommets extremité */
} Arete;

typedef struct cellule_arete {
  Arete* a; /* pointeur sur l'arete */
  struct cellule_arete *usuiv, *vsuiv;
} Cellule_arete;

typedef struct {
  int num; /* Numero du sommet (le meme que dans T_som) */
  double x, y;
  Cellule_arete* L_voisin; /* Liste chainee des voisins */
} Sommet;

typedef struct {
  int e1, e2; /* Les deux extremites de la commodite */
} Commod;

typedef struct {
  int nbsom;      /* Nombre de sommets */
  Sommet** T_som; /* Tableau de pointeurs sur sommets */
  int gamma;
  int nbcommod;     /* Nombre de commodites */
  Commod* T_commod; /* Tableau des commodites */
} Graphe;

/* Creer le graphe correspondant au reseau R */
Graphe* creerGraphe(Reseau* R);

/* Retourne la distance entre les sommets-noeuds u et v dans le graphe G.
   (Cette version de la fonction n'est pas utilisee dans reorganiseReseau)*/
int distance_sans_prec(Graphe* G, int u, int v);

/* Retourne une liste chainee d'entier contenant les sommets-noeuds de la plus
   courte chaine
   entre u et v dans le graphe G. Cette fonction est utilisee dans
   reorganiseReseau */
ListeEntier distance_avec_prec(Graphe* G, int u, int v);

/* Reorganise le Reseau R tel qu'indique dans la quesiton 7.4 */
int reorganiseReseau(Reseau* R);

/* Libere integralement la memoire occupee par le graphe G */
void libererGraphe(Graphe* G);

void ecrireGraph(Graphe* g, FILE* f);

#endif
