#include "entreeSortieLC.h"

#include <stdio.h>

Biblio* charger_n_entrees(char* nomfic, int n, Biblio* b) {
  FILE* f = fopen(nomfic, "r");

  if (f == NULL) {
    printf("Erreur lors de l'ouverture du fichier\n");
    exit(1);
  }

  char ligne[100];
  char* titre;
  char* auteur;
  int num;
  int cpt = 0;

  while (fgets(ligne, 100, f)) {
    if (cpt == n) {
      break;
    }
    sscanf("%d %s %s", &num, &titre, &auteur);
    inserer_en_tete(b, num, titre, auteur);
    cpt++;
  }

  fclose(f);

  return b;
}

void enregistrer_biblio(Biblio* b, char* nomfic) {
  FILE* f = fopen(nomfic, "w");

  if (f == NULL) {
    printf("Erreur lors de l'ouverture du fichier\n");
    exit(1);
  }

  Livre* l = b->L;
  while (l) {
    fprintf(f, "%d %s %s\n", l->num, l->titre, l->auteur);
    l = l->suiv;
  }

  fclose(f);
}