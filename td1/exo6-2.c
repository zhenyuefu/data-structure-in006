#include <malloc.h>
#include <stdio.h>

int echange_pointeur(int** ad_p, int* q) {
  ​​​​​​​printf("Adresse de p dans la fonction = %p\n", ad_p);
  printf("Adresse vers laquelle pointe p dans la fonction = %p\n\n", *ad_p);
  printf("Adresse de q dans la fonction = %p\n", &q);
  printf("Adresse vers laquelle pointe q dans la fonction = %p\n\n", q);
  *ad_p = q;
  printf("Nouvelle adresse de p dans la fonction = %p\n", ad_p);
  printf("Nouvelle adresse vers laquelle pointe p dans la fonction = %p\n",
         *ad_p);
  printf("Valeur vers laquelle pointe p dans la fonction = %d\n\n", **ad_p);
}

int main(void) {
  int* p;
  int* q;
  printf("Adresse de p dans main = %p\n", &p);
  printf("Adresse de q dans main = %p\n\n", &q);
  int i = 1;
  int j = 2;
  printf("Adresse de i = %p\n", &i);
  printf("Adresse de j = %p\n\n", &j);
  p = &i;
  q = &j;
  printf("Adresse vers laquelle pointe p dans main avant exhange = %p\n", p);
  printf("Valeur vers laquelle pointe p avant echeange = %d\n\n", *p);
  echange_pointeur(&p, q);
  printf("Adresse de p dans main apres echange = %p\n", &p);
  printf("Adresse vers laquelle pointe p dans main apres echange = %p\n", p);
  printf("Valeur vers laquelle pointe p dans main apres echange = %d\n", *p);
  printf("Adresse de q dans main apres echange = %p\n", q);
  printf("Adresse vers laquelle pointe q dans main apres echange = %p\n\n", q);
  return 0;
}
​​​​​​​