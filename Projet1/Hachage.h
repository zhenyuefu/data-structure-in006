#ifndef __HACHAGE_H__
#define __HACHAGE_H__

#define GOLDEN 0.618

typedef struct tableHachage TableHachage; 
typedef struct nodeHachage NodeHachage;

#include "Reseau.h"
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

#endif