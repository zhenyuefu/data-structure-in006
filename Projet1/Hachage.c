#include "Hachage.h"

int functionClef(int x, int y) { return y + (x + y) * (x + y + 1) / 2; }

int functionHachage(int cle, int size) {
  return (int)(size * ((double)cle * GOLDEN - (int)(cle * GOLDEN)));
}
