#include <stdio.h>
#include <stdlib.h>

#include "biblioLC.h"
#include "entreeSortieLC.h"

void usage(char* s) {
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

int main(int argc, char** argv) {
  if (argc != 3) {
    usage(argv[0]);
  }
  Biblio* b;
  Biblio* b2;
  Livre* livre;
  b = charger_n_entrees(argv[1], atoi(argv[2]));
  char rep;
  int num;
  char titre[256];
  char auteur[256];
  do {
    menu();
    rep = getchar();
    while (getchar() != '\n') continue;
    switch (rep) {
      case '1':
        puts("Affichage :");
        afficher_biblio(b);
        break;
      case '2': {
        printf(
            "Veuillez ecrire le numero, le titre et l'auteur de l'ouvrage.\n");
        /* On suppose que le titre et l'auteur ne contiennent pas d'espace*/
        if (scanf("%d %s %s", &num, titre, auteur) == 3) {
          inserer_en_tete(b, num, titre, auteur);
          puts("Ajout fait.");
          while (getchar() != '\n') continue;
        } else {
          puts("Erreur format");
          while (getchar() != '\n') continue;
        }
      } break;
      case '3':
        printf("\nVeuillez entrer le numero de l'ouvrage.\n");

        if (scanf("%d", &num) == 1) {
          if ((livre = recherche_livre_par_num(num, b)) == NULL)
            printf("\nOuvrage non trouvé\n");
          else
            afficher_livre(livre);
          while (getchar() != '\n') continue;
        } else {
          printf("\nErreur format\n");
          while (getchar() != '\n') continue;
        }
        break;

      case '4':
        printf("\nVeuillez enntrer le titre de l'ouvrage.\n");
        if (scanf("%s", titre) == 1) {
          if ((livre = recherche_livre_par_titre(titre, b)) == NULL)
            printf("\nOuvrage non trouvé\n");
          else
            afficher_livre(livre);
          while (getchar() != '\n') continue;
        } else {
          printf("\nErreur format\n");
          while (getchar() != '\n') continue;
        }
        break;

      case '5':
        printf("\nVeuillez entrer le nom de l'auteur.\n");
        if (scanf("%s", auteur) == 1) {
          if ((b2 = recherche_livres_meme_auteur(auteur, b)) != NULL &&
              b2->L == NULL)
            printf("\nAucun ouvrage trouvé de cet auteur\n");
          else
            afficher_biblio(b2);
          while (getchar() != '\n') continue;
          liberer_biblio(b2);
        } else {
          printf("\nErreur format\n");
          while (getchar() != '\n') continue;
        }
        break;

      case '6':
        printf(
            "\nVeuillez entrer le numero, le titre et l'auteur de "
            "l'ouvrage.\n");
        /* On suppose que le titre et l’auteur ne contiennent pas d’espace*/

        if (scanf("%d %s %s", &num, titre, auteur) == 3) {
          if (supprimer_livre(b, num, titre, auteur))
            printf("\nsuppression fait.\n");
          else
            printf("\nAucun livre trouvé à supprimer\n");
          while (getchar() != '\n') continue;
        } else {
          printf("\nErreur format\n");
          while (getchar() != '\n') continue;
        }
        break;

      case '7':
        if ((b2 = recherche_exemplaires(b)) != NULL && (b2->L == NULL))
          printf("\nAucun exemplaires trouvés\n");
        else
          afficher_biblio(b2);
        liberer_biblio(b2);
        break;
    }
  } while (rep != '0');
  puts("Merci, et au revoir.");
  liberer_biblio(b);
  return 0;
}