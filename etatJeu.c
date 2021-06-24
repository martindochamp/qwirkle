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
void demanderPseudos(int nbJoueurs, char** pseudos);
void afficherPseudos(int nbJoueurs, char** pseudos);
void lancementJeu(int nbJoueurs, char** pseudos, int modeDeJeu);
void afficherErreur(char* erreur);
void afficherPoints();

void preparationJeu() {
    int modeDeJeu = demanderModeDeJeu();
    int nbJoueurs = demanderNombreJoueur();

    char** pseudos = (char**) malloc(nbJoueurs*sizeof(char*));
    demanderPseudos(nbJoueurs, pseudos);

    //Récupération de toutes les données pour créer la partie

    //On génère la pioche en fonction du mode de jeu, puis on mélange les tuiles
    t_tuile* pioche = (t_tuile*) malloc((modeDeJeu == 1 ? 108 : 36)*sizeof(t_tuile));
    genererPioche(pioche, modeDeJeu);

    //Distribution des tuiles dans la main
    t_tuile** mains = (t_tuile**) malloc(nbJoueurs*sizeof(t_tuile*));
    for (int i = 0; i < nbJoueurs; i++)
        mains[i] = (t_tuile*) malloc(6*sizeof(t_tuile));

    int index = 0;
    distribuerTuiles(mains, pioche, nbJoueurs, modeDeJeu, &index);

    t_tuile** plateau = (t_tuile**) malloc(COLONNES*sizeof(t_tuile*));
    for (int i = 0; i < COLONNES; i++)
        plateau[i] = (t_tuile*) malloc(LIGNES*sizeof(t_tuile));

    int* scores = (int*) malloc(nbJoueurs*sizeof(int));
    for (int i = 0; i < nbJoueurs; i++)
        scores[i] = 0;

    t_partie nouvellePartie;
    nouvellePartie.pioche = pioche;
    nouvellePartie.mains = mains;
    nouvellePartie.index = index;
    nouvellePartie.plateau = plateau;
    nouvellePartie.scores = scores;
    nouvellePartie.nbTour = 0;
    nouvellePartie.pseudos = pseudos;
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

void demanderPseudos(int nbJoueurs, char** pseudos) {
    system("cls");

    Color(7, 0);
    positionnerCurseur(70, 12);
    printf("%c Veuillez saisir les pseudos de chaque joueur", 0xFE);
    positionnerCurseur(72, 13);
    printf("(20 caract%cres maximum)", 0x8A);

    positionnerCurseur(70, 15);
    printf("%c Pour valider utiliser la touche entr%ce", 0xFE, 0x82);

    //On demande les pseudos des joueurs
    for (int i = 0; i < nbJoueurs; i++) {
        positionnerCurseur(50, 14 - (nbJoueurs*2 /3) + (i-1)*3);
        Color(11, 0);
        printf("%c%c ", 0xCD, 0xCD);
        Color(15, 0);
        printf("Joueur %d", i+1);
        Color(11, 0);
        printf(" %c%c", 0xCD, 0xCD);
        positionnerCurseur(50, 14 - (nbJoueurs*2 /3) + (i-1)*3 + 1);
        Color(7, 0);
        int res;
        int nbChar = 0;
        char pseudo[20] = {'\0'};

        do {
            //Système de blindage et d'écriture de pseudo
            if((res >= 'a' && res <= 'z') || (res >= 'A' && res <= 'Z') || res == ' ') {
                if (nbChar < 19) {
                    positionnerCurseur(50 + nbChar, 14 - (nbJoueurs*2 /3) + (i-1)*3 + 1);
                    printf("%c", res);
                    pseudo[nbChar] = res;
                    nbChar++;
                }
            }

            if (res == 8 && nbChar >= 0) {
                positionnerCurseur(50 + nbChar-1, 14 - (nbJoueurs*2 /3) + (i-1)*3 + 1);
                printf(" ");
                pseudo[nbChar] = ' ';
                if (nbChar > 0)
                    nbChar--;
            }
            while (!kbhit());
            res = getch();
        } while(!(res == 13 && strlen(pseudo) >= 2));
        pseudos[i] = (char*) malloc((strlen(pseudo)+1)*sizeof(char));
        strcpy(pseudos[i], pseudo);
    }
}

void afficherPoints(int* scores, char** pseudos, int nbJoueur){
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
        printf("- %s ", pseudos[i]);
        Color(7, 0);
        printf("%d", scores[i]);
    }
}

void afficherPseudos(int nbJoueurs, char** pseudos) {
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


void partiesSauvegardes() {

}
