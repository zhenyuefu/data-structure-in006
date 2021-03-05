#include "iohash.h"

#include <stdio.h>
#include <stdlib.h>

#include "biblioH.h"

BiblioH* charger_n_entrees(char* nomfic, int n) {
  FILE* fp;

  if ((fp = fopen(nomfic, "r")) == NULL) {
    printf("Can't open %s\n", nomfic);
    exit(EXIT_FAILURE);
  }

  BiblioH* b;
  if ((b = creer_biblio(n)) == NULL) {
    puts("Can't creat biblio!");
    return NULL;
  }

  char ligne[256];
  char titre[256];
  char auteur[256];
  int num;
  int cpt = 0;

  while (fgets(ligne, 256, fp)) {
    if (cpt == n) {
      break;
    }
    sscanf(ligne, "%d %s %s", &num, titre, auteur);
    inserer(b, num, titre, auteur);
    cpt++;
  }

  if (fclose(fp)) printf("Error in closing file %s\n", nomfic);

  return b;
}

void enregistrer_biblio(BiblioH* b, char* nomfic) {
  FILE* fp;

  if ((fp = fopen(nomfic, "w")) == NULL) {
    printf("Can't open %s\n", nomfic);
    exit(EXIT_FAILURE);
  }

  LivreH* l;
  for (int i = 0; i < b->m; l = b->T[i++]) {
    while (l) {
      fprintf(fp, "%d %s %s\n", l->num, l->titre, l->auteur);
      l = l->suivant;
    }
  }
  if (fclose(fp)) printf("Error in closing file %s\n", nomfic);
}