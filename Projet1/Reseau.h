#ifndef __RESEAU_H__
#define __RESEAU_H__
#include "Chaine.h"

typedef struct noeud Noeud;

#include "Hachage.h"
/* Liste chainee de noeuds (pour la liste des noeuds du reseau ET les listes des
 * voisins de chaque noeud) */
typedef struct cellnoeud {
  Noeud *nd;              /* Pointeur vers le noeud stock\'e */
  struct cellnoeud *suiv; /* Cellule suivante dans la liste */
} CellNoeud;

/* Noeud du reseau */
struct noeud {
  int num;            /* Numero du noeud */
  double x, y;        /* Coordonnees du noeud*/
  CellNoeud *voisins; /* Liste des voisins du noeud */
};

/* Liste chainee de commodites */
typedef struct cellCommodite {
  Noeud *extrA, *extrB;       /* Noeuds aux extremites de la commodite */
  struct cellCommodite *suiv; /* Cellule suivante dans la liste */
} CellCommodite;

/* Un reseau */
typedef struct {
  int nbNoeuds;              /* Nombre de noeuds du reseau */
  int gamma;                 /* Nombre maximal de fibres par cable */
  CellNoeud *noeuds;         /* Liste des noeuds du reseau */
  CellCommodite *commodites; /* Liste des commodites a relier */
  TableHachage *H;
} Reseau;

Noeud *rechercheCreeNoeudListe(Reseau *R, double x, double y);
Noeud *rechercheCreeNoeudHachage(Reseau *R, TableHachage *H, double x,
                                 double y);
Reseau *reconstitueReseauListe(Chaines *C);
Reseau *reconstitueReseauHash(Chaines *C, int size);
void ecrireReseau(Reseau *R, FILE *f);
int nbLiaisons(Reseau *R);
int nbCommodites(Reseau *R);
int countNodes(CellNoeud *list_node);
void ajoute_voisins(Noeud *node1, Noeud *node2);
void ajoute_commodites(Reseau *R, Noeud *node1, Noeud *node2);
void afficheReseauSVG(Reseau *R, char *nomInstance);
#endif
