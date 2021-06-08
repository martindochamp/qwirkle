#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define LIGNES 12
#define COLONNES 26

void demanderPlacementPion(int* coordsCoup);
void jouerCoup(char map[COLONNES][LIGNES]);

void afficherMat(char mat[COLONNES][LIGNES])
{
    printf(" ");
    for (int i = 0; i < COLONNES; i++)
        printf(" %c", 97+i);
    printf("\n");

    for(int i = 0; i < LIGNES; i++)
    {
        printf("%c", (97 - 32 + i));
        for(int j = 0; j < COLONNES; j++)
        {
            printf(" ");
            printf("%c", mat[j][i]);
        }
        printf("\n");

    }
}

int main()
{
    char mat[COLONNES][LIGNES] = {{' '}};

    bool jeuEnCours = true;

    while (jeuEnCours) {
        afficherMat(mat);
        jouerCoup(mat);
        system("cls");
    }

    return 0;
}

void demanderPlacementPion(int* coordsCoup) {
    printf("\nQue voulez vous jouer ?\n");
    char x, y;

    do {
        fflush(stdin);
        x = getc(stdin);
    } while (!(x >= 'a' && x <= 'z'));

    do {
        fflush(stdin);
        y = getc(stdin);
    } while (!(y >= 'A' && y <= 'L'));

    coordsCoup[0] = x;
    coordsCoup[1] = y;
}


void jouerCoup(char map[COLONNES][LIGNES]) {
    int coordsCoup[2];
    demanderPlacementPion(coordsCoup);

    printf("\nCoup en %c%c", coordsCoup[0], coordsCoup[1]);
    printf("\n x = %d y = %d", coordsCoup[0] - 97, coordsCoup[1] - 65);
    Sleep(3000);
    map[coordsCoup[0] - 97][coordsCoup[1] - 65] = 'X';
}

