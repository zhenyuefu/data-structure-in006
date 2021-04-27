#include "ListeChainee.h"

/* Retourne le noeud du reseau R correspondant aux coordonnees (x, y) en le
   cherchant directement dans R->noeuds. Si un tel noeud n'existe pas, la
   fonction se chargera de le creer, de l'ajouter au reseau R avant de le
   retourner  */
Noeud *rechercheCreeNoeudListe(Reseau *R, double x, double y) {
  CellNoeud *cell_node = R->noeuds;
  while (cell_node != NULL) {
    Noeud *node = cell_node->nd;
    if (node->x == x && node->y == y) return node;
    cell_node = cell_node->suiv;
  }
  Noeud *new_node = malloc(sizeof(Noeud));
  new_node->num = R->nbNoeuds + 1;
  new_node->x = x;
  new_node->y = y;
  new_node->voisins = NULL;
  CellNoeud *new_cell = malloc(sizeof(CellNoeud));
  new_cell->nd = new_node;
  new_cell->suiv = R->noeuds;
  R->noeuds = new_cell;
  R->nbNoeuds++;
  return new_node;
}

/* Reconstruit et retourne le reseau a partir des chaines C */
Reseau *reconstitueReseauListe(Chaines *C) {
  Reseau *R = malloc(sizeof(Reseau));
  R->nbNoeuds = 0;
  R->gamma = C->gamma;
  R->noeuds = NULL;
  R->commodites = NULL;
  Noeud *node, *node_pre, *node_first;
  CellChaine *list_chaine = C->chaines;
  while (list_chaine != NULL) {
    CellPoint *list_point = list_chaine->points;
    node_pre = NULL;
    node_first = rechercheCreeNoeudListe(R, list_point->x, list_point->y);
    while (list_point != NULL) {
      node = rechercheCreeNoeudListe(R, list_point->x, list_point->y);
      if (node_pre != NULL) {
        ajoute_voisins(node_pre, node);
      }
      node_pre = node;
      list_point = list_point->suiv;
    }
    ajoute_commodites(R, node_first, node);
    list_chaine = list_chaine->suiv;
  }
  return R;
}