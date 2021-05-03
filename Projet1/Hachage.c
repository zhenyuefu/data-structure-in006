#include "Hachage.h"

#include <stdlib.h>
#include <string.h>

Noeud *rechercheCreeNoeudHachage(Reseau *R, TableHachage *H, double x,
                                 double y) {
  long long clef = functionClef(x, y);
  int hash = functionHachage(clef, H->size);
  NodeHachage *node_list = H->nodes[hash];
  while (node_list != NULL) {
    if (node_list->node->x == x && node_list->node->y == y) {
      return node_list->node;
    }
    node_list = node_list->suiv;
  }
  Noeud *new_node = malloc(sizeof(Noeud));
  new_node->num = R->nbNoeuds + 1;
  new_node->x = x;
  new_node->y = y;
  new_node->voisins = NULL;
  NodeHachage *new_node_hachage = malloc(sizeof(NodeHachage));
  new_node_hachage->node = new_node;
  new_node_hachage->suiv = H->nodes[hash];
  H->nodes[hash] = new_node_hachage;
  H->nb_elements++;
  CellNoeud *new_cell = malloc(sizeof(CellNoeud));
  new_cell->nd = new_node;
  new_cell->suiv = R->noeuds;
  R->noeuds = new_cell;
  R->nbNoeuds++;
  return new_node;
}

Reseau *reconstitueReseauHachage(Chaines *C, int size) {
  Reseau *R = malloc(sizeof(Reseau));
  R->nbNoeuds = 0;
  R->gamma = C->gamma;
  R->noeuds = NULL;
  R->commodites = NULL;
  TableHachage *H = malloc(sizeof(TableHachage));
  H->size = size;
  H->nb_elements = 0;
  H->nodes = malloc(sizeof(NodeHachage *) * H->size);
  memset(H->nodes, 0, sizeof(NodeHachage *) * H->size);
  Noeud *node, *node_pre, *node_first;
  CellChaine *list_chaine = C->chaines;
  while (list_chaine != NULL) {
    CellPoint *list_point = list_chaine->points;
    node_pre = NULL;
    node_first = rechercheCreeNoeudHachage(R, H, list_point->x, list_point->y);
    while (list_point != NULL) {
      node = rechercheCreeNoeudHachage(R, H, list_point->x, list_point->y);
      if (node_pre != NULL) {
        ajoute_voisins(node_pre, node);
      }
      node_pre = node;
      list_point = list_point->suiv;
    }
    ajoute_commodites(R, node_first, node);
    list_chaine = list_chaine->suiv;
  }
  liberer_hash(H);
  return R;
}

void liberer_node(NodeHachage *n) {
  while (n) {
    NodeHachage *tmp = n->suiv;
    free(n);
    n = tmp;
  }
}

void liberer_hash(TableHachage *hash) {
  for (int i = 0; i < hash->size; i++) {
    if (hash->nodes[i]) liberer_node(hash->nodes[i]);
  }
  free(hash->nodes);
  free(hash);
}