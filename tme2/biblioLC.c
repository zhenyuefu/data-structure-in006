#include "biblioLC.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* création d'un livre dont les données sont passées en paramètre */

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

/* libère le contenu du livre passé en paramètre */

void liberer_livre(Livre* l) {
  free(l->auteur);
  free(l->titre);
  free(l);
}

/* crée une bibliothèque */

Biblio* creer_biblio() {
  Biblio* biblio = (Biblio*)malloc(sizeof(Biblio));
  if (biblio == NULL) return NULL;
  biblio->L = NULL;
  return biblio;
}

/* libère le contenu de la bibliothèque passée en paramètre */

void liberer_biblio(Biblio* b) {
  Livre* l = b->L;
  while (l != NULL) {
    Livre* f = l;
    l = l->suiv;
    liberer_livre(f);
  }
  free(b);
}

/* insère un livre (dont les données ont été passé en paramètre) dans la bibliothèque */

void inserer_en_tete(Biblio* b, int num, char* titre, char* auteur) {
  Livre* l = creer_livre(num, titre, auteur);
  if (l == NULL) return;
  l->suiv = b->L;
  b->L = l;
}

/* affiche les données du livre passé en paramètre */

void afficher_livre(Livre* l) {
  if (l == NULL) {
    puts("error: livre is NULL!");
    return;
  }
  printf("Num:%-5d Titre:%-27s Auteur:%-27s\n", l->num, l->titre, l->auteur);
}

/* affiche le contenu de la bibliotèque passée en paramètre */

void afficher_biblio(Biblio* b) {
  if (b == NULL) {
    puts("error: biblio is NULL!");
    return;
  }
  Livre* l = b->L;
  if (l == NULL) {
    puts("error: this biblio has no book!");
    return;
  }
  while (l != NULL) {
    afficher_livre(l);
    l = l->suiv;
  }
}

/* recherche et retourne le livre portant le numéro 'num' */

Livre* recherche_livre_par_num(int num, Biblio* b) {
  Livre* l = b->L;
  while (l != NULL && l->num != num) {
    l = l->suiv;
  }
  if (l == NULL) return NULL;
  if (l->num == num) return l;
  return NULL;
}

/* recherche et retourne le livre portant le titre 'titre' */

Livre* recherche_livre_par_titre(char* titre, Biblio* b) {
  Livre* l = b->L;
  while (l != NULL && strcmp(titre, l->titre) != 0) {
    l = l->suiv;
  }
  if (l == NULL) return NULL;
  if (strcmp(titre, l->titre) == 0) return l;
  return NULL;
}

/* recherche et retourne une bibliothèque de tout les livres de l'auteur 'auteur' */

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

/* Retourne 1 si la suppression est réussie 0 sinon */
int supprimer_livre(Biblio* b, int num, char* titre, char* auteur) {
  Livre* curr;
  /* The pointer points to the address of the "suiv" of the previous node */
  Livre** suivp = &(b->L);
  while ((curr = *suivp) != NULL &&
         (curr->num != num || strcmp(titre, curr->titre) != 0 ||
          strcmp(auteur, curr->auteur) != 0)) {
    suivp = &curr->suiv;
  }
  if (curr == NULL) return 0;
  *suivp = curr->suiv;
  liberer_livre(curr);
  return 1;
}

/* ajoute la deuxième bibliothèque à la première */

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

/* recherche et retourne une bibliothèque dans laquelle on y retrouve plusieurs exemplaires d'ouvrages (même titre et même auteur) */

Biblio* recherche_exemplaires(Biblio* b) {
  Biblio* b_new;
  if ((b_new = creer_biblio()) == NULL) {
    puts("Can't create biblio");
    return NULL;
  }
  Livre* l = b->L;
  Livre* l2;
  while (l != NULL) {
    l2 = b->L;
    while (l2 != NULL) {
      if (l != l2 && strcmp(l2->titre, l->titre) == 0 &&
          strcmp(l2->auteur, l->auteur) == 0) {
        inserer_en_tete(b_new, l2->num, l2->titre, l2->auteur);
      }
      l2 = l2->suiv;
    }
    l = l->suiv;
  }
  return b_new;
}
