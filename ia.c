#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "sauvegarde.h"
#include "ia.h"
#include "plateau.h"

void testerCoups(t_tuile plateau[26][12], t_tuile main[6], int* x, int* y, int* tuile, int coup) {

    t_coup meilleurCoup;
    meilleurCoup.x = 0;
    meilleurCoup.y = 0;
    meilleurCoup.point = 0;
    meilleurCoup.numeroTuile = 0;

    for (int i = 0; i < 26; i++)
        for (int j= 0; j < 12; j++)
            if (plateau[i][j].forme == ' ')
                for (int k = 0; k < 6; k++)
                    if (placementValideV2(plateau, main[k], i, j)) {
                        int point = calculPoints(plateau, i, j);
                        if (point >= meilleurCoup.point) {
                            meilleurCoup.x = i;
                            meilleurCoup.y = j;
                            meilleurCoup.point = point;
                        }
                    }

    *x = meilleurCoup.x;
    *y = meilleurCoup.y;
    *tuile = meilleurCoup.numeroTuile;
}
