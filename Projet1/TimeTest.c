#include "TimeTest.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "ArbreQuat.h"
#include "Hachage.h"
#include "Reseau.h"

Chaines* generationAleatoire(int nbChaines, int nbPointsChaine, int xmax,
                             int ymax) {
  srand((unsigned)time(NULL));
  Chaines* chaine = malloc(sizeof(Chaines));
  chaine->nbChaines = nbChaines;
  chaine->gamma = nbPointsChaine;
  CellChaine* L_cell = NULL;
  for (int i = 0; i < nbChaines; i++) {
    CellChaine* cell_chaine = malloc(sizeof(CellChaine));
    cell_chaine->numero = i;
    CellPoint* L_point = NULL;
    for (int j = 0; j < nbPointsChaine; j++) {
      CellPoint* point = malloc(sizeof(CellPoint));
      point->x = rand() % xmax;
      point->y = rand() % ymax;
      point->suiv = L_point;
      L_point = point;
    }
    cell_chaine->points = L_point;
    cell_chaine->suiv = L_cell;
    L_cell = cell_chaine;
  }
  chaine->chaines = L_cell;
  return chaine;
}

int main(void) {
  Chaines* c;
  FILE* f = fopen("time_list.txt", "w");
  FILE* f2 = fopen("time_hash.txt", "w");
  clock_t start, end;
  double during;
  for (int i = 500; i <= 5000; i += 500) {
    c = generationAleatoire(i, NB_Points_Chaine, X_MAX, Y_MAX);

    start = clock();
    reconstitueReseauListe(c);
    end = clock();
    during = (double)(end - start) / CLOCKS_PER_SEC;
    fprintf(f, "%d %f\n", i, during);

    start = clock();
    reconstitueReseauHash(c, i * NB_Points_Chaine * 0.7);
    end = clock();
    during = (double)(end - start) / CLOCKS_PER_SEC;
    fprintf(f2, "%d %f ", i, during);

    start = clock();
    reconstitueReseauHash(c, i * NB_Points_Chaine);
    end = clock();
    during = (double)(end - start) / CLOCKS_PER_SEC;
    fprintf(f2, "%f ", during);

    start = clock();
    reconstitueReseauHash(c, i * NB_Points_Chaine * 0.5);
    end = clock();
    during = (double)(end - start) / CLOCKS_PER_SEC;
    fprintf(f2, "%f ", during);

    start = clock();
    reconstitueReseauArbre(c);
    end = clock();
    during = (double)(end - start) / CLOCKS_PER_SEC;
    fprintf(f2, "%f\n", during);
  }

  fclose(f);
  fclose(f2);

  return 0;
}