#include <stdio.h>
#include <stdlib.h>

#include "etatJeu.h"

int demanderModeDeJeu();
int demanderNombreJoueur();
void demanderPseudos(int nbJoueurs, char** pseudos);
void afficherPseudos(int nbJoueurs, char** pseudos);

void preparationJeu() {
    int modeDeJeu = demanderModeDeJeu();
    int nbJoueurs = demanderNombreJoueur();
    printf("Mode de jeu : %d\nNombre de joueurs : %d", modeDeJeu, nbJoueurs);
    char** pseudos = (char**) malloc(nbJoueurs*sizeof(char*));
    demanderPseudos(nbJoueurs, pseudos);
    afficherPseudos(nbJoueurs, pseudos);
}


int demanderModeDeJeu() {
    int modeDeJeu = -1;
    do {
        system("cls");
        printf("Mode de jeu :\n");
        printf("- Mode degrade\n");
        printf("- Mode normal\n\n");
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
        strcpy(pseudos+i, pseudoTemp);
    }
}


void afficherPseudos(int nbJoueurs, char** pseudos) {
    system("cls");
    for (int i = 0; i < nbJoueurs; i++)
        printf("- %s\n", pseudos+i);
}
