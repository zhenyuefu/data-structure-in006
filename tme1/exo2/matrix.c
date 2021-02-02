#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define V 10000

void alloue_matrice(int **mat, int n) { *mat = malloc(n * n * sizeof(int)); }

void desalloue_matrice(int *mat, int n) { free(mat); }

void remplir_matrice(int *mat, int n) {
  srand(time(NULL));
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

int main(void) {
  int *mat;
  struct timespec start1, end1, start2, end2;
  for (int n = 100; n < 10000; n += 100) {
    alloue_matrice(&mat, n);
    remplir_matrice(mat, n);

    timespec_get(&start1, TIME_UTC);
    diff1(mat, n);
    timespec_get(&end1, TIME_UTC);
    time_t d_sec1 = end1.tv_sec - start1.tv_sec;
    long d_nsec1 = end1.tv_nsec - start1.tv_nsec;
    long duration1 = d_sec1 * 1E9 + d_nsec1;

    timespec_get(&start2, TIME_UTC);
    diff2(mat, n);
    timespec_get(&end2, TIME_UTC);

    time_t d_sec2 = end2.tv_sec - start2.tv_sec;
    long d_nsec2 = end2.tv_nsec - start2.tv_nsec;
    long duration2 = d_sec2 * 1E9 + d_nsec2;
    printf("%d %d %d\n", n, duration1, duration2);

    desalloue_matrice(mat, n);
  }
  return 0;
}
