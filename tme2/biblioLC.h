#ifndef BIBLIOLC_H_
#define BIBLIOLC_H_

typedef struct livre {
  int num;
  char* titre;
  char* auteur;
  struct livre* suiv;
} Livre;

typedef struct biblio {
  Livre* L;
} Biblio;

Livre* creer_livre(int num, char* titre, char* auteur);

void liberer_livre(Livre* l);

Biblio* creer_biblio();

void liberer_biblio(Biblio* b);

void inserer_en_tete(Biblio* b, int num, char* titre, char* auteur);

void afficher_livre(Livre* l);

void afficher_biblio(Biblio* b);

Livre* recherche_livre_par_num(int num, Biblio* b);

Livre* recherche_livre_par_titre(char* titre, Biblio* b);

Biblio* recherche_livres_meme_auteur(char* auteur, Biblio* b);

void supprimer_livre(Biblio *b, int num, char *titre, char *auteur);

void fusion(Biblio* b1, Biblio* b2);

Biblio* recherche_exemplaires(Biblio* b);

#endif