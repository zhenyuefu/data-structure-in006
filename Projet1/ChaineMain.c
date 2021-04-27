#include "Chaine.h"

/* L'execution de ce fichier affiche les valeurs suivantes :
    - pour l'instance 00014_burma.cha : 85.97 30
    - pour l'instance 05000_USA-road-d-NY.cha : 481202156.40 130862
    - pour l'instance 07397_pla.cha :  3288496420.88 275090
*/
int main() {
  FILE* f = fopen("00014_burma.cha", "r");
  Chaines* C = lectureChaines(f);
  fclose(f);

  f = fopen("exemple.cha", "w");
  ecrireChaines(C, f);
  fclose(f);

  afficheChainesSVG(C, "sd_projet");
  printf("%.2f %d\n", longueurTotale(C), comptePointsTotal((C)));

  libererChaines(C);
  return 0;
}