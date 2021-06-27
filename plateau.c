#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <stdbool.h>

#include "tuiles.h"
#include "plateau.h"
#include "sauvegarde.h"

//Fonction récursive, vérifie que la couleur est bonne en fonction de l'axe
bool visiterTuileCouleur(t_tuile p[26][12], t_tuile tuile, int x, int y, int dirX, int dirY) {
    if (p[x+dirX][y+dirY].forme == ' ' || x+dirX < 0 || x+dirX > 25 || y+dirY < 0 || y+dirY > 11)
        return true;
    else if (p[x+dirX][y+dirY].couleur == tuile.couleur)
        visiterTuileCouleur(p, tuile, x+dirX, y+dirY, dirX, dirY);
    else
        return false;
}
//Fonction récursive, vérifie que la forme est bonne en fonction de l'axe
bool visiterTuileForme(t_tuile p[26][12], t_tuile tuile, int x, int y, int dirX, int dirY) {
    if (p[x+dirX][y+dirY].forme == ' ' || x+dirX < 0 || x+dirX > 25 || y+dirY < 0 || y+dirY > 11)
        return true;
    else if (p[x+dirX][y+dirY].forme == tuile.forme)
        visiterTuileForme(p, tuile, x+dirX, y+dirY, dirX, dirY);
    else
        return false;
}

//On place la tuile dans le plateau, et on l'affiche à ses coordonnées
void jouerPlacement(t_tuile plateau[26][12], t_tuile tuile, int x, int y) {
    plateau[x][y].couleur = tuile.couleur;
    plateau[x][y].forme = tuile.forme;

    positionnerCurseur((x+1)*2 + MARGEX, y+1 + MARGEY);
    Color(plateau[x][y].couleur, 0);
    printf("%c", plateau[x][y].forme);
    Color(15, 0);
}
//Vérification si le placement est bon
bool placementValide(t_tuile p[26][12], t_tuile tuile, int x, int y) {

    //Interdit de placer sur une tuile existante
    if (p[x][y].forme != ' ')
        return false;

    //Premier coup sur plateau toujours valide
    int nbTuile = 0;
    for (int i = 0; i < 26; i++)
        for (int j = 0; j < 12; j++)
            if (p[i][j].forme != ' ')
                nbTuile++;

    if (nbTuile == 0)
        return true;

    //Si aucune tuile autour, placement faux
    int nbTuileCotes = 0;
    int dir[4] = {1, -1, 0, 0};
    for (int i = 0; i < 4; i++) {
        if (p[x+dir[i]][y+dir[3-i]].forme != ' ' && x+dir[i] >= 0 && x+dir[i] < 26 && y+dir[3-i] >= 0 && y+dir[3-i] < 12) {
            nbTuileCotes++;
        }
    }

    if (nbTuileCotes == 0)
        return false;

    bool placement = true;
    for (int i = 0; i < 4; i++) {
        if (!(visiterTuileCouleur(p, tuile, x, y,  dir[i], dir[3-i]) || visiterTuileForme(p, tuile, x, y,  dir[i], dir[3-i])))
            placement = false;
    }

    return placement;
}
//On récupére les coordonées et la tuile à jouer souhaitée
void recupererPlacement(t_tuile main[6], int* tuile, int* coordsX, int* coordsY){
    int x = 0;
    int y = 0;

    int nbTuile = 0;
    for (int i = 0; i < 6; i++)
        if (main[i].forme != ' ')
            nbTuile++;

    //Demande tuile à jouer
    int res;
    int tuileSelectionne = 1;
    do {
        if (res == 75 && tuileSelectionne > 1)
            tuileSelectionne--;
        if (res ==  77 && tuileSelectionne < nbTuile)
            tuileSelectionne++;

        positionnerCurseur(70 + (tuileSelectionne-1)*2, 6);
        HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO info;
        info.dwSize = 10;
        info.bVisible = TRUE;
        SetConsoleCursorInfo(consoleHandle, &info);
        while (!kbhit());
        res = getch();
    } while (res != 13);

    //Demande placement curseur sur plateau
    do {
        if (res == 75 && x > 0)
            x--;
        if (res ==  77 && x < 25)
            x++;
        if (res == 72 && y > 0)
            y--;
        if (res ==  80 && y < 11)
            y++;

        positionnerCurseur((x+1)*2 + MARGEX, y+1 + MARGEY);
        HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO info;
        info.dwSize = 10;
        info.bVisible = TRUE;
        SetConsoleCursorInfo(consoleHandle, &info);
        while (!kbhit());
        res = getch();
    } while (res != 13);

    *tuile = tuileSelectionne-1;
    *coordsX = x;
    *coordsY = y;

    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 10;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

void afficherMain(t_joueur joueur) {

    //Supprime l'ancienne phrase
    for (int i = 0; i < 50; i++) {
        positionnerCurseur(MARGEX+i, 2);
        printf(" ");
    }

    for (int i = 0; i < 20; i++) {
        positionnerCurseur(70+i, 6);
        printf(" ");
    }

    positionnerCurseur(MARGEX, 2);
    Color(15, 0);
    printf("%s ", joueur.pseudo);
    Color(7, 0);
    printf("%c vous de jouer !", 0x85);

    positionnerCurseur(70, 5);
    printf("Votre main :");
    positionnerCurseur(70, 6);

    //Affichage tuiles joueurs
    for (int i = 0; i < 6; i++) {
        Color(joueur.main[i].couleur, 0);
        positionnerCurseur(70+(i*2), 6);
        printf("%c", joueur.main[i].forme);
    }

}

void afficherTitre() {
    positionnerCurseur(MARGEX, 1);
    Color(11, 0);
    printf("%c %c ", 0x04, 0x06);
    Color(15, 0);
    printf("QWIRKLE");
    Color(11, 0);
    printf(" %c %c", 0x06, 0x04);
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

    positionnerCurseur(MARGEX-2, MARGEY-1);
    printf("%c", 0xC9);
    positionnerCurseur(MARGEX+54, MARGEY-1);
    printf("%c", 0xBB);

    positionnerCurseur(MARGEX-2, MARGEY+13);
    printf("%c", 0xC8);
    positionnerCurseur(MARGEX+54, MARGEY+13);
    printf("%c", 0xBC);
}

void afficherPlateau(t_tuile plateau[26][12]) {
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

//Fonction récupérée sur les ressources de campus, le nom des variables est légérement modifié
void positionnerCurseur(int x, int y){
    COORD coords;
    coords.X = x;
    coords.Y = y;
    SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ), coords);
}

int calculPoints(t_tuile plateau[26][12], int x, int y) {
    int points = 0, tuilesEnX = 0, tuilesEnY = 0;
    int directions[4] = {1, -1, 0, 0};

    for (int i = 0; i < 4; i++) {
        int j = 1;
        while (x+(directions[i]*j) < 26 && x+(directions[i]*j) > 0 &&
                y+(directions[3-i]*j) < 12 && y+(directions[3-i]*j) > 0) {
            if (plateau[x+(directions[i]*j)][y+(directions[3-i]*j)].forme != ' ')
                if (directions[i] == 1 || directions[i] == -1)
                    tuilesEnX++;
                else
                    tuilesEnY++;
            else
                break;
            j++;
        }
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

    return points-1;
}
