#include "tuiles.h"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void distribuerTuiles(t_tuile** decks, t_tuile* pioche, int nbJoueurs, int modeDeJeu);

void Color(int couleurDuTexte,int couleurDeFond) // fonction d'affichage de couleurs
{
    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,couleurDeFond*16+couleurDuTexte);
}

void genererPioche(t_tuile* tuiles, int modeDeJeu)
{
    int lim = (modeDeJeu == 1) ? 3 : 1;
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

void distribuerTuiles(t_tuile** mains, t_tuile* pioche, int nbJoueurs, int modeDeJeu) {
    srand(time(NULL));
    for (int i = 0; i < nbJoueurs; i++) {
        for (int j = 0; j < 6; j++) {
            int randomInt;
            do {
                randomInt = rand() % (modeDeJeu == 1 ? 107 : 35);
            } while (pioche[randomInt].forme == ' ');
            mains[i][j] = pioche[randomInt];
            pioche[randomInt].couleur = 0;
            pioche[randomInt].forme = ' ';
        }
    }
}

void afficherMainsJoueurs(t_tuile** mains, char** pseudos, int nbJoueurs) {
    system("cls");
    printf("Mains des joueurs :\n\n");
    for (int i = 0; i < nbJoueurs; i++) {
        printf("- Main de %s\n", pseudos[i]);
        for (int j = 0; j < 6; j++) {
            Color(mains[i][j].couleur, 0);
            printf("%c", mains[i][j].forme);
            Color(15, 0);
        }
        printf("\n");
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
    t_tuile* tuiles = (t_tuile*) malloc(36*sizeof(t_tuile));
    genererPioche(tuiles, 2);
    afficherDeck(tuiles);
}
