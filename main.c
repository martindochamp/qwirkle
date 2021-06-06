#include <stdio.h>
#include <stdlib.h>
#define LIGNES 12
#define COLONNES 26


void afficherMat (char mat[LIGNES][COLONNES])
{
    char lettres[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

    printf(" ");
    for (int i = 0; i < COLONNES; i++)
        printf(" %c", lettres[i]);
    printf("\n");

    for(int i=0;i<LIGNES;i++)
    {
        printf("%c", (lettres[i] - 32));
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
