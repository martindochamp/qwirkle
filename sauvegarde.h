#ifndef SAUVEGARDE_H_INCLUDED
#define SAUVEGARDE_H_INCLUDED

#include "tuiles.h"
#include <stdbool.h>

typedef struct Joueur {
    bool humain;
    char pseudo[20];
    int score;
    t_tuile main[6];
} t_joueur;

typedef struct Partie {
    int nbJoueur;
    int nbTour;
    int modeDeJeu;
    int index;
    t_joueur joueurs[4];
    t_tuile plateau[26][12];
    t_tuile pioche[108];
} t_partie;

void chargerParties(t_partie* parties);
void sauvegarderPartie(t_partie partie);
void supprimerSauvegardes();
void menuSauvegardes();

void lancerPartie(t_partie partie);

#endif // SAUVEGARDE_H_INCLUDED
