#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "interfaces.h"
#include "tuiles.h"
#include "etatJeu.h"

#define LIGNES 12
#define COLONNES 26

void demanderPlacementPion(int* coordsCoup);
void jouerCoup(char map[COLONNES][LIGNES]);
void initialiserMat(char m[COLONNES][LIGNES], int cM[COLONNES][LIGNES]);

void afficherMat(char mat[COLONNES][LIGNES])
{
    printf(" ");
    for (int i = 0; i < COLONNES; i++)
        printf(" %c", 97+i);
    printf("\n");

    for(int i = 0; i < LIGNES; i++)
    {
        printf("%c ", (97 - 32 + i));
        for(int j = 0; j < COLONNES; j++)
        {
            printf("%c ", mat[j][i]);
        }
        printf("\n");

    }
}

int main()
{
    int res;
    do {
        printf("Mode de fonctionnement du prgm : \n");
        printf("1. Test menu\n");
        printf("2. Lisa\n");
        printf("3. Martin\n");
        scanf("%d", &res);
    } while(!(res > 0 && res < 4));

    switch(res) {
    case 1:
        emmaPrgm();
        return 0;
    case 2:
        prgmTuiles();
        return 0;
    case 3:
        preparationJeu();
        return 0;
    }

    char pseudos[4][20];


    char mat[COLONNES][LIGNES];
    int colorMat[COLONNES][LIGNES];

    initialiserMat(mat, colorMat);

    bool jeuEnCours = true;

    while (jeuEnCours) {
        afficherMat(mat);
        jouerCoup(mat);
        system("cls");
    }

    return 0;
}

void demanderPlacementPion(int* coordsCoup)
{
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
    //Sleep(3000);
    map[coordsCoup[0] - 97][coordsCoup[1] - 65] = 0x03;
}

void initialiserMat(char m[COLONNES][LIGNES], int cM[COLONNES][LIGNES]) {
    for (int i = 0; i < LIGNES; i++)
        for (int j = 0; j < COLONNES; j++) {
            m[j][i] = ' ';
            cM[j][i] = 0;
        }
}

