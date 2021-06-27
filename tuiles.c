#include "tuiles.h"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//Affichage couleur, source : Campus
void Color(int couleurDuTexte,int couleurDeFond)
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
    srand(time(NULL));
    char formeTemp;
    int tuileAlea1, tuileAlea2, couleurTemp;

    //On mélange la pioche 100 fois
    for (int i = 0; i < 100; i++) {
        tuileAlea1 = rand() % (lim*36);
        tuileAlea2 = rand() % (lim*36);

        couleurTemp = tuiles[tuileAlea1].couleur;
        formeTemp = tuiles[tuileAlea1].forme;

        tuiles[tuileAlea1].couleur = tuiles[tuileAlea2].couleur;
        tuiles[tuileAlea1].forme = tuiles[tuileAlea2].forme;

        tuiles[tuileAlea2].couleur = couleurTemp;
        tuiles[tuileAlea2].forme = formeTemp;
    }
}

//Distribution de 6 tuiles pour le joueur
void distribuerTuiles(t_tuile main[6], t_tuile pioche[108], int* index) {
    for (int i = 0; i < 6; i++) {
        main[i] = pioche[*index];
        *index += 1;
    }
}

//Pioche une nouvelle tuile
void remplacerTuile(t_tuile* tuile, t_tuile pioche[108], int* index, int modeDeJeu) {
    int lim = (modeDeJeu == 1) ? 108 : 36;
    if (*index < lim) {
        tuile->couleur = pioche[*index].couleur;
        tuile->forme = pioche[*index].forme;
        *index += 1;
    } else {
        tuile->couleur = 0;
        tuile->forme = ' ';
    }
}

//Echange de tuile avec une aléatoire dans la pioche
void echangerTuile(t_tuile* tuile, t_tuile pioche[108], int index, int modeDeJeu) {
    int lim = modeDeJeu == 1 ? 108 : 36;

    if (index < lim) {
        t_tuile tuileAEchanger;
        tuileAEchanger.couleur = tuile->couleur;
        tuileAEchanger.forme = tuile->forme;

        //Mélange pioche avant d'échanger
        int alea = rand() % (modeDeJeu == 1 ? 108 : 36) + index;
        tuile->couleur = pioche[alea].couleur;
        tuile->forme = pioche[alea].forme;
        pioche[alea].couleur = tuileAEchanger.couleur;
        pioche[alea].forme = tuileAEchanger.forme;
    }
}

//Retourne le nom de la tuile en fonction de sa forme et de sa couleur
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
