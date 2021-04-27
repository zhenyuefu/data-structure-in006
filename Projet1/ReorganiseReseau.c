#include "Graphe.h"
#include "Struct_Liste.h"

int main(void) {
  FILE *f;
  f = fopen("00014_burma.cha", "r");
  Chaines *C = lectureChaines(f);
  fclose(f);

  Reseau *R = reconstitueReseauListe(C);

  Graphe *G = creerGraphe(R);
  ListeEntier list = distance_avec_prec(G, 1, 8);

  while (list) {
    printf("%d", list->u);
    if (list->suiv) printf("->");
    list = list->suiv;
  }
  puts("");
  return 0;
}