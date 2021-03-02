#ifndef IOHASH_H_
#define IOHASH_H_

#include "biblioH.h"
#define HASH_SIZE 10

BiblioH* charger_n_entrees(char* nomfic, int n);

void enregistrer_biblio(BiblioH* b, char* nomfic);

#endif