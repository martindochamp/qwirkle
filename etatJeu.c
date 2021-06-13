#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "etatJeu.h"
#include "tuiles.h"
#include "plateau.h"

int demanderModeDeJeu();
int demanderNombreJoueur();
void demanderPseudos(int nbJoueurs, char** pseudos);
void afficherPseudos(int nbJoueurs, char** pseudos);
void lancementJeu(int nbJoueurs, char** pseudos, int modeDeJeu);

void preparationJeu() {
    int modeDeJeu = demanderModeDeJeu();
    int nbJoueurs = demanderNombreJoueur();

    char** pseudos = (char**) malloc(nbJoueurs*sizeof(char*));

    demanderPseudos(nbJoueurs, pseudos);
    lancementJeu(nbJoueurs, pseudos, modeDeJeu);
}


void lancementJeu(int nbJoueurs, char** pseudos, int modeDeJeu) {

    //On génére le deck en fonction du mode de jeu
    t_tuile* pioche = (t_tuile*) malloc((modeDeJeu == 1 ? 108 : 36)*sizeof(t_tuile));
    genererPioche(pioche, modeDeJeu);
    t_tuile** mains = (t_tuile**) malloc(nbJoueurs*sizeof(t_tuile*));

    //Distribution des cartes
    for (int i = 0; i < nbJoueurs; i++)
        *(mains+i) = (t_tuile*) malloc(6*sizeof(t_tuile));


    distribuerTuiles(mains, pioche, nbJoueurs, modeDeJeu);
    //afficherMainsJoueurs(mains, pseudos, nbJoueurs);
    t_tuile** plateau = (t_tuile**) malloc(LIGNES*sizeof(t_tuile*));
    for (int i = 0; i < LIGNES; i++)
        *(plateau+i) = (t_tuile*) malloc(COLONNES*sizeof(t_tuile));


    afficherPlateau(plateau);
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
        *(pseudos+i) = (char*) malloc((strlen(pseudoTemp)+1)*sizeof(char*));
        strcpy(&pseudos[i][0], pseudoTemp);
    }
}


void afficherPseudos(int nbJoueurs, char** pseudos) {
    system("cls");
    for (int i = 0; i < nbJoueurs; i++)
        printf("- %s\n", &pseudos[i][0]);
}
