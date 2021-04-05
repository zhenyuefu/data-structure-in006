#include <stdio.h>
#include <string.h>

#include "ArbreQuat.h"

int main(void) {
  FILE *f;
  f = fopen("00014_burma.cha", "r");
  Chaines *C = lectureChaines(f);
  fclose(f);

  Reseau *R = reconstitueReseauArbre(C);
  afficheReseauSVG(R, "test");

  f = fopen("14.res", "w");
  ecrireReseau(R, f);
  fclose(f);
  return 0;
}