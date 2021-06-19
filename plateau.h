#ifndef PLATEAU_H_INCLUDED
#define PLATEAU_H_INCLUDED

#define LIGNES 12
#define COLONNES 26
#define MARGE 5
#define MARGEX 10
#define MARGEY 5

void afficherPlateau(t_tuile** plateau);

void afficherMain(t_tuile** mains, char** pseudos, int joueur);

void positionnerCurseur(int x, int y);

void recupererPlacement(t_tuile* main, int* tuile, int* coordsX, int* coordsY);

void jouerPlacement(t_tuile** plateau, t_tuile* main, int tuile, int x, int y);

bool placementValide(t_tuile** plateau, char* erreur, t_tuile* main, int tuile, int x, int y, int coup);

#endif // PLATEAU_H_INCLUDED
