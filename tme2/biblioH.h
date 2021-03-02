#ifndef BIBLIOH_H_
#define BIBLIOH_H_

typedef struct livreh {
  int clef;
  int num;
  char * titre;
  char * auteur;
  struct livreh *suivant;
} LivreH;

typedef struct table {
  int nE; /* nombre d'elements contenus dans la table de hachage*/
  int m;  /* taille de la table de hachage */
  LivreH **T;
} BiblioH;



#endif