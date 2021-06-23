#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <stdbool.h>

#include "tuiles.h"
#include "plateau.h"

void jouerPlacement(t_tuile** plateau, t_tuile* main, int tuile, int x, int y) {
    plateau[x][y].couleur = main[tuile].couleur;
    plateau[x][y].forme = main[tuile].forme;

    positionnerCurseur((x+1)*2 + MARGEX, y+1 + MARGEY);
    Color(plateau[x][y].couleur, 0);
    printf("%c", plateau[x][y].forme);
    Color(15, 0);
}

bool placementValide(t_tuile** plateau, char* erreur, t_tuile* main, int tuile, int x, int y, int coup) {
    //Le premier coup est toujours bon
    if (coup == 0)
        return true;

    int directions[4] = {1, -1, 0, 0};
    bool couleurPresente = false, formePresente = false, couleurDifferente = false, formeDifferente = false;

    for (int i = 0; i < 4; i++) {
        int j = 1;
        while (x+(directions[i]*j) < 26 && x+(directions[i]*j) > 0 &&
                y+(directions[3-i]*j) < 12 && y+(directions[3-i]*j) > 0) {
            if (plateau[x+(directions[i]*j)][y+(directions[3-i]*j)].forme != ' ') {
                if (plateau[x+(directions[i]*j)][y+(directions[3-i]*j)].couleur == main[tuile].couleur)
                    couleurPresente = true;
                if (plateau[x+(directions[i]*j)][y+(directions[3-i]*j)].forme == main[tuile].forme)
                    formePresente = true;
                if (plateau[x+(directions[i]*j)][y+(directions[3-i]*j)].couleur != main[tuile].couleur)
                    couleurDifferente = true;
                if (plateau[x+(directions[i]*j)][y+(directions[3-i]*j)].forme != main[tuile].forme)
                    formeDifferente = true;
            } else
                break;
            j++;
        }
    }

    if ((couleurDifferente && !formeDifferente) || (!couleurDifferente && formeDifferente)
        && (formePresente || couleurPresente))
        return true;

    return false;
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

    *tuile = tuileTemp-49;
    *coordsX = x;
    *coordsY = y;
}

void initialiserPlateau(t_tuile** plateau) {
    for (int i = 0; i < COLONNES; i++)
        for (int j = 0; j < LIGNES; j++) {
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
            Color(plateau[j][i].couleur, 0);
            printf("%c ", plateau[j][i].forme);
            Color(15, 0);
        }
    }
    afficherBordure();
    afficherTitre();
}

//Fonction récupérer sur les ressources de campus, le nom des variables est légérement modifié
void positionnerCurseur(int x, int y){
    COORD coords;
    coords.X = x;
    coords.Y = y;
    SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ), coords);
}

int calculPoints(t_tuile** plateau, int x, int y)
{
    int points = 0;
    int bonus = 6;
    int coin = 2;
    int i = 0;
    int tuilesEnX = 0, tuilesEnY = 0;

    while (plateau[x+i][y].forme != ' ' && x+i<26){
        tuilesEnX++;
    }


    while (plateau[x-i][y].forme != ' ' && x-i>-1){
        tuilesEnX++;
    }


    while (plateau[x][y+i].forme != ' ' && y+i<12){
        tuilesEnY++;
    }


    while (plateau[x][y-i].forme != ' ' && y-i>-1)
    {
        tuilesEnY++;
    }

    if (tuilesEnX != 0 && tuilesEnY != 0)
        points++;

    tuilesEnX++;
    tuilesEnY++;

    if (tuilesEnX == 6)
        points += 6;

    if (tuilesEnY == 6)
        points += 6;

    points += tuilesEnX;
    points += tuilesEnY;

    return points;
}
