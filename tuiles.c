#include "tuiles.h"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

void Color(int couleurDuTexte,int couleurDeFond) // fonction d'affichage de couleurs
{
    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,couleurDeFond*16+couleurDuTexte);
}

void remplirStructure(t_tuile *tuile)
{
    tuile->couleur = 4;
    tuile->forme = 0x03;
    // {0x03, 0x04, 0x05, 0x06, 0x07, 0xDB,};
}

void genererDeck(t_tuile* tuiles)
{
    int index = 0;
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            int couleurs[] = {14, 15, 4, 3, 2, 5};
            char formes[] = {0x03, 0x04, 0x05, 0x06, 0x07, 0xDB};
            tuiles[index].couleur = couleurs[i];
            tuiles[index].forme = formes[j];
            index++;
        }
    }
}

void afficherDeck(t_tuile* tuiles)
{
    for (int i = 0; i < 36; i++) {
        Color(tuiles[i].couleur, 0);
        printf("%c", tuiles[i].forme);
        Color(15, 0);

    }
}


void prgmTuiles() {
    printf("Wow ça marche !");
    t_tuile* tuiles = (t_tuile*) malloc(36*sizeof(t_tuile));
    printf("cette tuile : \n%c", tuiles[1].forme);
    genererDeck(tuiles);

    //remplirStructure(&tuile);
    //afficherStructure(&tuile);
}

