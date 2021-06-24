#include "interfaces.h"
#include "tuiles.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void afficherReglesPages(int selection);

void ReglesJeu()
{//Règles du sujet !
    printf("1. Materiel: \n"); //en gras
    printf("  - Mode normal : 108 tuiles pour 6 formes et 6 couleurs. Chaque forme est donc presente 3 fois dans une meme couleur dans la pioche.\n");
    printf("  - Mode degrade : 36 tuiles pour 6 formes et 6 couleurs. Chaque forme n est presente qu une fois dans une meme couleur dans la pioche.\n");
    printf("  - Zone de jeu de 12 x 26 cases \n\n");
    printf("2. But du jeu: \nAligner des tuiles ayant des symboles de formes ou de couleurs identiques (mais pas les deux) de facon ");
    printf("a realiser des combinaisons rapportant un maximum de points.\n\n");
    printf("3. Preparation:\n"); //en gras
    printf("La pioche contient les 108 tuiles qui seront prises au hasard par les joueurs pour completer leur pupitre apres chaque tour.\n\n");
    printf("4. Debut de partie:\n"); //en gras
    printf("L ordinateur demande si on joue en mode degrade ou normal (contenu de la pioche different) ainsique le nombre de joueurs pour la");
    printf("partie, entre 2, 3 et 4.\nIl enregistre les pseudos pour chaque joueur.\n\n");
    printf("L ordinateur pioche au hasard six tuiles dans la pioche et les place sur le pupitre de chaque joueur, en les maintenant cachees de facon a ce qu aucun autre ");
    printf("joueur ne puisse voir les symboles. Ces tuiles forment la « main » du joueur. Les tuiles restantes forment la « pioche ».\n\n");
    printf("L ordinateur demarre la partie avec le joueur 1 (premier pseudo enregistre). Il revele le pupitre du joueur concerne et lance la partie en permettant au joueur \n");
    printf("concerne de poser une ou plusieurs tuiles à l endroit de son choix sur la zone de jeu. \n\n");
    printf("Apres la pose des tuiles par le joueur sur la zone de jeu, l ordinateur calcule les points obtenus, affiche les points du coup et le cumul depuis le debut de \n");
    printf("partie pour ce joueur. L’ordinateur preleve aleatoirement de nouvelles tuiles dans la pioche pour avoir à nouveau 6 tuiles sur le pupitre du joueur, \n");
    printf("tout en masquant de nouveau les 6 tuiles. Le joueur ne voit donc pas les nouvelles tuiles piochees.");
    printf("En appuyant sur la barre d espace, l ordinateur passe au joueur suivant.\n");
    printf("Lorsque tous les joueurs ont joue, l ordinateur demande si on veut arreter la partie ou passer au tour suivant pour l ensemble des joueurs.\n\n");
    printf("Les joueurs jouent a tour de role dans le sens des aiguilles d une montre (ou le sens croissant et cyclique des numeros de joueur).\n`\n");
    printf("5. Deroulement de la partie:\n"); //en gras
    printf("A son tour, un joueur voit son pupitre revele a l ecran. Il peut effectuer l une de ces trois actions :\n");
    //une partie en gras
    printf("A. Ajouter une tuile a une ligne ou a une colonne. L ordinateur masque les tuiles restantes sur le pupitre et pioche une tuile dans la reserve pour en avoir ");
    printf("a nouveau six tuiles sur le pupitre du joueur.");
    //une partie en gras
    printf("B. Ajouter deux tuiles ou plus a une ligne (ou colonne). Toutes les tuiles jouees a partir de la main du joueur doivent partager une caracteristique, a savoir\n");
    printf("la couleur ou la forme. Les tuiles du joueur doivent toujours etre posees sur la meme ligne (ou colonne) (il se peut qu elles ne se touchent pas).\n");
    printf("Ensuite, l ordinateur masque les tuiles restantes sur le pupitre et pioche une ou plusieurs tuiles dans la reserve pour en avoir a nouveau six sur le pupitre du joueur.\n");
    //une partie en gras
    printf("C. Echanger tout ou partie des tuiles de sa main contre differentes tuiles de la reserve, et passer son tour (sans jouer de tuile).\n\n");
    printf("Ajouter des tuiles a une ligne (ou colonne)\n"); //Couleur orange
    printf("Chacun a leur tour, les joueurs ajoutent des tuiles a la ligne creee au premier tour sans deborder l espace de jeu. Tous les coups joues doivent etre lies a la ligne existante.");
}


void afficherMenu()
{
    int ch1;
    char key='q';

    do{
        system("cls");
        printf("Bonjour et bienvenue dans le Qwirkle!\n");
        printf("1. Consulter les regles du jeu\n");
        printf("2. Demarrer une nouvelle partie\n");
        printf("3. Reprendre une partie sauvegardee\n");
        printf("4. Consulter l'ensemble des scores des joueurs\n");
        printf("5. Quitter le jeu\n");
        fflush(stdin);
        scanf("%d", &ch1);

    switch(ch1){
        case 1:
            printf("Pour retourner au menu principal, tapez q");
            ReglesJeu();
            if (kbhit()){
                system("CLS");
                afficherMenu();
            }
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            printf("Au revoir et a bientot !");
            break;
        default :
            printf("Faux");
        }
    }while((ch1<1)||(ch1>4));
}

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
