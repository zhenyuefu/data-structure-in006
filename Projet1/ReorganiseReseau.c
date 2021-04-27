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
  ListeEntier iterlist = iterlist;
  while (iterlist) {
    printf("%d", iterlist->u);
    if (iterlist->suiv) printf("->");
    iterlist = iterlist->suiv;
  }
  puts("");
  desalloue(&list);

  printf("%d\n",reorganiseReseau((R)));
  libererChaines(C);
  libererReseau(R);
  libererGraphe(G);
  return 0;
}