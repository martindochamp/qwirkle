#ifndef PLATEAU_H_INCLUDED
#define PLATEAU_H_INCLUDED
#include <stdbool.h>
#include "sauvegarde.h"
#define LIGNES 12
#define COLONNES 26
#define MARGE 5
#define MARGEX 10
#define MARGEY 5

void afficherPlateau(t_tuile plateau[26][12]) ;

void afficherMain(t_joueur joueur);

void positionnerCurseur(int x, int y);

void recupererPlacement(t_tuile main[6], int* tuile, int* coordsX, int* coordsY);

void jouerPlacement(t_tuile plateau[26][12], t_tuile tuile, int x, int y);

bool placementValide(t_tuile plateau[26][12], char* erreur, t_tuile main[6], int tuile, int x, int y, int coup);

int calculPoints(t_tuile plateau[26][12], int x, int y);

#endif // PLATEAU_H_INCLUDED
