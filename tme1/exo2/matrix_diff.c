#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "matrix.h"

int main(void) {
  int *mat;

  clock_t start, end;
  double d;

  srand((unsigned)time(NULL));

  for (int n = 100; n < 10000; n += 100) {
    alloue_matrice(&mat, n);
    remplir_matrice(mat, n);

    printf("%d ", n);

    start = clock();

    diff1(mat, n);
    end = clock();
    d = (double)(end - start) / CLOCKS_PER_SEC;
    printf("%f ", d);

    start = clock();

    diff2(mat, n);
    end = clock();
    d = (double)(end - start) / CLOCKS_PER_SEC;
    printf("%f\n", d);

    desalloue_matrice(mat, n);
  }
  return 0;
}