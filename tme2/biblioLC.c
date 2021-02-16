#include "biblioLC.h"

#include <stdlib.h>
#include <string.h>

Livre* creer_livre(int num, char* titre, char* auteur) {
  Livre* livre = (Livre*)malloc(sizeof(Livre));
  if (livre == NULL) return NULL;
  livre->titre = (char*)malloc(strlen(titre) + 1);
  if (livre->titre == NULL) {
    free(livre);
    return NULL;
  }
  livre->auteur = (char*)malloc(strlen(auteur) + 1);
  if (livre->auteur == NULL) {
    free(livre->titre);
    free(livre);
    return NULL;
  }
  livre->num = num;
  strcpy(livre->titre, titre);
  strcpy(livre->auteur, auteur);
  livre->suiv = NULL;
  return livre;
}

void liberer_livre(Livre* l) {
  free(l->auteur);
  free(l->titre);
  free(l);
}

Biblio* creer_biblio() {
  Biblio* biblio = (Biblio*)malloc(sizeof(Biblio));
  if (biblio == NULL) return NULL;
  biblio->L=NULL;
  return biblio;
}

void liberer_biblio(Biblio* b) {
  Livre* l = b->L;
  while (l != NULL) {
    Livre* f = l;
    l = l->suiv;
    liberer_livre(f);
  }
  free(b);
}

void inserer_en_tete(Biblio* b, int num, char* titre, char* auteur) {
  Livre* l = creer_livre(num, titre, auteur);
  if (l == NULL) return;
  l->suiv = b->L;
  b->L = l;
}