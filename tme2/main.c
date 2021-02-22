#include <stdio.h>
#include <stdlib.h>

#include "biblioLC.h"
#include "entreeSortieLC.h"

void usage(char* s) {
  printf("Usage:%s <filename> <ligne>\n", s);
  exit(EXIT_FAILURE);
}

int main(int argc, char** argv) {
  if (argc != 3) {
    usage(argv[0]);
  }
  Biblio* b;
  b = charger_n_entrees(argv[1], atoi(argv[2]));
  afficher_biblio(b);
  liberer_biblio(b);
  return 0;
}