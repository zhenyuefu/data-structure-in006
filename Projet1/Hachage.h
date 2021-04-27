#ifndef __HACHAGE_H__
#define __HACHAGE_H__
#include "Reseau.h"

#define GOLDEN 0.618

typedef struct tableHachage TableHachage;
typedef struct nodeHachage NodeHachage;

struct nodeHachage {
  Noeud *node;
  NodeHachage *suiv;
};

struct tableHachage {
  int size;
  int nb_elements;
  NodeHachage **nodes;
};

int functionClef(int x, int y);
int functionHachage(int cle, int size);
Reseau *reconstitueReseauHachage(Chaines *C, int size);
Noeud *rechercheCreeNoeudHachage(Reseau *R, TableHachage *H, double x,
                                 double y);

#endif