#ifndef PLATEAU_H_INCLUDED
#define PLATEAU_H_INCLUDED

#define LIGNES 12
#define COLONNES 26
#define MARGE 5
#define MARGEX 10
#define MARGEY 5

void afficherPlateau(t_tuile** plateau);

void afficherMain(t_tuile** mains, int joueur);

void positionnerCurseur(int x, int y);

#endif // PLATEAU_H_INCLUDED
