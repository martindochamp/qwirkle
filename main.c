#include <stdio.h>
#include <stdlib.h>
#define LIGNES 12
#define COLONNES 26


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
            mat[i][j]='1';
            printf(" %c",mat[i][j]);
        }
        printf("\n");
    }
}

int main()
{   char mat[LIGNES][COLONNES];
    afficherMat (mat);
    return 0;
}
