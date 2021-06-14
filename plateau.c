#include <stdlib.h>
#include <stdio.h>
#include <windows.h>

#include "tuiles.h"
#include "plateau.h"

void initialiserPlateau(t_tuile** plateau) {
    for (int i = 0; i < LIGNES; i++)
        for (int j = 0; j < COLONNES; j++) {
            plateau[i][j].couleur = 0;
            plateau[i][j].forme = ' ';
        }
}

void afficherMain(t_tuile** mains, int joueur) {
    positionnerCurseur(70, 5);
    printf("Test");
}

void afficherTitre() {
    positionnerCurseur(MARGEX, 1);
    Color(12, 0);
    printf("%c ", 0x05);
    Color(11, 0);
    printf("QWIRKLE ");
    Color(12, 0);
    printf("%c ", 0x05);
    Color(15, 0);
    //printf("%c QWIRKLE %c", , 0x05);
}

void afficherBordure() {
    for (int i = 0; i < 55; i++) {
        //Bordure en X
        positionnerCurseur(MARGEX+i-1, MARGEY-1);
        printf("%c", 0xCD);
        positionnerCurseur(MARGEX+i-1, MARGEY+12+1);
        printf("%c", 0xCD);

    }

    for (int i = 0; i < 13; i++) {
        //Bordure en Y
        positionnerCurseur(MARGEX-2, MARGEY+i);
        printf("%c", 0xBA);
        positionnerCurseur(MARGEX+(26*2)+2, MARGEY+i);
        printf("%c", 0xBA);
    }

    //Bordure coin
    positionnerCurseur(MARGEX-2, MARGEY-1);
    printf("%c", 0xC9);
    positionnerCurseur(MARGEX+54, MARGEY-1);
    printf("%c", 0xBB);

    positionnerCurseur(MARGEX-2, MARGEY+13);
    printf("%c", 0xC8);
    positionnerCurseur(MARGEX+54, MARGEY+13);
    printf("%c", 0xBC);
}

void afficherPlateau(t_tuile** plateau) {
    initialiserPlateau(plateau);
    system("cls");
    positionnerCurseur(MARGEX, MARGEY);

    printf(" ");
    for (int i = 0; i < COLONNES; i++)
        printf(" %c", 97+i);
    printf("\n");

    for(int i = 0; i < LIGNES; i++)
    {
        positionnerCurseur(MARGEX, MARGEY+i+1);
        printf("%c ", (97 - 32 + i));
        for(int j = 0; j < COLONNES; j++)
        {
            Color(plateau[i][j].couleur, 0);
            printf("%c ", plateau[i][j].forme);
            Color(15, 0);
        }
    }
    afficherBordure();
    afficherTitre();
}

void positionnerCurseur(int x, int y)
{
    COORD coords;

    coords.X = x;
    coords.Y = y;
    SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ), coords);
}
