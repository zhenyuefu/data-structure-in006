#include "biblioLC.h"

#include <stdio.h>
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
  biblio->L = NULL;
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

void afficher_livre(Livre* l) {
  printf("Num:%-5d Titre:%-27s Auteur:%-27s\n", l->num, l->titre, l->auteur);
}

void afficher_biblio(Biblio* b) {
  Livre* l = b->L;
  do {
    afficher_livre(l);
  } while ((l = l->suiv) != NULL);
}

Livre* recherche_livre_par_num(int num, Biblio* b) {
  Livre* l = b->L;
  while (l != NULL && l->num != num) {
    l = l->suiv;
  }
  if (l == NULL) return NULL;
  if (l->num == num) return l;
  return NULL;
}

Livre* recherche_livre_par_titre(char* titre, Biblio* b) {
  Livre* l = b->L;
  while (l != NULL && strcmp(titre, l->titre) == 0) {
    l = l->suiv;
  }
  if (l == NULL) return NULL;
  if (strcmp(titre, l->titre) == 0) return l;
  return NULL;
}

Biblio* recherche_livres_meme_auteur(char* auteur, Biblio* b) {
  Biblio* b_new;
  if ((b_new = creer_biblio()) == NULL) {
    puts("Can't creat biblio!");
    return NULL;
  }

  Livre* l = b->L;
  while (l != NULL) {
    if (strcmp(auteur, l->auteur) == 0)
      inserer_en_tete(b_new, l->num, l->titre, l->auteur);
    l = l->suiv;
  }
  return b_new;
}

void supprimer_livre(Biblio* b, int num, char* titre, char* auteur) {
  Livre* curr;
  /* The pointer points to the address of the "suiv" of the previous node */
  Livre** suivp = &(b->L);
  while ((curr = *suivp) != NULL &&
         (curr->num != num || strcmp(titre, curr->titre) != 0 ||
          strcmp(auteur, curr->auteur) != 0)) {
    suivp = &curr->suiv;
  }
  if (curr == NULL) return;
  *suivp = curr->suiv;
  liberer_livre(curr);
}

void fusion(Biblio* b1, Biblio* b2) {
  Livre** lp = &b2->L;
  Livre* curr;
  while ((curr = *lp) != NULL) {
    lp = &curr->suiv;
  }
  *lp = b1->L;
  b1->L = b2->L;
  b2->L = NULL;
  liberer_biblio(b2);
}

Biblio* recherche_exemplaires(Biblio* b) {
  Biblio* b_new;
  if ((b_new = creer_biblio()) == NULL) {
    puts("Can't create biblio");
    return NULL;
  }
  Livre* l = b->L;
  Livre* l2;
  int inser = 0;
  while (l != NULL) {
    l2 = b->L;
    while (l2 != NULL) {
      if (l != l2 && strcmp(l2->titre, l->titre) == 0 &&
          strcmp(l2->auteur, l->auteur) == 0) {
        inserer_en_tete(b_new, l2->num, l2->titre, l2->auteur);
        inser = 1;
      }
      l2 = l2->suiv;
    }
    if (inser == 1) {
      inserer_en_tete(b_new, l->num, l->titre, l->auteur);
      inser = 0;
    }
    l = l->suiv;
  }
  return b_new;
}