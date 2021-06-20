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
    int modeDeJeu = -1;
    do {
        system("cls");
        printf("Mode de jeu :\n");
        printf("- Mode normal\n");
        printf("- Mode degrade\n\n");
        fflush(stdin);
        scanf("%d", &modeDeJeu);
    } while (!(modeDeJeu == 1 || modeDeJeu == 2));
    return modeDeJeu;
}

int demanderNombreJoueur() {
    int nbJoueur = 0;
    do {
        system("cls");
        printf("Combien de joueur ? (2 a 4)\n");
        fflush(stdin);
        scanf("%d", &nbJoueur);
    } while(!(nbJoueur >= 2 && nbJoueur <= 4));
    return nbJoueur;
}

void demanderPseudos(int nbJoueurs, char** pseudos) {
    for (int i = 0; i < nbJoueurs; i++) {
        char pseudoTemp[20];
        do {
            system("cls");
            printf("Pseudo joueur %d : (Minimum 3 caracteres)\n\n", i+1);
            fflush(stdin);
            scanf("%[^\n]s", pseudoTemp);
        } while(sizeof(pseudoTemp) < 3);
        pseudos[i] = (char*) malloc((strlen(pseudoTemp)+1)*sizeof(char*));
        strcpy(&pseudos[i][0], pseudoTemp);
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
