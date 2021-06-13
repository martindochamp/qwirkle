#include <stdlib.h>
#include <stdio.h>

#include "tuiles.h"
#include "plateau.h"

void initialiserPlateau(t_tuile** plateau) {
    for (int i = 0; i < LIGNES; i++)
        for (int j = 0; j < COLONNES; j++) {
            plateau[i][j].couleur = 0;
            plateau[i][j].forme = ' ';
        }
}

void afficherPlateau(t_tuile** plateau) {
    initialiserPlateau(plateau);
    printf(" ");
    for (int i = 0; i < COLONNES; i++)
        printf(" %c", 97+i);
    printf("\n");

    for(int i = 0; i < LIGNES; i++)
    {
        printf("%c ", (97 - 32 + i));
        for(int j = 0; j < COLONNES; j++)
        {
            Color(plateau[i][j].couleur, 0);
            printf("%c ", plateau[i][j].forme);
            Color(15, 0);
        }
        printf("\n");
    }
}
