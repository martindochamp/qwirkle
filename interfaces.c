#include "interfaces.h"
#include "tuiles.h"
#include "plateau.h"

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void afficherReglesPages(int selection);

void reglesDuJeu() {
    int selection = 1;
    int res;
    do {
        if (res == 75 && selection > 1)
            selection--;
        if (res == 77 && selection < 4)
            selection++;

        afficherReglesPages(selection);

        while (!kbhit());
        res = getch();
    } while(selection == 0);
}

void afficherReglesPages(int selection) {
    system("cls");
    positionnerCurseur(48, 4);
    Color(11, 0);
    printf("%c%c%c", 0xCD, 0xCD, 0xCD);

    Color(15, 0);
    printf(" R%cgles du jeu ", 0x8A);

    Color(11, 0);
    printf("%c%c%c", 0xCD, 0xCD, 0xCD);

    if (selection == 1) {
        positionnerCurseur(14, 7);
        Color(7, 0);
        printf("%c Chaque joueur dispose de 6 tuiles. A", 0x10);
        positionnerCurseur(14, 8);
        printf("  son tour, il en place une %c condition", 0x85);
        positionnerCurseur(14, 9);
        printf("  d'avoir un attribut en commun : forme ");
        positionnerCurseur(14, 10);
        printf("  ou couleur.");

        positionnerCurseur(14, 12);
        printf("%c L'astuce consiste %c placer ses pi%cces", 0x10, 0x85, 0x8A);
        positionnerCurseur(14, 13);
        printf("  %c des endroits strat%cgiques, comme par", 0x85, 0x82);
        positionnerCurseur(14, 14);
        printf("  exemple des intersections, pour marquer");
        positionnerCurseur(14, 15);
        printf("  un maximum de points");

        positionnerCurseur(14, 17);        printf("  - Mode normal : ");
        Color(15, 0);
        printf("108 Tuiles");
        positionnerCurseur(14, 18);
        Color(7, 0);        printf("  - Mode d%cgrad%c : ", 0x82, 0x82);
        Color(15, 0);
        printf("36 Tuiles");
        positionnerCurseur(14, 19);
        Color(7, 0);
        printf("  - Zone de jeu : ");
        Color(15, 0);
        printf("12x26");

        t_tuile demo[7][10];
        for (int i = 0; i < 7; i++)
            for (int j = 0; j < 10; j++) {
                demo[i][j].couleur = 0;
                demo[i][j].forme = ' ';
            }

        //Placement tuiles
        demo[3][0].couleur = 2;
        demo[3][0].forme = 0x05;

        demo[3][1].couleur = 15;
        demo[3][1].forme = 0x05;

        demo[2][1].couleur = 15;
        demo[2][1].forme = 0x04;

        demo[1][1].couleur = 15;
        demo[1][1].forme = 0x03;

        demo[0][1].couleur = 15;
        demo[0][1].forme = 0x06;

        demo[1][0].couleur = 3;
        demo[1][0].forme = 0x03;

        demo[1][2].couleur = 4;
        demo[1][2].forme = 0x03;

        demo[1][3].couleur = 14;
        demo[1][3].forme = 0x03;

        demo[1][4].couleur = 2;
        demo[1][4].forme = 0x03;

        demo[1][5].couleur = 5;
        demo[1][5].forme = 0x03;

        demo[0][5].couleur = 5;
        demo[0][5].forme = 0x04;

        demo[2][5].couleur = 5;
        demo[2][5].forme = 0xFE;

        demo[2][6].couleur = 3;
        demo[2][6].forme = 0xFE;

        demo[2][7].couleur = 14;
        demo[2][7].forme = 0xFE;

        demo[1][7].couleur = 14;
        demo[1][7].forme = 0x0F;

        demo[0][7].couleur = 14;
        demo[0][7].forme = 0x04;

        demo[0][6].couleur = 4;
        demo[0][6].forme = 0x04;

        demo[2][3].couleur = 14;
        demo[2][3].forme = 0x06;

        demo[3][3].couleur = 14;
        demo[3][3].forme = 0x04;

        demo[4][3].couleur = 14;
        demo[4][3].forme = 0x05;

        demo[5][3].couleur = 14;
        demo[5][3].forme = 0xFE;

        demo[6][3].couleur = 14;
        demo[6][3].forme = 0x0F;

        for (int i = 0; i < 7; i++)
            for (int j = 0; j < 10; j++) {
                positionnerCurseur(80+(i*2), 10+j);
                Color(demo[i][j].couleur, 0);
                printf("%c", demo[i][j].forme);
            }

    }
}
