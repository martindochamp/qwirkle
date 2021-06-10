#include "tuiles.h"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

void remplirStructure(t_tuile *tuile)
{
    tuile->couleur = 4;
    tuile->forme = 0x03;
    // {0x03, 0x04, 0x05, 0x06, 0x07, 0xDB,};
}

void afficherStructure(t_tuile* tuile)
{
    printf("%d", tuile->couleur);

}

void prgmTuiles() {
    printf("Wow ça marche !");
    t_tuile tuile;
    remplirStructure(&tuile);
    afficherStructure(&tuile);
}


