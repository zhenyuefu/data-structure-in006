#include "ArbreQuat.h"

#include <stdio.h>
#include <stdlib.h>

void chaineCoordMinMax(Chaines* C, double* xmin, double* ymin, double* xmax,
                       double* ymax) {
  CellChaine* chaine = C->chaines;
  if (chaine != NULL && chaine->points != NULL) {
    *xmin = chaine->points->x;
    *xmax = chaine->points->x;
    *ymin = chaine->points->y;
    *xmax = chaine->points->y;
  } else {
    puts("Error: Chaines have no points");
  }
  while (chaine != NULL) {
    CellPoint* p = chaine->points;
    while (p != NULL) {
      if (*xmin > p->x) *xmin = p->x;
      if (*xmax < p->x) *xmax = p->x;
      if (*ymin > p->y) *ymin = p->y;
      if (*ymax < p->y) *ymax = p->y;
      p = p->suiv;
    }
    chaine = chaine->suiv;
  }
}

ArbreQuat* creerArbreQuat(double xc, double yc, double coteX, double coteY) {
  ArbreQuat* arbre = malloc(sizeof(ArbreQuat));
  arbre->xc = xc;
  arbre->yc = yc;
  arbre->coteX = coteX;
  arbre->coteY = coteY;
  arbre->ne = NULL;
  arbre->no = NULL;
  arbre->se = NULL;
  arbre->so = NULL;
  arbre->noeud = NULL;
  return arbre;
}

void insererNoeudArbre(Noeud* n, ArbreQuat** a, ArbreQuat* parent) {
  if (*a == NULL) {
    double coteX = parent->coteX / 2;
    double coteY = parent->coteY / 2;
    double xc, yc;
    if (n->x < parent->xc) {
      if (n->y < parent->yc) {
        xc = parent->xc - (coteX / 2);
        yc = parent->yc - (coteY / 2);
      } else {
        xc = parent->xc - (coteX / 2);
        yc = parent->yc + (coteY / 2);
      }
    } else if (n->y < parent->yc) {
      xc = parent->xc + (coteX / 2);
      yc = parent->yc - (coteY / 2);
    } else {
      xc = parent->xc + (coteX / 2);
      yc = parent->yc + (coteY / 2);
    }
    *a = creerArbreQuat(xc, yc, coteX, coteY);
    (*a)->noeud = n;
    return;
  }
  if ((*a)->noeud != NULL) {
    if ((*a)->noeud->x < (*a)->xc) {
      if ((*a)->noeud->y < (*a)->yc) {
        insererNoeudArbre((*a)->noeud, &(*a)->so, *a);
      } else {
        insererNoeudArbre((*a)->noeud, &(*a)->no, *a);
      }
    } else if ((*a)->noeud->y < (*a)->yc) {
      insererNoeudArbre((*a)->noeud, &(*a)->se, *a);
    } else {
      insererNoeudArbre((*a)->noeud, &(*a)->ne, *a);
    }
    (*a)->noeud = NULL;
    if (n->x < (*a)->xc) {
      if (n->y < (*a)->yc) {
        insererNoeudArbre(n, &(*a)->so, *a);
      } else {
        insererNoeudArbre(n, &(*a)->no, *a);
      }
    } else if (n->y < (*a)->yc) {
      insererNoeudArbre(n, &(*a)->se, *a);
    } else {
      insererNoeudArbre(n, &(*a)->ne, *a);
    }
    return;
  }
  if (n->x < (*a)->xc) {
    if (n->y < (*a)->yc) {
      insererNoeudArbre(n, &(*a)->so, *a);
    } else {
      insererNoeudArbre(n, &(*a)->no, *a);
    }
  } else if (n->y < (*a)->yc) {
    insererNoeudArbre(n, &(*a)->se, *a);
  } else {
    insererNoeudArbre(n, &(*a)->ne, *a);
  }
}

