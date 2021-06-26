#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#include "sauvegarde.h"
#include "plateau.h"
#include "tuiles.h"
#include "etatJeu.h"

void menuSauvegardes() {
    system("cls");
    positionnerCurseur(46, 4);
    Color(11, 0);
    printf("%c%c%c", 0xCD, 0xCD, 0xCD);

    Color(15, 0);
    printf(" Parties sauvegard%ces ", 0x82);

    Color(11, 0);
    printf("%c%c%c", 0xCD, 0xCD, 0xCD);

    t_partie* parties = (t_partie*) malloc(20*sizeof(t_partie));

    chargerParties(parties);

    for (int i = 0; i < 20; i++) {
        if (parties[i].nbJoueur != 0) {
            positionnerCurseur(35, 6+(i*2));
            Color(11, 0);
            printf("%c%c%c ", 0xCD, 0xCD, 0xCD);
            Color(15, 0);
            printf("Partie ");
            printf("#%d", i+1);
            Color(11, 0);
            printf(" %c%c%c", 0xCD, 0xCD, 0xCD);
            positionnerCurseur(35, 7+(i*2));
            Color(15, 0);
            printf("Joueurs : %s", parties[i].modeDeJeu);
            Color(7, 0);
            for (int j = 0; j < parties[i].nbJoueur; j++) {
                printf("%s ", parties[i].joueurs[j].pseudo);
            }
            positionnerCurseur(35, 8+(i*2));
            Color(15, 0);
            printf("Tour : ");
            Color(7, 0);
            printf("%d", parties[i].nbTour + 1);
        }
    }

    int saisie = 0;

    do {

        while (!kbhit());
        saisie = getch();
    } while (!((saisie >= 49 && saisie <= 54) || saisie == 27) );

    if (saisie != 27) {
        lancerPartie(parties[saisie-49]);
    }

}

void sauvegarderPartie(t_partie partie) {
    FILE *fp;

    fp = fopen ("parties.dat", "wb");

    if (fp == NULL) {
        fprintf(stderr, "\nErreur d'ouverture de fichier\n");
        exit(1);
    }

    fwrite(&partie, sizeof(t_partie), 1, fp);

    fclose(fp);
}

void chargerParties(t_partie* parties) {

    FILE *fp;

    fp = fopen ("parties.dat", "rb");

    if (fp == NULL) {
        fprintf(stderr, "\nErreur d'ouverture de fichier\n");
        exit(1);
    }

    while (fread(parties, sizeof(t_partie), 1, fp) != NULL);

    fclose(fp);
}

void lancerPartie(t_partie partie) {

    afficherPlateau(partie.plateau);

    bool finJeu = false;

    while (!finJeu) {
        afficherMain(partie.joueurs[partie.nbTour % partie.nbJoueur]);

        int tuile = 0;
        int coordsX = 0;
        int coordsY = 0;

        char erreur[30] = {0};

        afficherPoints(partie.joueurs, partie.nbJoueur);
        int tourJoueur = partie.nbTour % partie.nbJoueur;
        do {
            //afficherErreur(erreur);
            recupererPlacement(partie.joueurs[tourJoueur].main, &tuile, &coordsX, &coordsY);
        } while(!placementValide(partie.plateau, erreur, partie.joueurs[tourJoueur].main, tuile, coordsX-97, coordsY-65, partie.nbTour));

        jouerPlacement(partie.plateau, partie.joueurs[tourJoueur].main[tuile], coordsX-97, coordsY-65);
        remplacerTuile(&partie.joueurs[tourJoueur].main[tuile], partie.pioche, &partie.index);
        partie.joueurs[tourJoueur].score += calculPoints(partie.plateau, coordsX-97, coordsY-65);

        if (((partie.nbTour+1) % partie.nbJoueur == 0) && partie.nbTour != 0) {
            positionnerCurseur(60, 20);
            Color(11, 0);
            printf("1. Continuer");
            positionnerCurseur(60, 21);
            printf("2. Quitter");
            int saisie;
            do {
                while (!kbhit());
                saisie = getch();
            } while (!(saisie == 49 || saisie == 50));

            if (saisie == 50) {

                positionnerCurseur(60, 20);
                Color(11, 0);
                printf("1. Sauvegarder");
                positionnerCurseur(60, 21);
                printf("2. Quitter");
                int saisie2;
                do {
                    while (!kbhit());
                    saisie2 = getch();
                } while (!(saisie2 == 49 || saisie2 == 50));

                finJeu = true;
                if (saisie2 == 49) {
                    sauvegarderPartie(partie);
                }

                /*free(partie.mains);
                free(partie.pioche);
                free(partie.plateau);
                free(partie.pseudos);
                free(partie.scores);*/
            }
        }

        partie.nbTour += 1;
    }
}


