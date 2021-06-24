#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#include "sauvegarde.h"
#include "plateau.h"
#include "tuiles.h"

void menuSauvegardes() {
    system("cls");
    positionnerCurseur(46, 4);
    Color(11, 0);
    printf("%c%c%c", 0xCD, 0xCD, 0xCD);

    Color(15, 0);
    printf(" Parties sauvegard%ces ", 0x82);

    Color(11, 0);
    printf("%c%c%c", 0xCD, 0xCD, 0xCD);

    t_partie parties[20];
    chargerSauvegardes(parties);

    for (int i = 0; i < 20; i++) {
        if (parties[i].nbJoueur >= 2 && parties[i].nbJoueur <= 4) {
            positionnerCurseur(35, 6+(i*2));
            printf("- Partie %d : %d", i+1, parties[i].nbJoueur);
        }
        i++;

    }

    int saisie = 0;

    do {

        while (!kbhit());
        saisie = getch();
    } while (!(saisie >= 49 && saisie <= 54));

    if (saisie != 27) {
        lancerPartie(parties[saisie-49]);
    }



}


void sauvegardeParties(t_partie partie) {
    t_partie parties[20];
    chargerSauvegardes(parties);

    FILE* fp;

    fp = fopen("sauvegarde.dat", "w");
    if (fp != NULL) {
        for (int i = 0; i < 20; i++) {
            if (!(parties[i].nbJoueur >= 2 && parties[i].nbJoueur <= 4)) {
                parties[i] = partie;
                fwrite(&parties[i], sizeof(t_partie), 1, fp);
                break;
            }
        }
    } else {
        printf("\nProblème d'ouverture du fichier :/");
    }
}


void chargerSauvegardes(t_partie* parties) {
    FILE* fp;

    fp = fopen("sauvegarde.dat", "r");

    if (fp == NULL)
        exit(-1);

    fread(parties , sizeof(t_partie), 20, fp);
    fclose(fp);
}

void lancerPartie(t_partie partie) {

    afficherPlateau(partie.plateau);

    bool finJeu = 0;
    int tour = partie.nbTour;

    while (finJeu == 0) {
        afficherMain(partie.mains, partie.pseudos, (partie.nbTour % partie.nbJoueur));

        int tuile = 0;
        int coordsX = 0;
        int coordsY = 0;

        char erreur[30] = {0};

        afficherPoints(partie.scores, partie.pseudos, partie.nbJoueur);

        do {
            afficherErreur(erreur);
            recupererPlacement(partie.mains[(partie.nbTour % partie.nbJoueur)],&tuile, &coordsX, &coordsY);
        } while(!placementValide(partie.plateau, erreur, partie.mains[(partie.nbTour % partie.nbJoueur)], tuile, coordsX-97, coordsY-65, tour));

        jouerPlacement(partie.plateau, partie.mains[(partie.nbTour % partie.nbJoueur)], tuile, coordsX-97, coordsY-65);
        remplacerTuile(&partie.mains[partie.nbTour % partie.nbJoueur][tuile], partie.pioche, &partie.index);
        partie.scores[partie.nbTour % partie.nbJoueur] += calculPoints(partie.plateau, coordsX-97, coordsY-65);

        if ((partie.nbTour+1) % partie.nbJoueur == 0 && partie.nbTour != 0) {
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

                finJeu == 1;
                if (saisie2 == 49)
                    sauvegardeParties(partie);
            }
        }

        partie.nbTour++;
    }
}