Noeud* rechercheCreeNoeudArbre(Reseau* R, ArbreQuat** a, ArbreQuat* parent,
                               double x, double y) {
  if (*a == NULL) {
    Noeud* new_node = malloc(sizeof(Noeud));
    new_node->num = R->nbNoeuds + 1;
    new_node->x = x;
    new_node->y = y;
    new_node->voisins = NULL;
    insererNoeudArbre(new_node, a, parent);
    CellNoeud* new_cell = malloc(sizeof(CellNoeud));
    new_cell->nd = new_node;
    new_cell->suiv = R->noeuds;
    R->noeuds = new_cell;
    R->nbNoeuds++;
    return new_node;
  }
  if ((*a)->noeud != NULL) {
    if ((*a)->noeud->x == x && (*a)->noeud->y == y) return (*a)->noeud;
    Noeud* new_node = malloc(sizeof(Noeud));
    new_node->num = R->nbNoeuds + 1;
    new_node->x = x;
    new_node->y = y;
    new_node->voisins = NULL;
    insererNoeudArbre(new_node, a, parent);
    CellNoeud* new_cell = malloc(sizeof(CellNoeud));
    new_cell->nd = new_node;
    new_cell->suiv = R->noeuds;
    R->noeuds = new_cell;
    R->nbNoeuds++;
    return new_node;
  }

  if (x < (*a)->xc) {
    if (y < (*a)->yc) {
      return rechercheCreeNoeudArbre(R, &(*a)->so, *a, x, y);
    } else {
      return rechercheCreeNoeudArbre(R, &(*a)->no, *a, x, y);
    }
  } else if (y < (*a)->yc) {
    return rechercheCreeNoeudArbre(R, &(*a)->se, *a, x, y);
  } else {
    return rechercheCreeNoeudArbre(R, &(*a)->ne, *a, x, y);
  }
}

Reseau* reconstitueReseauArbre(Chaines* C) {
  Reseau* R = malloc(sizeof(Reseau));
  R->nbNoeuds = 0;
  R->gamma = C->gamma;
  R->noeuds = NULL;
  R->commodites = NULL;
  double xmin, ymin, xmax, ymax;
  chaineCoordMinMax(C, &xmin, &ymin, &xmax, &ymax);
  double coteX = xmax - xmin;
  double coteY = ymax - ymin;
  double xc = (xmax + xmin) / 2;
  double yc = (ymax + ymin) / 2;
  ArbreQuat* root = creerArbreQuat(xc, yc, coteX, coteY);
  Noeud *node, *node_pre, *node_first;
  CellChaine* list_chaine = C->chaines;
  while (list_chaine != NULL) {
    CellPoint* list_point = list_chaine->points;
    node_pre = NULL;
    if (list_point->x < root->xc) {
      if (list_point->y < root->yc) {
        node_first = rechercheCreeNoeudArbre(R, &root->so, root, list_point->x,
                                             list_point->y);
      } else {
        node_first = rechercheCreeNoeudArbre(R, &root->no, root, list_point->x,
                                             list_point->y);
      }
    } else if (list_point->y < root->yc) {
      node_first = rechercheCreeNoeudArbre(R, &root->se, root, list_point->x,
                                           list_point->y);
    } else {
      node_first = rechercheCreeNoeudArbre(R, &root->ne, root, list_point->x,
                                           list_point->y);
    }
    while (list_point != NULL) {
      if (list_point->x < root->xc) {
        if (list_point->y < root->yc) {
          node = rechercheCreeNoeudArbre(R, &root->so, root, list_point->x,
                                         list_point->y);
        } else {
          node = rechercheCreeNoeudArbre(R, &root->no, root, list_point->x,
                                         list_point->y);
        }
      } else if (list_point->y < root->yc) {
        node = rechercheCreeNoeudArbre(R, &root->se, root, list_point->x,
                                       list_point->y);
      } else {
        node = rechercheCreeNoeudArbre(R, &root->ne, root, list_point->x,
                                       list_point->y);
      }
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