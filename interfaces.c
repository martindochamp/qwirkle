#include "interfaces.h"

void PartieNormale()
{
    printf("Hehe");
}
void PartieDegradee()
{
    printf("Hehehe");
}

void ReglesJeu()
{
    printf("Voici les regles du jeu:\n ");
    printf("Vous avez ");
}

void ModeJeu()
{
    int ch2;

    printf("Veuillez choisir votre mode de jeu\n");
    printf("1. Mode normal\n");
    printf("2. Mode degrade\n");

    do{
        fflush(stdin);
        scanf("%d", &ch2);
    } while((ch2<1)&&(ch2>2));

    switch(ch2){
        case 1:
            PartieNormale();
            break;
        case 2:
            PartieDegradee();
            break;
    }
}

void afficherMenu()
{
    int ch1;

    printf("Bonjour et bienvenue dans le Qwirkle!\n");
    printf("1. Consulter les regles du jeu\n");
    printf("2. Demarrer une nouvelle partie\n");
    printf("3. Reprendre une partie sauvegardee\n");
    printf("4. Consulter l'ensemble des scores des joueurs\n");

    do{
        fflush(stdin);
        scanf("%d", &ch1);
    } while((ch1<1)&&(ch1>4));

    switch(ch1){
        case 1:
            ReglesJeu();
            break;
        case 2:
            ModeJeu();
            break;
        case 3:
            break;
        case 4:
            break;
    }
}

void emmaPrgm() {
    printf("Wow c'est Emma");
    afficherMenu();
    ReglesJeu;

}
