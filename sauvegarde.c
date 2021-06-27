#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "sauvegarde.h"
#include "plateau.h"
#include "tuiles.h"
#include "etatJeu.h"
#include "ia.h"
#include "interfaces.h"

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
            printf("Joueurs : ");
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

    if (fp == NULL)
        exit(1);

    fwrite(&partie, sizeof(t_partie), 1, fp);

    fclose(fp);
}

void chargerParties(t_partie* parties) {

    FILE *fp;

    fp = fopen ("parties.dat", "rb");

    if (fp == NULL)
        exit(1);

    while (fread(parties, sizeof(t_partie), 1, fp) != NULL);

    fclose(fp);
}

void lancerPartie(t_partie partie) {

    afficherPlateau(partie.plateau);

    bool finJeu = false;
    bool victoire = false;

    while (!finJeu) {
        int tourJoueur = partie.nbTour % partie.nbJoueur;
        if (partie.joueurs[tourJoueur].humain) {

            //On réorganise la main si des tuiles sont manquantes
            for (int i = 0; i < 5; i++) {
                if (partie.joueurs[tourJoueur].main[i].forme == ' ') {
                    for (int j = i+1; j < 6; j++) {
                        if (partie.joueurs[tourJoueur].main[j].forme != ' ') {
                            partie.joueurs[tourJoueur].main[i].forme = partie.joueurs[tourJoueur].main[j].forme;
                            partie.joueurs[tourJoueur].main[i].couleur = partie.joueurs[tourJoueur].main[j].couleur;
                            partie.joueurs[tourJoueur].main[j].forme = ' ';
                            partie.joueurs[tourJoueur].main[j].couleur = 0;
                            break;
                        }
                    }
                }
            }
            afficherMain(partie.joueurs[tourJoueur]);

            int tuile = 0;
            int coordsX = 0;
            int coordsY = 0;

            afficherPoints(partie.joueurs, partie.nbJoueur);

            int res;
            int selection = 1;
            do {
                if (res == 72 && selection > 1)
                    selection--;
                if (res == 80 && selection < 2)
                    selection++;

                positionnerCurseur(70, 8);
                Color(15, 0);
                printf("Que voulez-vous faire ?");

                for (int i = 0; i < 2; i++)
                    for (int j = 0; j < 20; j++) {
                        positionnerCurseur(70+j, 10+i);
                        printf(" ");
                    }

                if (selection == 1) {
                    positionnerCurseur(70, 10);
                    Color(11, 0);
                    printf("%c %c ", 0x03, 0x04);
                    Color(15, 0);
                    printf("Poser tuiles");
                    positionnerCurseur(74, 11);
                    Color(7, 0);
                    printf("Echanger tuiles");
                } else {
                    positionnerCurseur(74, 10);
                    Color(7, 0);
                    printf("Poser tuiles");
                    positionnerCurseur(70, 11);
                    Color(11, 0);
                    printf("%c %c ", 0x03, 0x04);
                    Color(15, 0);
                    printf("Echanger tuiles");
                }
                while(!kbhit());
                res = getch();
            } while (res != 13);

            if (selection == 1) {
                //Placement tuile
                do {
                    recupererPlacement(partie.joueurs[tourJoueur].main, &tuile, &coordsX, &coordsY);
                } while(!placementValide(partie.plateau, partie.joueurs[tourJoueur].main[tuile], coordsX, coordsY));

                jouerPlacement(partie.plateau, partie.joueurs[tourJoueur].main[tuile], coordsX, coordsY);
                remplacerTuile(&partie.joueurs[tourJoueur].main[tuile], partie.pioche, &partie.index, partie.nbJoueur);
                partie.joueurs[tourJoueur].score += calculPoints(partie.plateau, coordsX, coordsY);
            } else {
                //Echange de tuile
                for (int i = 0; i < 5; i++)
                    for (int j = 0; j < 30; j++) {
                        positionnerCurseur(70+j, 8+i);
                        printf(" ");
                    }

                positionnerCurseur(70, 8);
                Color(15, 0);
                printf("Quelles tuiles ?");

                int tuilesSelectionnees[6] = {0};
                //Récupération tuile d'échange
                do {
                    int saisie;

                    int tuileSelectionne = 1;
                    do {
                        if (saisie == 75 && tuileSelectionne > 1)
                            tuileSelectionne--;
                        if (saisie  ==  77 && tuileSelectionne < 6)
                            tuileSelectionne++;
                        positionnerCurseur(70 + (tuileSelectionne-1)*2, 6);
                        HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
                        CONSOLE_CURSOR_INFO info;
                        info.dwSize = 10;
                        info.bVisible = TRUE;
                        SetConsoleCursorInfo(consoleHandle, &info);
                        while (!kbhit());
                        saisie = getch();
                    } while (saisie != 13);


                    for (int i = 0; i < 6; i++) {
                        if (tuilesSelectionnees[i] == tuileSelectionne) {
                            tuilesSelectionnees[i] = 0;
                        } else if (tuilesSelectionnees[i] == 0) {
                            tuilesSelectionnees[i] = tuileSelectionne;
                            break;
                        }
                    }

                    while (!kbhit());
                    res = getch();
                } while (res != 13);

                //On échange les tuiles demandées
                for (int i = 0; i < 6; i++)
                    if (tuilesSelectionnees[i] != 0)
                        echangerTuile(&partie.joueurs[tourJoueur].main[tuilesSelectionnees[i]-1], partie.pioche, partie.index, partie.modeDeJeu);
            }
        } else {
            //Le joueur n'est pas humain
            int x, y, numeroTuile;
            testerCoups(partie.plateau, partie.joueurs[tourJoueur].main, &x, &y, &numeroTuile, partie.nbTour);
            jouerPlacement(partie.plateau, partie.joueurs[tourJoueur].main[numeroTuile], x, y);
            remplacerTuile(&partie.joueurs[tourJoueur].main[numeroTuile], partie.pioche, &partie.index, partie.modeDeJeu);
            partie.joueurs[tourJoueur].score += calculPoints(partie.plateau, x, y);
        }

        //Vérification victoire/fin de jeu
        int lim = partie.modeDeJeu == 1 ? 108 : 36;

        int tuilesMainsRestantes = 0;
        for (int i = 0; i < partie.nbJoueur; i ++)
            for (int j = 0; j < 6; j++)
                if (partie.joueurs[i].main[j].forme != ' ')
                    tuilesMainsRestantes++;

        if (partie.index >= lim && tuilesMainsRestantes == 0) {
            //Fin de jeu
            menuFinDeJeu(partie);
            victoire = true;
            break;
        }

        if (((partie.nbTour+1) % partie.nbJoueur == 0) && partie.nbTour != 0 && victoire == false) {
            int selection = 1;
            int saisie;

            do {
                if (saisie == 72 && selection > 1)
                    selection--;
                if (saisie == 80 && selection < 2)
                    selection++;

                for (int i = 0; i < 2; i++)
                    for (int j = 0; j < 20; j++) {
                        positionnerCurseur(70+j, 14+i);
                        printf(" ");
                    }

                if (selection == 1) {
                    positionnerCurseur(70, 14);
                    Color(6, 0);
                    printf("%c %c ", 0x03, 0x04);
                    Color(15, 0);
                    printf("Continuer");
                    positionnerCurseur(74, 15);
                    Color(7, 0);
                    printf("Quitter");
                } else {
                    positionnerCurseur(74, 14);
                    Color(7, 0);
                    printf("Continuer");
                    positionnerCurseur(70, 15);
                    Color(6, 0);
                    printf("%c %c ", 0x03, 0x04);
                    Color(15, 0);
                    printf("Quitter");
                }

                while (!kbhit());
                saisie = getch();
            } while (saisie != 13);

            //On supprime la zone
            for (int i = 0; i < 2; i++)
                for (int j = 0; j < 20; j++) {
                    positionnerCurseur(70+j, 14+i);
                    printf(" ");
                }

            if (selection == 2) {
                selection = 1;
                do {
                    if (saisie == 72 && selection > 1)
                        selection--;
                    if (saisie == 80 && selection < 2)
                        selection++;

                    for (int i = 0; i < 2; i++)
                        for (int j = 0; j < 20; j++) {
                            positionnerCurseur(70+j, 14+i);
                            printf(" ");
                        }

                    if (selection == 1) {
                        positionnerCurseur(70, 14);
                        Color(6, 0);
                        printf("%c %c ", 0x03, 0x04);
                        Color(15, 0);
                        printf("Sauvegarder");
                        positionnerCurseur(74, 15);
                        Color(7, 0);
                        printf("Quitter");
                    } else {
                        positionnerCurseur(74, 14);
                        Color(7, 0);
                        printf("Sauvegarder");
                        positionnerCurseur(70, 15);
                        Color(6, 0);
                        printf("%c %c ", 0x03, 0x04);
                        Color(15, 0);
                        printf("Quitter");
                    }

                    while (!kbhit());
                    saisie = getch();
                } while (saisie != 13);

                finJeu = true;
                if (selection == 1) {
                    sauvegarderPartie(partie);
                }
            }
        }
        partie.nbTour += 1;
    }
}
