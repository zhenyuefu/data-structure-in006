#include "ArbreQuaternaire.h"
#include "Hachage.h"
#include "ListeChainee.h"
#include "Reseau.h"

/* L'execution de fichier ReconstitueReseau se fait avec 2 parametres :
    - le premier : le nom du fichier instances sans l'extension .cha
    - le second : un entier (1, 2 ou 3) suivant la SDA utilisee
*/
int main(int argc, char **argv) {
  char filenamecha[104], filenameres[104];
  int chmeth;

  if (argc != 3) {
    printf("usage: %s <file> <numeromethod>\n", argv[0]);
    printf("where numeromethode = 1 if using Liste Chainee\n");
    return 1;
  }

  chmeth = atoi(argv[2]);
  strcpy(filenamecha, argv[1]);
  strcpy(filenameres, argv[1]);
  strcat(filenamecha, ".cha");
  strcat(filenameres, ".res");

  FILE *f1 = fopen(filenamecha, "r");
  if (f1 == NULL) {
    printf("Probleme lecture du fichier %s\n", filenamecha);
    exit(1);
  }

  Chaines *C = lectureChaines(f1);
  fclose(f1);

  Reseau *R;

  if (chmeth == 1) {
    printf("Reconstruit Reseau avec liste chainee\n");
    R = reconstitueReseauListe(C);
  } else {
    if (chmeth == 2) {
      printf("Reconstruit Reseau avec Table de Hachage\n");
      R = reconstitueReseauHachage(C, C->nbChaines*C->gamma*0.5);
    } else {
      if (chmeth == 3) {
        printf("Reconstruit Reseau avec Arbre Quaternaire\n");
        R = reconstitueReseauArbre(C);
      } else {
        printf("Ressaisir le type (1, 2 ou 3) de SDA a utiliser");
        libererChaines(C);
        return 1;
      }
    }
  }
  libererChaines(C);

  FILE *f2 = fopen(filenameres, "w");
  if (f2 == NULL) {
    printf("Probleme Lecture du fichier %s\n", filenameres);
    exit(1);
  }

  ecrireReseau(R, f2);
  fclose(f2);

  libererReseau(R);

  return 0;
}