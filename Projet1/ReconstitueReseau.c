#include <stdio.h>
#include <string.h>

#include "Chaine.h"
#include "Reseau.h"

int main(void) {
  FILE *f;
  f = fopen("00014_burma.cha", "r");
  Chaines *C = lectureChaines(f);
  fclose(f);

  Reseau *R = reconstitueReseauListe(C);
  afficheReseauSVG(R, "test");

  printf("%d\n%d\n", nbLiaisons(R), nbCommodites(R));
  return 0;
}