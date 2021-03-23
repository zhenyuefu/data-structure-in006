#include "Chaine.h"

#include <math.h>
#include <stdlib.h>

#include "SVGwriter.h"

Chaines* lectureChaines(FILE* f) {
  Chaines* chaine = malloc(sizeof(Chaines));
  char ligne[256];
  int nbChaines, gamma;
  /* première ligne */
  if (fgets(ligne, sizeof(ligne), f) != NULL)
    sscanf(ligne, "%*s %d", &nbChaines);
  chaine->nbChaines = nbChaines;
  /* deuxième ligne */
  if (fgets(ligne, sizeof(ligne), f) != NULL) sscanf(ligne, "%*s %d", &gamma);
  chaine->gamma = gamma;

  int num, nP;
  double x, y;
  CellChaine* L_cell = NULL; /* initialisation de la liste des cellules */

  for (int i = 0; i < chaine->nbChaines; i++) {
    CellChaine* cell = malloc(sizeof(CellChaine));
    fscanf(f, "%d %d", &num, &nP);
    cell->numero = num;
    CellPoint* L_point = NULL; /* initialisation de la liste de points */
    for (int j = 0; j < nP; j++) {
      CellPoint* point = malloc(sizeof(CellPoint));
      fscanf(f, "%lf %lf", &x, &y);
      point->x = x;
      point->y = y;
      point->suiv = L_point; /* on insère le point dans la liste L_point */
      L_point = point;       /* on met à jour notre liste L_point */
    }
    cell->points = L_point;
    cell->suiv = L_cell; /* on insère la cellule dans la liste L_cell */
    L_cell = cell;       /* on met à jour notre liste L_cell */
  }

  chaine->chaines = L_cell;
  return chaine;
}

void afficheChainesSVG(Chaines* C, char* nomInstance) {
  double maxx = 0, maxy = 0, minx = 1e6, miny = 1e6;
  CellChaine* ccour;
  CellPoint* pcour;
  double precx, precy;
  SVGwriter svg;
  ccour = C->chaines;
  while (ccour != NULL) {
    pcour = ccour->points;
    while (pcour != NULL) {
      if (maxx < pcour->x) maxx = pcour->x;
      if (maxy < pcour->y) maxy = pcour->y;
      if (minx > pcour->x) minx = pcour->x;
      if (miny > pcour->y) miny = pcour->y;
      pcour = pcour->suiv;
    }
    ccour = ccour->suiv;
  }
  SVGinit(&svg, nomInstance, 500, 500);
  ccour = C->chaines;
  while (ccour != NULL) {
    pcour = ccour->points;
    SVGlineRandColor(&svg);
    SVGpoint(&svg, 500 * (pcour->x - minx) / (maxx - minx),
             500 * (pcour->y - miny) / (maxy - miny));
    precx = pcour->x;
    precy = pcour->y;
    pcour = pcour->suiv;
    while (pcour != NULL) {
      SVGline(&svg, 500 * (precx - minx) / (maxx - minx),
              500 * (precy - miny) / (maxy - miny),
              500 * (pcour->x - minx) / (maxx - minx),
              500 * (pcour->y - miny) / (maxy - miny));
      SVGpoint(&svg, 500 * (pcour->x - minx) / (maxx - minx),
               500 * (pcour->y - miny) / (maxy - miny));
      precx = pcour->x;
      precy = pcour->y;
      pcour = pcour->suiv;
    }
    ccour = ccour->suiv;
  }
  SVGfinalize(&svg);
}

void ecrireChaines(Chaines* C, FILE* f) {
  fprintf(f, "NbChain: %d\nGamma: %d\n", C->nbChaines, C->gamma);

  for (CellChaine* L_cell = C->chaines; L_cell; L_cell = L_cell->suiv) {
    int taille_L_point = 0;
    for (CellPoint* L_point = L_cell->points; L_point; L_point = L_point->suiv)
      taille_L_point++;
    fprintf(f, "%d %d ", L_cell->numero, taille_L_point);
    for (CellPoint* L_point = L_cell->points; L_point; L_point = L_point->suiv)
      fprintf(f, "%.2f %.2f ", L_point->x, L_point->y);
    fprintf(f, "\n");
  }
}

double longueurChaine(CellChaine* c) {
  double somme = 0;

  for (CellPoint* L1_point = c->points;
       L1_point->suiv /* on vérifie que le prochain point n'est pas NULL */;
       L1_point = L1_point->suiv) {
    CellPoint* p1 = L1_point;
    CellPoint* p2 = p1->suiv;
    somme += sqrt(pow(p2->x - p1->x, 2) + pow(p2->y - p1->y, 2));
  }

  return somme;
}

double longueurTotale(Chaines* C) {
  double somme = 0;

  for (CellChaine* L_cell = C->chaines; L_cell; L_cell = L_cell->suiv)
    somme += longueurChaine(L_cell);

  return somme;
}

int comptePointsTotal(Chaines* C) {
  int n = 0;

  for (CellChaine* chaine = C->chaines; chaine; chaine = chaine->suiv)
    for (CellPoint* point = chaine->points; point; point = point->suiv) n++;

  return n;
}