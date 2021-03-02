#ifndef BIBLIOH_H_
#define BIBLIOH_H_

#define GOLDEN 0.618

typedef struct livreh {
  int clef;
  int num;
  char* titre;
  char* auteur;
  struct livreh* suivant;
} LivreH;

typedef struct table {
  int nE; /* nombre d'elements contenus dans la table de hachage*/
  int m;  /* taille de la table de hachage */
  LivreH** T;
} BiblioH;

int fonctionClef(char* auteur);
LivreH* creer_livre(int num, char* titre, char* auteur);
BiblioH* creer_biblio(int m);
void liberer_biblio(BiblioH* b);
void liberer_livre(LivreH** lh);
int fonctionHachage(int cle, int m);
void inserer(BiblioH* b, int num, char* titre, char* auteur);

void afficher_livre(LivreH* l);
void afficher_biblio(BiblioH* b);

#endif