#include <stdio.h>
#include <stdlib.h>


#define V 10000

void alloue_matrice(int **mat, int n) { *mat = malloc(n * n * sizeof(int)); }

void alloue_matrice_triangulaire(int **mat, int n) {
  *mat = malloc(n * (n + 1) / 2 * sizeof(int));
}

void desalloue_matrice(int *mat, int n) { free(mat); }

void desalloue_matrice_triangulaire(int *mat, int n) { free(mat); }

void remplir_matrice_triangulaire(int *mat, int n) {
  
  for (int i = 0; i < n * (n + 1) / 2; i++) {
    *(mat + i) = rand() % V;
  }
}

void remplir_matrice(int *mat, int n) {
 
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      *(mat + i * n + j) = rand() % V;
    }
  }
}

void afficher_matrice(int *mat, int n) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      printf("%-10d", *(mat + i * n + j));
    }
    printf("\n");
  }
}

int diff1(int *mat, int n) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      for (int k = 0; k < n; k++) {
        for (int l = 0; l < n; l++) {
          if (i == k && j == l) continue;
          if (*(mat + i * n + j) == *(mat + k * n + l)) return 0;
        }
      }
    }
  }
  return 1;
}

int diff2(int *mat, int n) {
  int d[V] = {0};
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      d[*(mat + i * n + j)]++;
      if (d[*(mat + i * n + j)] > 1) return 0;
    }
  }
  return 1;
}

void mat_produit(int *mat1, int *mat2, int *res, int n) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      *(res + i * n + j) = 0;
      for (int k = 0; k < n; k++) {
        *(res + i * n + j) += *(mat1 + i * n + k) * *(mat2 + k * n + j);
      }
    }
  }
}

void mat_produit_sup_inf(int *mat_sup, int *mat_inf, int *res, int n) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      res[i * n + j] = 0;
      for (int k = i > j ? i : j; k < n; k++) {
        res[i * n + j] += mat_sup[n * i - i * (i + 1) / 2 + k] *
                          mat_inf[k * (k + 1) / 2 + j];
      }
    }
  }
}
