#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>

#include "etatJeu.h"
#include "tuiles.h"
#include "plateau.h"
#include "sauvegarde.h"

int demanderModeDeJeu();
int demanderNombreJoueur();
void demanderPseudos(t_joueur joueurs[4], int joueurHumain);
void afficherPseudos(int nbJoueurs, char pseudos[4][20]);
void lancementJeu(int nbJoueurs, char** pseudos, int modeDeJeu);
void afficherErreur(char* erreur);
int demanderTypeJoueur(int nbJoueur);

int demanderTypeJoueur(int nbJoueur) {
    char nombres[4][40] = {
        {
        ' ',' ',' ',' ',' ',' ',' ', 0xBA,
        ' ',' ',' ',' ',' ',' ',' ', 0xBA,
        ' ',' ',' ',' ',' ',' ',' ', 0xBA,
        ' ',' ',' ',' ',' ',' ',' ', 0xBA,
        ' ',' ',' ',' ',' ',' ',' ', 0xBA,
        },{
        0xCD,0xCD,0xCD,0xCD,0xCD,0xCD,0xCD,0xBB,
        ' ',' ',' ',' ',' ',' ',' ', 0xBA,
        0xC9,0xCD,0xCD,0xCD,0xCD,0xCD,0xCD,0xBC,
        0xBA,' ',' ',' ',' ',' ',' ',' ',
        0xC8,0xCD,0xCD,0xCD,0xCD,0xCD,0xCD,0xCD
        },
        {
        0xCD,0xCD,0xCD,0xCD,0xCD,0xCD,0xCD,0xBB,
        ' ',' ',' ',' ',' ',' ',' ', 0xBA,
        ' ',0xCD,0xCD,0xCD,0xCD,0xCD,0xCD,0xB9,
        ' ',' ',' ',' ',' ',' ',' ',0xBA,
        0xCD,0xCD,0xCD,0xCD,0xCD,0xCD,0xCD,0xBC
        },
        {
        0xBA,' ',' ',' ',' ',' ',' ',0xBA,
        0xBA,' ',' ',' ',' ',' ',' ', 0xBA,
        0xC8,0xCD,0xCD,0xCD,0xCD,0xCD,0xCD,0xB9,
        ' ',' ',' ',' ',' ',' ',' ',0xBA,
        ' ',' ',' ',' ',' ',' ',' ',0xBA
        },
    };

    int joueurHumain = 1;
    int res;

    system("cls");
    positionnerCurseur(55, 13);
    Color(15, 0);
    printf("Nombre de joueur réel ?");
    Color(7, 0);
    positionnerCurseur(55, 14);
    printf("Les autres seront des bots.", 0x1E, 0x8A);
    positionnerCurseur(55, 15);
    printf("%c Augmenter avec les fl%cches", 0x1E, 0x8A);
    positionnerCurseur(55, 16);
    printf("%c Valider avec entr%ce", 0x1F, 0x82);
    positionnerCurseur(60, 0);

    do {
        if (res == 80 && joueurHumain > 1)
            joueurHumain--;
        if (res == 72 && joueurHumain < nbJoueur)
            joueurHumain++;

        int index = 0;
        Color(6, 0);
        for (int i = 0; i < 5; i++)
            for (int j = 0; j < 8; j++) {
                positionnerCurseur(44+j, 12+i);
                printf("%c", nombres[joueurHumain-2][index]);
                index++;
            }

        while(!kbhit());
        res = getch();
    } while(res != 13);
    return joueurHumain;
}

