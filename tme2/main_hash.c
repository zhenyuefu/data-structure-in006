#include <stdio.h>
#include <stdlib.h>

#include "biblioH.h"
#include "iohash.h"

void usage(char *s) {
  printf("Usage:%s <filename> <ligne>\n", s);
  exit(EXIT_FAILURE);
}

void menu() {
  puts("");
  puts("1.affichage biblio");
  puts("2.ajouter un ouvrage");
  puts("3.recherche d’un ouvrage par son numero");
  puts("4.recherche d’un ouvrage par son titre");
  puts("5.recherche de tous les livres d’un meme auteur");
  puts("6.suppression d’un ouvrage");
  puts("7.recherche de tous les ouvrages avec plusieurs exemplaires");
  puts("press 0 to exit...");
}

int main(int argc, char **argv) {
  if (argc != 3) {
    usage(argv[0]);
  }

  BiblioH *b = charger_n_entrees_hash(argv[1], atoi(argv[2]));
  char rep;
  char buf[256];
  int num;
  char titre[256];
  char auteur[256];
  BiblioH *b2;
  LivreH *livre;
  do {
    menu();
    rep = getchar();
    while (getchar() != '\n') continue;
    switch (rep) {
      case '1':
        printf("\nAffichage:\n");
        afficher_biblioH(b);
        puts("Press entrer to continue...");
        while (getchar() != '\n') continue;
        break;

      case '2':
        printf(
            "\nVeuillez entrer le numero, le titre et l'auteur de "
            "l'ouvrage.\n");

        /* On suppose que le titre et l’auteur ne contiennent pas d’espace*/
        fgets(buf, sizeof(buf), stdin);
        if (sscanf(buf, "%d %s %s", &num, titre, auteur) == 3) {
          inserer(b, num, titre, auteur);
          puts("Ajout fait.");
        } else {
          puts("Erreur format");
        }
        puts("Press entrer to continue...");
        while (getchar() != '\n') continue;
        break;

      case '3':
        printf("\nVeuillez entrer le numero de l'ouvrage.\n");
        fgets(buf, sizeof(buf), stdin);
        if (sscanf(buf, "%d", &num) == 1) {
          if ((livre = hash_recherche_par_num(num, b)) == NULL) {
            printf("\nOuvrage non trouvé\n");
          } else {
            afficher_un_livre(livre);
          }
        } else {
          printf("\nErreur format\n");
        }
        puts("Press entrer to continue...");
        while (getchar() != '\n') continue;
        break;

      case '4':
        printf("\nVeuillez enntrer le titre de l'ouvrage.\n");
        fgets(buf, sizeof(buf), stdin);
        if (sscanf(buf, "%s", titre) == 1) {
          if ((livre = hash_recherche_par_titre(titre, b)) == NULL) {
            printf("\nOuvrage non trouvé\n");
          } else {
            afficher_un_livre(livre);
          }
          while (getchar() != '\n') continue;
        } else {
          printf("\nErreur format\n");
        }
        puts("Press entrer to continue...");
        while (getchar() != '\n') continue;
        break;

      case '5':
        printf("\nVeuillez entrer le nom de l'auteur.\n");
        fgets(buf, sizeof(buf), stdin);
        if (sscanf(buf, "%s", auteur) == 1) {
          if ((b2 = hash_recherche_meme_auteur(auteur, b)) != NULL &&
              b2->nE == 0) {
            printf("\nAucun ouvrage trouvé de cet auteur\n");
          } else {
            afficher_biblioH(b2);
          }
          liberer_biblioH(b2);
        } else {
          printf("\nErreur format\n");
        }
        puts("Press entrer to continue...");
        while (getchar() != '\n') continue;
        break;

      case '6':
        printf(
            "\nVeuillez entrer le numero, le titre et l'auteur de "
            "l'ouvrage.\n");
        /* On suppose que le titre et l’auteur ne contiennent pas d’espace*/
        fgets(buf, sizeof(buf), stdin);
        if (sscanf(buf, "%d %s %s", &num, titre, auteur) == 3) {
          if (supprimer_livreH(b, num, titre, auteur)) {
            printf("\nsuppression fait.\n");
          } else {
            printf("\nAucun livre trouvé à supprimer\n");
          }
        } else {
          printf("\nErreur format\n");
        }
        puts("Press entrer to continue...");
        while (getchar() != '\n') continue;
        break;

      case '7':
        if ((b2 = recherche_exemplaires_hash(b)) != NULL && (b2->nE == 0))
          printf("\nAucun exemplaires trouvés\n");
        else
          afficher_biblioH(b2);
        liberer_biblioH(b2);
        puts("Press entrer to continue...");
        while (getchar() != '\n') continue;
        break;
    }
  } while (rep != '0');

  liberer_biblioH(b);
  printf("\nAu revoir !\n");

  return 0;
}