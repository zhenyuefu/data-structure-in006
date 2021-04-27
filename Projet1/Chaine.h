#ifndef __CHAINE_H__
#define __CHAINE_H__

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Liste chainee de points */
typedef struct cellPoint {
  double x, y;            /* Coordonnees du point */
  struct cellPoint *suiv; /* Cellule suivante dans la liste */
} CellPoint;

/* Cellule d une liste (chainee) de chaines */
typedef struct cellChaine {
  int numero;              /* Numero de la chaine */
  CellPoint *points;       /* Liste des points de la chaine */
  struct cellChaine *suiv; /* Cellule suivante dans la liste */
} CellChaine;

/* L'ensemble des chaines */
typedef struct {
  int gamma;           /* Nombre maximal de fibres par cable */
  int nbChaines;       /* Nombre de chaines */
  CellChaine *chaines; /* La liste chainee des chaines */
} Chaines;

/* Retourne la structure Chaines resultant de la lecture de f */
Chaines *lectureChaines(FILE *f);

/* Ecrit/Sauvegarde dans f la structure C */
void ecrireChaines(Chaines *C, FILE *f);

/* Fonction (fournie) d'affichage de la structure C au format SVG */
void afficheChainesSVG(Chaines *C, char *nomInstance);

/* Retourne la longueur physique de la chaine c*/
double longueurChaine(CellChaine *c);

/* Retourne la longueur totale des chaines contenues dans C */
double longueurTotale(Chaines *C);

/* Retourne le nombre total de points contenus dans la structure C (les doublons
   sont comptabilisés plusieurs fois) */
int comptePointsTotal(Chaines *C);

/* Libere l'ensemble des points de la liste chainee cPoints */
void libererPoints(CellPoint *cPoints);

/* Libere integralement la memoire occupee par la structure C */
void libererChaines(Chaines *C);

#endif