void preparationJeu() {
    int modeDeJeu = demanderModeDeJeu();
    int nbJoueurs = demanderNombreJoueur();
    int joueurHumain = demanderTypeJoueur(nbJoueurs);

    t_joueur joueurs[4];
    demanderPseudos(joueurs, joueurHumain);

    //On génére le pseudo des joueurs non humains
    char pseudosAleas[10][20] = {
        "Jean", "Mathieu", "Emilie", "Damien", "Fred",
        "Guillaume", "Rose", "Ambre", "Camille", "Ryujin"
    };

    srand(time(NULL));
    for (int i = joueurHumain-1; i < nbJoueurs; i++) {
        strcpy(joueurs[i].pseudo, pseudosAleas[rand() % 10]);
        joueurs[i].humain = false;
    }

    //Récupération de toutes les données pour créer la partie

    //On génère la pioche en fonction du mode de jeu, puis on mélange les tuiles
    t_tuile pioche[108];
    genererPioche(pioche, modeDeJeu);

    //Distribution des tuiles dans la main
    int index = 0;
    for (int i = 0; i < nbJoueurs; i++) {
        distribuerTuiles(joueurs[i].main, pioche, &index);
        joueurs[i].score = 0;
    }

    t_tuile plateau[26][12];

    for (int i = 0; i < COLONNES; i++)
        for (int j = 0; j < LIGNES; j++) {
            plateau[i][j].couleur = 0;
            plateau[i][j].forme = ' ';
        }

    t_partie nouvellePartie;
    memcpy(nouvellePartie.joueurs, joueurs, sizeof(nouvellePartie.joueurs));
    memcpy(nouvellePartie.pioche, pioche, sizeof(nouvellePartie.pioche));
    memcpy(nouvellePartie.plateau, plateau, sizeof(nouvellePartie.plateau));

    nouvellePartie.index = index;
    nouvellePartie.nbTour = 0;
    nouvellePartie.nbJoueur = nbJoueurs;

    lancerPartie(nouvellePartie);
}

int demanderModeDeJeu() {
    int modeDeJeu = 1;
    int res;
    do {
        system("cls");
        if (res == 75 && modeDeJeu == 2)
            modeDeJeu = 1;
        if (res == 77 && modeDeJeu == 1)
            modeDeJeu = 2;

        positionnerCurseur(50, 11);
        Color(11, 0);
        printf("%c%c%c ", 0xCD, 0xCD, 0xCD);
        Color(15, 0);
        printf("Mode de jeu ");
        Color(11, 0);
        printf("%c%c%c ", 0xCD, 0xCD, 0xCD);

        if (modeDeJeu == 1) {
            positionnerCurseur(42, 13);
            Color(11, 0);
            printf("%c %c ", 0x05, 0x03);
            Color(15, 0);
            printf("Normal ");
            Color(11, 0);
            printf("%c %c", 0x03, 0x05);

            positionnerCurseur(66, 13);
            Color(7, 0);
            printf("D%cgrad%c ", 0x82, 0x82);

        } else {
            positionnerCurseur(46, 13);
            Color(7, 0);
            printf("Normal");

            positionnerCurseur(62, 13);
            Color(11, 0);
            printf("%c %c ", 0x05, 0x03);
            Color(15, 0);
            printf("D%cgrad%c ", 0x82, 0x82);
            Color(11, 0);
            printf("%c %c", 0x03, 0x05);
        }

        while(!kbhit());
        res = getch();
    } while (res != 13);
    return modeDeJeu;
}

int demanderNombreJoueur() {
    char nombres[3][40] = {
        {
        0xCD,0xCD,0xCD,0xCD,0xCD,0xCD,0xCD,0xBB,
        ' ',' ',' ',' ',' ',' ',' ', 0xBA,
        0xC9,0xCD,0xCD,0xCD,0xCD,0xCD,0xCD,0xBC,
        0xBA,' ',' ',' ',' ',' ',' ',' ',
        0xC8,0xCD,0xCD,0xCD,0xCD,0xCD,0xCD,0xCD
        },
        {
        0xCD,0xCD,0xCD,0xCD,0xCD,0xCD,0xCD,0xBB,
        ' ',' ',' ',' ',' ',' ',' ', 0xBA,
        ' ',0xCD,0xCD,0xCD,0xCD,0xCD,0xCD,0xB9,
        ' ',' ',' ',' ',' ',' ',' ',0xBA,
        0xCD,0xCD,0xCD,0xCD,0xCD,0xCD,0xCD,0xBC
        },
        {
        0xBA,' ',' ',' ',' ',' ',' ',0xBA,
        0xBA,' ',' ',' ',' ',' ',' ', 0xBA,
        0xC8,0xCD,0xCD,0xCD,0xCD,0xCD,0xCD,0xB9,
        ' ',' ',' ',' ',' ',' ',' ',0xBA,
        ' ',' ',' ',' ',' ',' ',' ',0xBA
        },
    };

    int nbJoueur = 2;
    int res;

    system("cls");
    positionnerCurseur(55, 13);
    Color(15, 0);
    printf("Combien de joueur ?");
    Color(7, 0);
    positionnerCurseur(55, 14);
    printf("%c Augmenter avec les fl%cches", 0x1E, 0x8A);
    positionnerCurseur(55, 15);
    printf("%c Valider avec entr%ce", 0x1F, 0x82);
    positionnerCurseur(60, 0);

    do {
        if (res == 80 && nbJoueur > 2)
            nbJoueur--;
        if (res == 72 && nbJoueur < 4)
            nbJoueur++;

        int index = 0;
        Color(11, 0);
        for (int i = 0; i < 5; i++)
            for (int j = 0; j < 8; j++) {
                positionnerCurseur(44+j, 12+i);
                printf("%c", nombres[nbJoueur-2][index]);
                index++;
            }

        while(!kbhit());
        res = getch();
    } while(res != 13);
    return nbJoueur;
}

