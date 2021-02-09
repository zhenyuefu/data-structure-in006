#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "matrix.h"

int main(void) {
  int *mat_sup, *mat_inf;
  clock_t start, end;
  double d;
  srand((unsigned)time(NULL));
  for (int n = 100; n <= 1000; n += 50) {
    printf("%d ", n);
    alloue_matrice_triangulaire(&mat_sup, n);
    alloue_matrice_triangulaire(&mat_inf, n);

    int *mat1, *mat2, *res1, *res2;

    remplir_matrice_triangulaire(mat_sup, n);
    remplir_matrice_triangulaire(mat_inf, n);

    alloue_matrice(&mat1, n);
    alloue_matrice(&mat2, n);
    alloue_matrice(&res1, n);
    alloue_matrice(&res2, n);

    int loc = 0;
    for (int i = 0; i < n; i++) {
      for (int j = i; j < n; j++) {
        mat1[n * i + j] = mat_sup[loc++];
      }
    }
    loc = 0;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j <= i; j++) {
        mat2[n * i + j] = mat_inf[loc++];
      }
    }

    start = clock();
    mat_produit(mat1, mat2, res1, n);
    end = clock();
    d = (double)(end - start) / CLOCKS_PER_SEC;
    printf("%f ", d);

    start = clock();
    mat_produit_sup_inf(mat_sup, mat_inf, res2, n);
    end = clock();
    d = (double)(end - start) / CLOCKS_PER_SEC;
    printf("%f\n", d);

    desalloue_matrice(mat1, n);
    desalloue_matrice(mat2, n);
    desalloue_matrice_triangulaire(mat_inf, n);
    desalloue_matrice_triangulaire(mat_sup, n);
  }
  return 0;
}