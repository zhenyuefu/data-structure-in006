#include <stdio.h>
#include <string.h>

#include "Chaine.h"
#include "Hachage.h"
#include "Reseau.h"

int main(void) {
  FILE *f;
  f = fopen("00014_burma.cha", "r");
  Chaines *C = lectureChaines(f);
  fclose(f);

  Reseau *R = reconstitueReseauHash(C,57);
  afficheReseauSVG(R, "test");

  f = fopen("14.res","w");
  ecrireReseau(R,  f) ;
  fclose(f);
  return 0;
}