#include "biblioH.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int fonctionClef(char* auteur) {
  int somme = 0;

  for (int i = 0; auteur[i] != '\0'; i++) {
    somme += (int)auteur[i];
  }
  return somme;
}

LivreH* creer_livre(int num, char* titre, char* auteur) {
  LivreH* lh = (LivreH*)malloc(sizeof(LivreH));
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
  /* Initialisation des tableaux */
  memset(b->T, 0, sizeof(LivreH*) * b->m);
  return b;
}

void liberer_biblio(BiblioH* b) {
  LivreH** tab = b->T;

  for (int i = 0; i < (b->m); i++) liberer_livre(&tab[i]);
  free(b->T);
  free(b);
}

void liberer_livre(LivreH** lh) {
  LivreH* curr = *lh;

  while ((curr = *lh) != NULL) {
    lh = &curr->suivant;
    free(curr->auteur);
    free(curr->titre);
    free(curr);
  }
}

int fonctionHachage(int cle, int m) {
  return (int)(m * ((double)cle * GOLDEN - (int)(cle * GOLDEN)));
}

void inserer(BiblioH* b, int num, char* titre, char* auteur) {
  LivreH* l = creer_livre(num, titre, auteur);
  if (l == NULL) {
    puts("error:creer_livre");
    return;
  }
  int hash = fonctionHachage(l->clef, b->m);
  l->suivant = b->T[hash];
  b->T[hash] = l;
  b->nE++;
}

void afficher_livre(LivreH* l) {
  if (l == NULL) {
    return;
  }
  printf("Num:%-5d Titre:%-27s Auteur:%-27s\n", l->num, l->titre, l->auteur);
}

void afficher_biblio(BiblioH* b) {
  if (b == NULL) {
    puts("error: biblio is NULL!");
    return;
  }
  if (b->nE == 0) {
    puts("This biblio has no book!");
    return;
  }

  LivreH* l;

  for (int i = 0; i < (b->m); i++) {
    l = b->T[i];
    while (l) {
      afficher_livre(l);
      l = l->suivant;
    }
  }
}