#include <stdio.h>
#include <string.h>

#include "Reseau.h"

int main(void) {
  FILE *f;
  f = fopen("00014_burma.cha", "r");
  Chaines *C = lectureChaines(f);
  fclose(f);

  Reseau *R = reconstitueReseauListe(C);
  afficheReseauSVG(R, "test");

  f = fopen("14.res", "w");
  ecrireReseau(R, f);
  fclose(f);
  return 0;
}