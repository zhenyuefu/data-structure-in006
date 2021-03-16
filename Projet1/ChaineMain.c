#include <string.h>

#include "Chaine.h"

int main(void) {
  FILE *f;
  f = fopen("00014_burma.cha", "r");
  Chaines *C = lectureChaines(f);
  fclose(f);

  f = fopen("Chaine.txt", "w");
  ecrireChaines(C, f);
  fclose(f);

  afficheChainesSVG(C, "test");
  printf("longueur totale = %.2f\n", longueurTotale(C));
  return 0;
}