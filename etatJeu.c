#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>

#include "etatJeu.h"
#include "tuiles.h"
#include "plateau.h"

int demanderModeDeJeu();
int demanderNombreJoueur();
void demanderPseudos(int nbJoueurs, char** pseudos);
void afficherPseudos(int nbJoueurs, char** pseudos);
void lancementJeu(int nbJoueurs, char** pseudos, int modeDeJeu);
void afficherErreur(char* erreur);

void preparationJeu() {
    int modeDeJeu = demanderModeDeJeu();
    int nbJoueurs = demanderNombreJoueur();

    char** pseudos = (char**) malloc(nbJoueurs*sizeof(char*));

    demanderPseudos(nbJoueurs, pseudos);
    lancementJeu(nbJoueurs, pseudos, modeDeJeu);
}

void lancementJeu(int nbJoueurs, char** pseudos, int modeDeJeu) {

    //On génère la pioche en fonction du mode de jeu, puis on mélange les tuiles
    t_tuile* pioche = (t_tuile*) malloc((modeDeJeu == 1 ? 108 : 36)*sizeof(t_tuile));
    genererPioche(pioche, modeDeJeu);

    //Distribution des cartes
    t_tuile** mains = (t_tuile**) malloc(nbJoueurs*sizeof(t_tuile*));
    for (int i = 0; i < nbJoueurs; i++)
        mains[i] = (t_tuile*) malloc(6*sizeof(t_tuile));

    int index = 0;
    distribuerTuiles(mains, pioche, nbJoueurs, modeDeJeu, &index);


    //afficherMainsJoueurs(mains, pseudos, nbJoueurs);
    t_tuile** plateau = (t_tuile**) malloc(COLONNES*sizeof(t_tuile*));
    for (int i = 0; i < COLONNES; i++)
        plateau[i] = (t_tuile*) malloc(LIGNES*sizeof(t_tuile));

    afficherPlateau(plateau);

    bool finJeu = false;
    int tour = 0;

    while (!finJeu) {
        /**
        Afficher main joueur et pseudo,
        Demander tuile et placement
        Vérification placement tuile
        Calcul des points,
        Nouvelle pioche d'une tuile,
        Détection fin jeu (Plus du tuile, coup impossible)
        Joueur suivant
        **/
        afficherMain(mains, pseudos, (tour % nbJoueurs));

        int tuile = 0;
        int coordsX = 0;
        int coordsY = 0;

        char erreur[30] = {0};
        do {
            afficherErreur(erreur);
            recupererPlacement(mains[(tour % nbJoueurs)],&tuile, &coordsX, &coordsY);
        } while(!placementValide(plateau, erreur, mains[(tour % nbJoueurs)], tuile, coordsX-97, coordsY-65, tour));

        jouerPlacement(plateau, mains[(tour % nbJoueurs)], tuile, coordsX-97, coordsY-65);
        remplacerTuile(&mains[tour % nbJoueurs][tuile], pioche, &index);

        tour++;
    }
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
        } while(res != 13);
        pseudos[i] = (char*) malloc((strlen(pseudo)+1)*sizeof(char));
        strcpy(pseudos[i], pseudo);
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
