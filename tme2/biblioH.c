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

/* Cette fonction permettra de libérer tous les livres sur la liste chainee */
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

void afficher_livreH(LivreH* l) {
  if (l == NULL) {
    return;
  }
  while (l) {
    afficher_livre(l);
    l = l->suivant;
  }
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
    afficher_livreH(l);
  }
}

LivreH* recherche_livre_par_num(int num, BiblioH* b) {
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

LivreH* recherche_livre_par_titre(char* titre, BiblioH* b) {
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

BiblioH* recherche_livres_meme_auteur(char* auteur, BiblioH* b) {
  int cle = fonctionClef(auteur);
  int hash = fonctionHachage(cle, b->m);
  BiblioH* b_new = creer_biblio(b->m);
  LivreH* l = b->T[hash];
  while (l != NULL) {
    if (strcmp(auteur, l->auteur) == 0) {
      inserer(b_new, l->num, l->titre, l->auteur);
    }
    l = l->suivant;
  }
  return b_new;
}

void supprimer_livre(BiblioH* b, int num, char* titre, char* auteur) {
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
  if (curr == NULL) return;
  *suivp = curr->suivant;
  /* Pour que le livre qui se trouve derrière ce nœud ne soit pas libéré, coupez
   * la chaîne */
  curr->suivant = NULL;
  liberer_livre(&curr);
  b->nE--;
}

/* Ajouter les livres en b2 à b1 */
void fusion(BiblioH* b1, BiblioH* b2) {
  LivreH** lp;
  LivreH* current;
  for (int i = 0; i < b2->m; i++) {
    lp = &b2->T[i];
    while ((current = *lp) != NULL) {
      inserer(b1, current->num, current->titre, current->auteur);
      lp = &current->suivant;
    }
  }
  liberer_biblio(b2);
}

BiblioH* recherche_exemplaires(BiblioH* b) {
  BiblioH* b_new;
  if ((b_new = creer_biblio(b->m)) == NULL) {
    puts("Can't create biblio");
    return NULL;
  }
  LivreH** lp;
  LivreH* current;
  LivreH* l2;
  for (int i = 0; i < b->m; i++) {
    lp= &b->T[i];
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