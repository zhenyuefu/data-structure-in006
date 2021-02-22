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