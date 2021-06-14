#include <stdlib.h>
#include <stdio.h>
#include <windows.h>

#include "tuiles.h"
#include "plateau.h"

void jouerPlacement(t_tuile** plateau, t_tuile* main, int tuile, int x, int y) {

    //plateau[x][y]

}

void recupererPlacement(t_tuile* main, int* tuile, int* coordsX, int* coordsY) {
    int tuileTemp = -1;
    int x = -1;
    int y = -1;

    //On supprime la barre de côté
    for (int i = 0; i < 40; i++)
        for (int j = 0; j < 8; j++) {
            positionnerCurseur(70+i, 8+j);
            printf(" ");
        }

    positionnerCurseur(70, 8);
    Color(14, 0);
    printf("Quelle tuile voulez-vous jouer ?");
    Color(15, 0);
    positionnerCurseur(70, 9);

    do {
        while(!kbhit());
        tuileTemp = getch();
    } while (!(tuileTemp >= 49 && tuileTemp <= 55));

    char strtest[30];
    retournerNomTuile(main[tuileTemp-49], strtest);
    printf("%s", strtest);

    positionnerCurseur(70, 11);
    Color(14, 0);
    printf("Quelle colonne ?");
    Color(15, 0);
    positionnerCurseur(70, 12);

    do {
        while(!kbhit());
        x = getch();
    } while (!(x >= 'a' && x <= 'z'));
    printf(" - %c ", x);

    positionnerCurseur(70, 14);
    Color(14, 0);
    printf("Quelle ligne ?");
    Color(15, 0);
    positionnerCurseur(70, 15);

    do {
        while(!kbhit());
        y = getch();
    } while (!(y >= 'A' && y <= 'L'));
    printf(" - %c ", y);

    *tuile = tuileTemp;
    *coordsX = x;
    *coordsY = y;
}

void initialiserPlateau(t_tuile** plateau) {
    for (int i = 0; i < LIGNES; i++)
        for (int j = 0; j < COLONNES; j++) {
            plateau[i][j].couleur = 0;
            plateau[i][j].forme = ' ';
        }
}

void afficherMain(t_tuile** mains, char** pseudos, int joueur) {

    //Supprime l'ancienne phrase
    for (int i = 0; i < 50; i++) {
        positionnerCurseur(MARGEX+i, 2);
        printf(" ");
    }

    positionnerCurseur(MARGEX, 2);
    Color(11, 0);
    printf("%s ", *(pseudos+joueur));
    Color(15, 0);
    printf("%c vous de jouer !", 0x85);

    positionnerCurseur(70, 5);
    printf("Votre main :");
    positionnerCurseur(70, 6);

    //Affichage tuiles joueurs
    for (int i = 0; i < 6; i++) {
        Color(mains[joueur][i].couleur, 0);
        printf("%c ", mains[joueur][i].forme);
    }
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

void positionnerCurseur(int x, int y){
    COORD coords;
    coords.X = x;
    coords.Y = y;
    SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ), coords);
}
