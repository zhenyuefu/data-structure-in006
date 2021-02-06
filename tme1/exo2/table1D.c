#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define V 100

void alloue_table(int **t, int n) { *t = malloc(n * sizeof(int)); }
void remplir_table(int *t, int n) {
  srand((unsigned)time(NULL));
  for (int i = 0; i < n; i++) {
    t[i] = rand() % V;
  }
}
void desalloue_table(int *t, int n) { free(t); }
void afficher_table(int *t, int n) {
  printf("[ ");
  for (int i = 0; i < n;) {
    printf("%d ", t[i]);
  }
  printf(" ]\n");
}

int fct1(int *t, int n) {
  int somme = 0;
  int x, x2 = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      x = t[i] - t[j];
      x2 = x * x;
      somme += x2;
    }
  }
  return somme;
}

int fct2(int *t, int n) {
  int somme = 0;
  int temp = 0;
  for (int i = 0; i < n; i++) {
    somme += pow(t[i], 2);
    temp += t[i];
  }
  somme *= n * 2;
  somme -= pow(temp, 2) * 2;
}

int main(void) {
  int *t;
  // struct timespec start1, end1, start2, end2;
  clock_t start, end;
  double d;
  for (int n = 100; n <= 10000; n += 100) {
    alloue_table(&t, n);
    remplir_table(t, n);

    printf("%d ", n);
    // timespec_get(&start1, TIME_UTC);
    start = clock();
    fct1(t, n);
    // timespec_get(&end1, TIME_UTC);
    end = clock();
    d = (double)(end - start) / CLOCKS_PER_SEC;
    printf("%f ", d);

    start = clock();
    // timespec_get(&start2, TIME_UTC);
    fct2(t, n);
    end = clock();
    // timespec_get(&end2, TIME_UTC);
    d = (double)(end - start) / CLOCKS_PER_SEC;
    printf("%f\n", d);

    // time_t d_sec1 = end1.tv_sec - start1.tv_sec;
    // long d_nsec1 = end1.tv_nsec - start1.tv_nsec;
    // long duration1 = d_sec1 * 1E9 + d_nsec1;

    // time_t d_sec2 = end2.tv_sec - start2.tv_sec;
    // long d_nsec2 = end2.tv_nsec - start2.tv_nsec;
    // long duration2 = d_sec2 * 1E9 + d_nsec2;
    // printf("%d %f %f\n", n, (double)duration1 / 1000000,
    //  (double)duration2 / 1000000);

    desalloue_table(t, n);
  }
  return 0;
}