void demanderPseudos(t_joueur joueurs[4], int joueurHumain) {
    system("cls");

    Color(7, 0);
    positionnerCurseur(70, 12);
    printf("%c Veuillez saisir les pseudos de chaque joueur", 0xFE);
    positionnerCurseur(72, 13);
    printf("(20 caract%cres maximum)", 0x8A);

    positionnerCurseur(70, 15);
    printf("%c Pour valider utiliser la touche entr%ce", 0xFE, 0x82);

    //On demande les pseudos des joueurs
    for (int i = 0; i < joueurHumain; i++) {
        positionnerCurseur(50, 14 - (joueurHumain*2 /3) + (i-1)*3);
        Color(11, 0);
        printf("%c%c ", 0xCD, 0xCD);
        Color(15, 0);
        printf("Joueur %d", i+1);
        Color(11, 0);
        printf(" %c%c", 0xCD, 0xCD);
        positionnerCurseur(50, 14 - (joueurHumain*2 /3) + (i-1)*3 + 1);
        Color(7, 0);
        int res;
        int nbChar = 0;
        char pseudo[20] = {'\0'};

        do {
            //Système de blindage et d'écriture de pseudo
            if((res >= 'a' && res <= 'z') || (res >= 'A' && res <= 'Z') || res == ' ') {
                if (nbChar < 19) {
                    positionnerCurseur(50 + nbChar, 14 - (joueurHumain*2 /3) + (i-1)*3 + 1);
                    printf("%c", res);
                    pseudo[nbChar] = res;
                    nbChar++;
                }
            }

            if (res == 8 && nbChar >= 0) {
                positionnerCurseur(50 + nbChar-1, 14 - (joueurHumain*2 /3) + (i-1)*3 + 1);
                printf(" ");
                pseudo[nbChar] = ' ';
                if (nbChar > 0)
                    nbChar--;
            }
            while (!kbhit());
            res = getch();
        } while(!(res == 13 && strlen(pseudo) >= 2));
        strcpy(joueurs[i].pseudo, pseudo);
        joueurs[i].humain = true;
    }
}

void afficherPoints(t_joueur joueurs[4], int nbJoueur) {
    //On efface la zone de scores
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 40; j++) {
            positionnerCurseur(10+j, 20+i);
            printf(" ");
        }

    positionnerCurseur(10, 20);
    Color(11, 0);
    printf("%c%c%c ", 0xCD, 0xCD, 0xCD);
    Color(15, 0);
    printf("Scores");
    Color(11, 0);
    printf(" %c%c%c", 0xCD, 0xCD, 0xCD);

    for (int i = 0; i < nbJoueur; i++) {
        positionnerCurseur(10, 21+i);
        Color(15, 0);
        printf("- %s ", joueurs[i].pseudo);
        Color(7, 0);
        printf("%d", joueurs[i].score);
    }
}

void afficherPseudos(int nbJoueurs, char pseudos[4][20]) {
    system("cls");
    for (int i = 0; i < nbJoueurs; i++)
        printf("- %s\n", &pseudos[i][0]);
}

void afficherErreur(char* erreur) {
    //On efface l'ancienne erreur
    positionnerCurseur(10, 19);
    for (int i = 0; i < 52; i++)
        printf(" ");

    positionnerCurseur(10, 19);
    Color(12, 0);
    printf("%s", erreur);
    Color(15, 0);
}
