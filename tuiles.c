#include "tuiles.h"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/*
    - Demander au joueur les tuile qui veut échanger
    - Les échanger si il en reste dans la pioche
*/

/*void echangerTuile(t_tuile main[6]) //
{
    positionnerCurseur(60,60);
    Color(11,0);
    printf("Echanger des tuiles? Combien?");

    do{
        while(!kbhit());
        touche = getch();
    }while(!(touche>=49 && touche<=54));

    for (int i=0; i<touche; i++){
        remplacerTuile(tuile, pioche, index);
    }
}*/

void Color(int couleurDuTexte,int couleurDeFond) // fonction d'affichage de couleurs
{
    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,couleurDeFond*16+couleurDuTexte);
}

void genererPioche(t_tuile tuiles[108], int modeDeJeu)
{
    //On crée toutes les tuiles dans l'ordre
    int lim = (modeDeJeu == 1) ? 3 : 1;
    int index = 0;
    int couleurs[] = {14, 15, 4, 3, 2, 5};
    char formes[] = {0x03, 0x04, 0x05, 0x0F, 0x06, 0xFE};
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 6; j++)
            for (int k = 0; k < lim; k++) {
                tuiles[index].couleur = couleurs[i];
                tuiles[index].forme = formes[j];
                index++;
            }
    //On mélange la pioche
    srand(time(NULL));
    char formeTemp;
    int tuileAlea1, tuileAlea2, couleurTemp;

    for (int i = 0; i < 100; i++) {
        tuileAlea1 = rand() % index;
        tuileAlea2 = rand() % index;

        couleurTemp = tuiles[tuileAlea1].couleur;
        formeTemp = tuiles[tuileAlea1].forme;

        tuiles[tuileAlea1].couleur = tuiles[tuileAlea2].couleur;
        tuiles[tuileAlea1].forme = tuiles[tuileAlea2].forme;

        tuiles[tuileAlea2].couleur = couleurTemp;
        tuiles[tuileAlea2].forme = formeTemp;
    }
}

void distribuerTuiles(t_tuile main[6], t_tuile pioche[108], int* index) {
    for (int i = 0; i < 6; i++) {
        main[i] = pioche[*index];
        *index += 1;
    }
}

void afficherMainsJoueurs(t_tuile mains[4][6], char pseudos[4][20], int nbJoueurs) {
    system("cls");
    printf("Mains des joueurs :\n\n");
    for (int i = 0; i < nbJoueurs; i++) {
        printf("- Main de %s\n", pseudos[i]);
        for (int j = 0; j < 6; j++) {
            Color(mains[i][j].couleur, 0);
            printf("%c", mains[i][j].forme);
            Color(15, 0);
        }
        printf("\n");
    }
}

void afficherDeck(t_tuile* tuiles)
{
    for (int i = 0; i < 36; i++) {
        Color(tuiles[i].couleur, 0);
        printf("%c", tuiles[i].forme);
        Color(15, 0);
    }
}

void remplacerTuile(t_tuile* tuile, t_tuile pioche[108], int* index) {
    tuile->couleur = pioche[*index].couleur;
    tuile->forme = pioche[*index].forme;
    *index += 1;
}

void prgmTuiles() {
    system("cls");
    t_tuile* tuiles = (t_tuile*) malloc(36*sizeof(t_tuile));
    genererPioche(tuiles, 2);
    afficherDeck(tuiles);
}

void retournerNomTuile(t_tuile tuile, char* nomTuile)
{
    char chaine1[20];
    char chaine2[20];
    switch(tuile.couleur)
    {
        case 2 :
            strcpy(chaine2, "vert");
            break;
        case 3 :
            strcpy(chaine2, "bleu");
            break;
        case 4 :
            strcpy(chaine2, "rouge");
            break;
        case 5 :
            strcpy(chaine2, "violet");
            break;
        case 14 :
            strcpy(chaine2, "jaune");
            break;
        case 15 :
            strcpy(chaine2, "blanc");
            break;
    }

     switch((unsigned char)tuile.forme)
    {
        case 0x03 :
            strcpy(chaine1, "Coeur ");
            break;
        case 0x04 :
            strcpy(chaine1, "Losange ");
            break;
        case 0x05 :
            strcpy(chaine1, "Trefle ");
            break;
        case 0x0F :
              strcpy(chaine1, "Soleil ");
            break;
        case 0x06 :
            strcpy(chaine1, "Pique ");
            break;
        case 0xFE :
            strcpy(chaine1, "Carreaux ");
            break;
    }
    strcat(chaine1,chaine2);
    strcpy(nomTuile, chaine1);
}
