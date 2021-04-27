#include "Graphe.h"

#include <stdio.h>
#include <string.h>

#include "Struct_File.h"
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
    // printf("%d %d %d\n", i, c_commodite->extrA->num,
    // c_commodite->extrB->num);
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
int distance_sans_prec(Graphe* G, int u, int v) {
  if (u == v) {
    return 0;
  }
  int visited[G->nbsom];
  for (int i = 0; i < G->nbsom; i++) {
    visited[i] = 0;
  }

  S_file* queue = malloc(sizeof(S_file));
  Init_file(queue);
  enfile(queue, u);
  visited[u - 1]++;

  int depth = 0;
  while (!estFileVide(queue)) {
    int n = queue->size;
    for (int i = 0; i < n; i++) {
      int num = defile(queue);
      if (num == v) return depth;
      Sommet* som = G->T_som[num - 1];
      Cellule_arete* c_arete = som->L_voisin;
      while (c_arete != NULL) {
        Arete* a = c_arete->a;
        if (a->u == num) {
          if (!visited[a->v - 1]) {
            enfile(queue, a->v);
            visited[a->v - 1]++;
          }
          c_arete = c_arete->usuiv;
        } else {
          if (!visited[a->u - 1]) {
            enfile(queue, a->u);
            visited[a->u - 1]++;
          }
          c_arete = c_arete->vsuiv;
        }
      }
    }
    depth++;
  }

  return -1;
}

/* Retourne une liste chainee d'entier contenant les sommets-noeuds de la plus
   courte chaine entre u et v dans le graphe G. */
ListeEntier distance_avec_prec(Graphe* G, int u, int v) {
  if (u == v) {
    return 0;
  }
  int visited[G->nbsom];
  int path[G->nbsom];
  for (int i = 0; i < G->nbsom; i++) {
    visited[i] = 0;
    path[i] = -1;
  }

  S_file* queue = malloc(sizeof(S_file));
  Init_file(queue);
  enfile(queue, u);
  visited[u - 1]++;

  while (!estFileVide(queue)) {
    int n = queue->size;
    for (int i = 0; i < n; i++) {
      int num = defile(queue);
      if (num == v) break;
      Sommet* som = G->T_som[num - 1];
      Cellule_arete* c_arete = som->L_voisin;
      while (c_arete != NULL) {
        Arete* a = c_arete->a;
        if (a->u == num) {
          if (!visited[a->v - 1]) {
            enfile(queue, a->v);
            visited[a->v - 1]++;
            path[a->v - 1] = num;
          }
          c_arete = c_arete->usuiv;
        } else {
          if (!visited[a->u - 1]) {
            enfile(queue, a->u);
            visited[a->u - 1]++;
            path[a->u - 1] = num;
          }
          c_arete = c_arete->vsuiv;
        }
      }
    }
  }
  free(queue);

  ListeEntier liste;
  Init_Liste(&liste);
  ajoute_en_tete(&liste, v);
  int p = path[v - 1];
  while (p != -1) {
    ajoute_en_tete(&liste, p);
    p = path[p - 1];
  }
  return liste;
}

/* Reorganise le Reseau R tel qu'indique dans la quesiton 7.4 */
int reorganiseReseau(Reseau* R) {
  Graphe* G = creerGraphe(R);
  int nbsom = G->nbsom;
  int nb_pass_arete[nbsom][nbsom];
  memset(nb_pass_arete, 0, sizeof(nb_pass_arete));
  ListeEntier l;
  for (int i = 0; i < G->nbcommod; i++) {
    l = distance_avec_prec(G, G->T_commod[i].e1, G->T_commod[i].e2);
    if (l == NULL) {
      continue;
    }
    ListeEntier freelist =l;
    while (l->suiv) {
      int u = l->u - 1;

      int v = l->suiv->u - 1;
      nb_pass_arete[u][v]++;

      l = l->suiv;
    }
    desalloue(&freelist);
  }

  for (int i = 0; i < nbsom; i++)
    for (int j = 0; j < nbsom; j++)
      if (nb_pass_arete[i][j] > G->gamma) {
        libererGraphe(G);
        return 0;
      }
  libererGraphe(G);
  return 1;
}

/* Libere integralement la memoire occupee par le graphe G */
void libererGraphe(Graphe* G) {
  for (int i = 0; i < G->nbsom; i++) {
    Cellule_arete* next = G->T_som[i]->L_voisin;
    while (next != NULL) {
      Cellule_arete* freenode = next;
      next = next->a->u == i + 1 ? next->usuiv : next->vsuiv;
      if (freenode->a->v == i + 1) {
        free(freenode->a);
        free(freenode);
      }
    }
    free(G->T_som[i]);
  }
  free(G->T_som);
  free(G->T_commod);
  free(G);
}