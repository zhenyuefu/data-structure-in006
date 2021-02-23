#include <stdio.h>
#include <stdlib.h>

#include "biblioLC.h"
#include "entreeSortieLC.h"

void usage(char* s) {
  printf("Usage:%s <filename> <ligne>\n", s);
  exit(EXIT_FAILURE);
}

void menu() {
  puts("1.affichage biblio");
  puts("2.ajouter un ouvrage");
  puts("press 0 to exit...");
}

int main(int argc, char** argv) {
  if (argc != 3) {
    usage(argv[0]);
  }
  Biblio* b;
  b = charger_n_entrees(argv[1], atoi(argv[2]));
  char rep;
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
        int num;
        char titre[256];
        char auteur[256];
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
    }
  } while (rep != '0');
  puts("Merci, et au revoir.");
  liberer_biblio(b);
  return 0;
}