#include "Reseau.h"

#include <stdlib.h>

#include "SVGwriter.h"

void ajoute_voisins(Noeud *node1, Noeud *node2) {
  CellNoeud *voisins = node1->voisins;
  while (voisins != NULL) {
    if (voisins->nd == node2) return;
    voisins = voisins->suiv;
  }
  CellNoeud *list_node1 = malloc(sizeof(CellNoeud));
  list_node1->nd = node2;
  list_node1->suiv = node1->voisins;
  CellNoeud *list_node2 = malloc(sizeof(CellNoeud));
  list_node2->nd = node1;
  list_node2->suiv = node2->voisins;
  node1->voisins = list_node1;
  node2->voisins = list_node2;
}

void ajoute_commodites(Reseau *R, Noeud *node1, Noeud *node2) {
  CellCommodite *commodite = malloc(sizeof(CellCommodite));
  commodite->extrA = node1;
  commodite->extrB = node2;
  commodite->suiv = R->commodites;
  R->commodites = commodite;
}

void afficheReseauSVG(Reseau *R, char *nomInstance) {
  CellNoeud *courN, *courv;
  SVGwriter svg;
  double maxx = 0, maxy = 0, minx = 1e6, miny = 1e6;

  courN = R->noeuds;
  while (courN != NULL) {
    if (maxx < courN->nd->x) maxx = courN->nd->x;
    if (maxy < courN->nd->y) maxy = courN->nd->y;
    if (minx > courN->nd->x) minx = courN->nd->x;
    if (miny > courN->nd->y) miny = courN->nd->y;
    courN = courN->suiv;
  }
  SVGinit(&svg, nomInstance, 500, 500);
  courN = R->noeuds;
  while (courN != NULL) {
    SVGpoint(&svg, 500 * (courN->nd->x - minx) / (maxx - minx),
             500 * (courN->nd->y - miny) / (maxy - miny));
    courv = courN->nd->voisins;
    while (courv != NULL) {
      if (courv->nd->num < courN->nd->num)
        SVGline(&svg, 500 * (courv->nd->x - minx) / (maxx - minx),
                500 * (courv->nd->y - miny) / (maxy - miny),
                500 * (courN->nd->x - minx) / (maxx - minx),
                500 * (courN->nd->y - miny) / (maxy - miny));
      courv = courv->suiv;
    }
    courN = courN->suiv;
  }
  SVGfinalize(&svg);
}

int nbLiaisons(Reseau *R) {
  int nb = 0;
  CellNoeud *list_node = R->noeuds;
  while (list_node != NULL) {
    Noeud *node = list_node->nd;
    nb += countNodes(node->voisins);
    list_node = list_node->suiv;
  }
  nb /= 2;
  return nb;
}

int countNodes(CellNoeud *list_node) {
  int nb = 0;
  while (list_node != NULL) {
    nb++;
    list_node = list_node->suiv;
  }
  return nb;
}

int nbCommodites(Reseau *R) {
  CellCommodite *list_commodite = R->commodites;
  int nb = 0;
  while (list_commodite != NULL) {
    nb++;
    list_commodite = list_commodite->suiv;
  }
  return nb;
}

void ecrireReseau(Reseau *R, FILE *f) {
  fprintf(f, "nbNoeud = %d\n", R->nbNoeuds);
  fprintf(f, "nbLiaison = %d\n", nbLiaisons(R));
  fprintf(f, "nbCom = %d\n", nbCommodites(R));
  fprintf(f, "Gamma = %d\n\n", R->gamma);

  for (CellNoeud *cell_noeud = R->noeuds; cell_noeud;
       cell_noeud = cell_noeud->suiv)
    fprintf(f, "v %d %.2f %.2f\n", cell_noeud->nd->num, cell_noeud->nd->x,
            cell_noeud->nd->y);

  fprintf(f, "\n");

  for (CellNoeud *cell_noeud = R->noeuds; cell_noeud;
       cell_noeud = cell_noeud->suiv)
    for (CellNoeud *voisin = cell_noeud->nd->voisins; voisin;
         voisin = voisin->suiv)
      if (voisin->nd->num > cell_noeud->nd->num)
        fprintf(f, "l %d %d\n", cell_noeud->nd->num, voisin->nd->num);

  fprintf(f, "\n");

  for (CellCommodite *cell_com = R->commodites; cell_com;
       cell_com = cell_com->suiv)
    fprintf(f, "k %d %d\n", cell_com->extrA->num, cell_com->extrB->num);
}

void liberer_noeud(CellNoeud *n) {
  while (n) {
    CellNoeud *tmp = n->suiv;
    CellNoeud *voisin = n->nd->voisins;
    while (voisin) {
      CellNoeud *next = voisin->suiv;
      free(voisin);
      voisin = next;
    }
    free(n->nd);
    free(n);
    n = tmp;
  }
}

void liberer_commodite(CellCommodite *c) {
  while (c) {
    CellCommodite *tmp = c->suiv;
    free(c);
    c = tmp;
  }
}

/* Libere integralement la memoire occupee par le reseau R */
void libererReseau(Reseau *R) {
  liberer_noeud(R->noeuds);
  liberer_commodite(R->commodites);
  free(R);
}
