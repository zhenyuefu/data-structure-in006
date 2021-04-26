#include "Graphe.h"

#include <stdio.h>
/* Creer le graphe correspondant au reseau R */
Graphe* creerGraphe(Reseau* r) {
  Graphe* g = malloc(sizeof(Graphe));
  g->gamma = r->gamma;
  g->nbsom = r->nbNoeuds;
  g->nbcommod = nbCommodites(r);
  g->T_som = malloc(sizeof(Sommet*) * g->nbsom);
  g->T_commod = malloc(sizeof(Commod) * g->nbcommod);
  CellNoeud* l_nodes = r->noeuds;
  while (l_nodes != NULL) {
    Sommet* sommet = malloc(sizeof(Sommet));
    sommet->num = l_nodes->nd->num;
    g->T_som[sommet->num - 1] = sommet;
    sommet->x = l_nodes->nd->x;
    sommet->y = l_nodes->nd->y;
    sommet->L_voisin = NULL;

    l_nodes = l_nodes->suiv;
  }
  l_nodes = r->noeuds;
  while (l_nodes != NULL) {
    CellNoeud* c_node = l_nodes->nd->voisins;
    Sommet* s = g->T_som[l_nodes->nd->num - 1];
    while (c_node != NULL) {
      if (c_node->nd->num > s->num) {
        Arete* arete = malloc(sizeof(Arete));
        arete->u = s->num;
        arete->v = c_node->nd->num;
        Cellule_arete* c_arete = malloc(sizeof(Cellule_arete));
        c_arete->a = arete;
        c_arete->usuiv = s->L_voisin;
        c_arete->vsuiv = g->T_som[arete->v - 1]->L_voisin;
        s->L_voisin = c_arete;
        g->T_som[arete->v - 1]->L_voisin = c_arete;
      }

      c_node = c_node->suiv;
    }

    l_nodes = l_nodes->suiv;
  }

  CellCommodite* c_commodite = r->commodites;
  int i = 0;
  while (c_commodite != NULL) {
    g->T_commod[i].e1 = c_commodite->extrA->num;
    g->T_commod[i].e2 = c_commodite->extrB->num;
    // printf("%d %d %d\n", i, c_commodite->extrA->num, c_commodite->extrB->num);
    i++;
    c_commodite = c_commodite->suiv;
  }

  return g;
}

void ecrireGraph(Graphe* g, FILE* f) {
  fprintf(f, "nbNoeud = %d\n", g->nbsom);
  fprintf(f, "nbCom = %d\n", g->nbcommod);
  fprintf(f, "Gamma = %d\n\n", g->gamma);

  for (int i = 0; i < g->nbsom; i++) {
    fprintf(f, "v %d %.2f %.2f:\n", g->T_som[i]->num, g->T_som[i]->x,
            g->T_som[i]->y);
    Cellule_arete* L_voisin = g->T_som[i]->L_voisin;
    while (L_voisin != NULL) {
      Arete* a = L_voisin->a;
      fprintf(f, "%d %d\n", a->u, a->v);
      if (a->u == i + 1)
        L_voisin = L_voisin->usuiv;
      else
        L_voisin = L_voisin->vsuiv;
    }
  }
  fprintf(f, "\n");

  for (int i = 0; i < g->nbcommod; i++)
    fprintf(f, "k %d %d\n", g->T_commod[i].e1, g->T_commod[i].e2);
}

/* Retourne la distance entre les sommets-noeuds u et v dans le graphe G.
   (Cette version de la fonction n'est pas utilisee dans reorganiseReseau)*/
// int distance_sans_prec(Graphe* G, int u, int v) { return 0; }

/* Retourne une liste chainee d'entier contenant les sommets-noeuds de la plus
   courte chaine entre u et v dans le graphe G. */
// ListeEntier distance_avec_prec(Graphe* G, int u, int v) { return NULL; }

/* Reorganise le Reseau R tel qu'indique dans la quesiton 7.4 */
// int reorganiseReseau(Reseau* R) { return 1; }

/* Libere integralement la memoire occupee par le graphe G */
// void libererGraphe(Graphe* G) {}