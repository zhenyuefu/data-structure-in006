#include "biblioH.h"

#include <stdlib.h>

int fonctionClef(char* auteur) {
  int somme = 0;

  for (int i = 0; auteur[i] != '\0'; i++) {
    somme += (int)auteur[i];
  }
  return somme;
}

LivreH* create_libre(int num, char* titre, char* auteur) {
  LivreH* lh = malloc(sizeof(LivreH));
  if (lh == NULL) return NULL;
  lh->titre = (char*)malloc(strlen(titre) + 1);
  if (lh->titre == NULL) {
    free(lh);
    return NULL;
  }
  lh->auteur = (char*)malloc(strlen(auteur) + 1);
  if (lh->auteur == NULL) {
    free(lh->titre);
    free(lh);
    return NULL;
  }
  lh->num = num;
  strcpy(lh->titre, titre);
  strcpy(lh->auteur, auteur);
  lh->clef = fonctionClef(auteur);
  lh->suivant = NULL;
  return lh;
}

BiblioH* creer_biblio(int m) {
  BiblioH* b = malloc(sizeof(BiblioH));

  if (b == NULL) return NULL;
  b->nE = 0;
  b->m = m;
  b->T = (LivreH**)malloc(sizeof(LivreH*) * b->m);
  if (b->T == NULL) {
    free(b);
    return NULL;
  }
  return b;
}

void liberer_biblio(BiblioH* b) {
  LivreH** tab = b->T;

  for (int i = 0; i < (b->m); i++) liberer_livreH(&tab[i]);
  free(b->T);
  free(b);
}

void liberer_livreH(LivreH** lh) {
  LivreH* curr = *lh;

  while ((curr = *lh) != NULL) {
    lh = &curr->suivant;
    free(curr->auteur);
    free(curr->titre);
    free(curr);
  }
}