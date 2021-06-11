#include "tuiles.h"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

void Color(int couleurDuTexte,int couleurDeFond) // fonction d'affichage de couleurs
{
    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,couleurDeFond*16+couleurDuTexte);
}

void genererDeck(t_tuile* tuiles, int modeDeJeu)
{
    int lim = (modeDeJeu == 1) ? 1 : 4;
    int index = 0;
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 6; j++)
            for (int k = 0; k < lim; k++) {
                int couleurs[] = {14, 15, 4, 3, 2, 5};
                char formes[] = {0x03, 0x04, 0x05, 0x0F, 0x06, 0xFE};
                tuiles[index].couleur = couleurs[i];
                tuiles[index].forme = formes[j];
                index++;
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
    system("cls");
    printf("VOICI LES TUILES\n\n");
    t_tuile* tuiles = (t_tuile*) malloc(36*sizeof(t_tuile));
    genererDeck(tuiles, 1);
    afficherDeck(tuiles);

}
