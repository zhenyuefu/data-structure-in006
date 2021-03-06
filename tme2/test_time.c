#include <stdio.h>
#include <time.h>

#include "biblioH.h"
#include "biblioLC.h"
#include "entreeSortieLC.h"
#include "iohash.h"

int main(void) {
  int n;
  FILE *fp;
  fp = fopen("time.txt", "w");
  for (n = 1000; n < 50000; n += 1000) {
    BiblioH *bh = charger_n_entrees_hash("GdeBiblio.txt", n);
    Biblio *blc = charger_n_entrees("GdeBiblio.txt", n);

    time_t start, end;
    double d;

    fprintf(fp, "%d ", n);

    start = clock();
    recherche_exemplaires(blc);
    end = clock();
    d = (double)(end - start) / CLOCKS_PER_SEC;

    fprintf(fp, "%f ", d);

    start = clock();
    recherche_exemplaires_hash(bh);
    end = clock();
    d = (double)(end - start) / CLOCKS_PER_SEC;

    fprintf(fp, "%f\n", d);

    liberer_biblio(blc);
    liberer_biblioH(bh);
  }
}
