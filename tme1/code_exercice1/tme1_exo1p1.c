#include <stdio.h>
#include <stdlib.h>

const static int len = 10;

int main(void) {
  int *tab;
  unsigned int i;

  tab = (int *)malloc(len * sizeof(int));

  for (i = 0; i < len; i++) {
    tab[i] = i;
  }

  free(tab);
  return 0;
}
