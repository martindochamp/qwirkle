#ifndef TUILES_H_INCLUDED
#define TUILES_H_INCLUDED

typedef struct Tuiles
{
    int couleur;
    char forme;
} t_tuile;

void afficherStructure(t_tuile* tuile);

void remplirStructure(t_tuile *tuile);

void prgmTuiles();

#endif // TUILES_H_INCLUDED
