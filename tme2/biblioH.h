#ifndef BIBLIOH_H_
#define BIBLIOH_H_

#define GOLDEN 0.618

#define PRIMESIZE 26
static const int PrimeList[PRIMESIZE] = {
    53,        97,        193,       389,       769,       1543,     3079,
    6151,      12289,     24593,     49157,     98317,     196613,   393241,
    786433,    1572869,   3145739,   6291469,   12582917,  25165843, 50331653,
    100663319, 201326611, 402653189, 805306457, 1610612741};

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
LivreH* creer_livreH(int num, char* titre, char* auteur);
BiblioH* creer_biblioH(int m);
void liberer_biblioH(BiblioH* b);
void liberer_livreH(LivreH** lh);
int fonctionHachage(int cle, int m);
void inserer(BiblioH* b, int num, char* titre, char* auteur);

void afficher_un_livre(LivreH* l);
void afficher_livreH(LivreH* l);
void afficher_biblioH(BiblioH* b);

LivreH* hash_recherche_par_num(int num, BiblioH* b);
LivreH* hash_recherche_par_titre(char* titre, BiblioH* b);
BiblioH* hash_recherche_meme_auteur(char* auteur, BiblioH* b);
int supprimer_livreH(BiblioH* b, int num, char* titre, char* auteur);
void fusion_hash(BiblioH* b1, BiblioH* b2);
BiblioH* recherche_exemplaires_hash(BiblioH* b);

#endif