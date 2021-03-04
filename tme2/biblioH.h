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
void afficher_livreH(LivreH* l);
void afficher_biblio(BiblioH* b);

LivreH* recherche_livre_par_num(int num, BiblioH* b);
LivreH* recherche_livre_par_titre(char* titre, BiblioH* b);
BiblioH* recherche_livres_meme_auteur(char* auteur, BiblioH* b);
void supprimer_livre(BiblioH *b, int num, char *titre, char *auteur);
void fusion(BiblioH* b1, BiblioH* b2);
BiblioH* recherche_exemplaires(BiblioH* b);

#endif