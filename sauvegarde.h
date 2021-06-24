#ifndef SAUVEGARDE_H_INCLUDED
#define SAUVEGARDE_H_INCLUDED

#include "tuiles.h"

typedef struct Partie {
    int nbJoueur;
    int nbTour;
    t_tuile** plateau;
    t_tuile** mains;
    t_tuile* pioche;
    int* scores;
    char** pseudos;
    int index;
} t_partie;

void lancerPartie(t_partie partie);
void chargerSauvegardes(t_partie* parties);
void sauvegardeParties(t_partie partie);
void supprimerSauvegardes();
void menuSauvegardes();

#endif // SAUVEGARDE_H_INCLUDED
