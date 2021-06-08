#include <stdio.h>
#include <stdlib.h>
#define LIGNES 12
#define COLONNES 26

void demanderPlacementPion();

void afficherMat (char mat[LIGNES][COLONNES])
{
    printf(" ");
    for (int i = 0; i < COLONNES; i++)
        printf(" %c", 97+i);
    printf("\n");

    for(int i=0;i<LIGNES;i++)
    {
        printf("%c", (97 - 32 + i));
        for(int j=0;j<COLONNES;j++)
        {
            printf(" %c",mat[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    char mat[LIGNES][COLONNES] = {{' '}};
    afficherMat(mat);
    demanderPlacementPion();
    return 0;
}

void demanderPlacementPion() {
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
}


