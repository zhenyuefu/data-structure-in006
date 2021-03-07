#include "biblioH.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* retourne un entier (clef) à partir du nom de l'auteur */

int fonctionClef(char* auteur) {
  int somme = 0;

  for (int i = 0; auteur[i] != '\0'; i++) {
    somme += (int)auteur[i];
  }
  return somme;
}

/* création d'un livre dont les données sont passées en paramètre */

LivreH* creer_livreH(int num, char* titre, char* auteur) {
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

/* crée une bibliothèque dont la taille est passée en paramètre */

BiblioH* creer_biblioH(int m) {
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

/* libère le contenu de la bibliothèque passée en paramètre */

void liberer_biblioH(BiblioH* b) {
  LivreH** tab = b->T;

  for (int i = 0; i < (b->m); i++) liberer_livreH(&tab[i]);
  free(b->T);
  free(b);
}

/* Cette fonction permettra de libérer tous les livres sur la liste chainee */

void liberer_livreH(LivreH** lh) {
  LivreH* curr = *lh;

  while ((curr = *lh) != NULL) {
    lh = &curr->suivant;
    free(curr->auteur);
    free(curr->titre);
    free(curr);
  }
}

/* retourne un entier (index de la clé calculée à partir de la clé et de la taille) pour la table de hachage */

int fonctionHachage(int cle, int m) {
  return (int)(m * ((double)cle * GOLDEN - (int)(cle * GOLDEN)));
}

/* insère un livre (dont les données ont été passé en paramètre) dans la bibliothèque */

void inserer(BiblioH* b, int num, char* titre, char* auteur) {
  LivreH* l = creer_livreH(num, titre, auteur);
  if (l == NULL) {
    puts("error:creer_livre");
    return;
  }
  int hash = fonctionHachage(l->clef, b->m);
  l->suivant = b->T[hash];
  b->T[hash] = l;
  b->nE++;
}

/* affiche les données du livre passé en paramètre */

void afficher_un_livre(LivreH* l) {
  if (l == NULL) {
    return;
  }

  printf("Num:%-5d Titre:%-27s Auteur:%-27s\n", l->num, l->titre, l->auteur);
}

/* affiche les données d'une liste chainée de livre passée en paramètre */

void afficher_livreH(LivreH* l) {
  if (l == NULL) {
    return;
  }
  while (l) {
    afficher_un_livre(l);
    l = l->suivant;
  }
}

/* affiche le contenu de la bibliotèque passée en paramètre */

void afficher_biblioH(BiblioH* b) {
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
    afficher_livreH(l);
  }
}

/* recherche et retourne le livre portant le numéro 'num' */

LivreH* hash_recherche_par_num(int num, BiblioH* b) {
  LivreH* l;
  for (int i = 0; i < b->m; i++) {
    l = b->T[i];
    while (l != NULL && l->num != num) {
      l = l->suivant;
    }
    if (l != NULL) return l;
  }
  return NULL;
}

/* recherche et retourne le livre portant le titre 'titre' */

LivreH* hash_recherche_par_titre(char* titre, BiblioH* b) {
  LivreH* l;
  for (int i = 0; i < b->m; i++) {
    l = b->T[i];
    while (l != NULL && strcmp(titre, l->titre) != 0) {
      l = l->suivant;
    }
    if (l != NULL) return l;
  }
  return NULL;
}

/* recherche et retourne une bibliothèque de tout les livres de l'auteur 'auteur' */

/* Une nouvelle biblio est créée et la mémoire doit être libérée */
BiblioH* hash_recherche_meme_auteur(char* auteur, BiblioH* b) {
  int cle = fonctionClef(auteur);
  int hash = fonctionHachage(cle, b->m);
  BiblioH* b_new;
  if ((b_new = creer_biblioH(b->m)) == NULL) {
    puts("Can't create biblio");
    return NULL;
  }
  LivreH* l = b->T[hash];
  while (l != NULL) {
    if (strcmp(auteur, l->auteur) == 0) {
      inserer(b_new, l->num, l->titre, l->auteur);
    }
    l = l->suivant;
  }
  return b_new;
}

/* Retourne 1 si la suppression est réussie 0 sinon */

int supprimer_livreH(BiblioH* b, int num, char* titre, char* auteur) {
  int cle = fonctionClef(auteur);
  int hash = fonctionHachage(cle, b->m);
  LivreH* curr;
  /* The pointer points to the address of the "suiv" of the previous node */
  LivreH** suivp = &(b->T[hash]);
  while ((curr = *suivp) != NULL &&
         (curr->num != num || strcmp(titre, curr->titre) != 0 ||
          strcmp(auteur, curr->auteur) != 0)) {
    suivp = &curr->suivant;
  }
  if (curr == NULL) return 0;
  *suivp = curr->suivant;
  /* Pour que le livre qui se trouve derrière ce nœud ne soit pas libéré, coupez
   * la chaîne */
  curr->suivant = NULL;
  liberer_livreH(&curr);
  b->nE--;
  return 1;
}

/* Ajouter les livres en b2 à b1 */
void fusion_hash(BiblioH* b1, BiblioH* b2) {
  LivreH** lp;
  LivreH* current;
  for (int i = 0; i < b2->m; i++) {
    lp = &b2->T[i];
    while ((current = *lp) != NULL) {
      inserer(b1, current->num, current->titre, current->auteur);
      lp = &current->suivant;
    }
  }
  liberer_biblioH(b2);
}

/* recherche et retourne une bibliothèque dans laquelle on y retrouve plusieurs exemplaires d'ouvrages (même titre et même auteur) */

/* Une nouvelle biblio est créée et la mémoire doit être libérée */
BiblioH* recherche_exemplaires_hash(BiblioH* b) {
  BiblioH* b_new;
  if ((b_new = creer_biblioH(b->m)) == NULL) {
    puts("Can't create biblio");
    return NULL;
  }
  LivreH** lp;
  LivreH* current;
  LivreH* l2;
  for (int i = 0; i < b->m; i++) {
    lp = &b->T[i];
    while ((current = *lp) != NULL) {
      l2 = b->T[i];
      while (l2 != NULL) {
        if (current != l2 && strcmp(l2->titre, current->titre) == 0 &&
            strcmp(l2->auteur, current->auteur) == 0) {
          inserer(b_new, l2->num, l2->titre, l2->auteur);
        }
        l2 = l2->suivant;
      }
      lp = &current->suivant;
    }
  }
  return b_new;
}
