#include "interfaces.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
void PartieNormale()
{
    printf("Hehe");
}
void PartieDegradee()
{
    printf("Hehehe");
}

void ReglesJeu()
{//Règles du sujet !
    printf("Voici les regles du jeu:\n"); //en gros et gras
    printf("Chaque joueur dispose de 6 tuiles. A son tour, il en place un maximum a condition de les poser sur une seule ligne avec un ");
    printf("caractere commun: la couleur ou la forme. \nA chaque tour on marque les points des lignes que l on a completees. ");
    printf("\nL astuce consiste a placer ses pieces a des endroits strategiques, comme par exemple des intersections, pour marquer ");
    printf("un maximum de points.\n\n");
    printf("1. Materiel: \n"); //en gras
    printf("  - Mode normal : 108 tuiles pour 6 formes et 6 couleurs. Chaque forme est donc presente 3 fois dans une meme couleur dans la pioche.\n");
    printf("  - Mode degrade : 36 tuiles pour 6 formes et 6 couleurs. Chaque forme n est presente qu une fois dans une meme couleur dans la pioche.\n");
    printf("  - Zone de jeu de 12 x 26 cases \n\n");
    printf("2. But du jeu: \nAligner des tuiles ayant des symboles de formes ou de couleurs identiques (mais pas les deux) de facon ");
    printf("a realiser des combinaisons rapportant un maximum de points.\n\n");
    printf("3. Preparation:\n"); //en gras
    printf("La pioche contient les 108 tuiles qui seront prises au hasard par les joueurs pour completer leur pupitre apres chaque tour.\n\n");
    printf("4. Debut de partie:\n"); //en gras
    printf("L ordinateur demande si on joue en mode degrade ou normal (contenu de la pioche different) ainsique le nombre de joueurs pour la");
    printf("partie, entre 2, 3 et 4.\nIl enregistre les pseudos pour chaque joueur.\n\n");
    printf("L ordinateur pioche au hasard six tuiles dans la pioche et les place sur le pupitre de chaque joueur, en les maintenant cachees de facon a ce qu aucun autre ");
    printf("joueur ne puisse voir les symboles. Ces tuiles forment la « main » du joueur. Les tuiles restantes forment la « pioche ».\n\n");
    printf("L ordinateur demarre la partie avec le joueur 1 (premier pseudo enregistre). Il revele le pupitre du joueur concerne et lance la partie en permettant au joueur \n");
    printf("concerne de poser une ou plusieurs tuiles à l endroit de son choix sur la zone de jeu. \n\n");
    printf("Apres la pose des tuiles par le joueur sur la zone de jeu, l ordinateur calcule les points obtenus, affiche les points du coup et le cumul depuis le debut de \n");
    printf("partie pour ce joueur. L’ordinateur preleve aleatoirement de nouvelles tuiles dans la pioche pour avoir à nouveau 6 tuiles sur le pupitre du joueur, \n");
    printf("tout en masquant de nouveau les 6 tuiles. Le joueur ne voit donc pas les nouvelles tuiles piochees.");
    printf("En appuyant sur la barre d espace, l ordinateur passe au joueur suivant.\n");
    printf("Lorsque tous les joueurs ont joue, l ordinateur demande si on veut arreter la partie ou passer au tour suivant pour l ensemble des joueurs.\n\n");
    printf("Les joueurs jouent a tour de role dans le sens des aiguilles d une montre (ou le sens croissant et cyclique des numeros de joueur).\n`\n");
    printf("5. Deroulement de la partie:\n"); //en gras
    printf("A son tour, un joueur voit son pupitre revele a l ecran. Il peut effectuer l une de ces trois actions :\n");
    //une partie en gras
    printf("A. Ajouter une tuile a une ligne ou a une colonne. L ordinateur masque les tuiles restantes sur le pupitre et pioche une tuile dans la reserve pour en avoir ");
    printf("a nouveau six tuiles sur le pupitre du joueur.");
    //une partie en gras
    printf("B. Ajouter deux tuiles ou plus a une ligne (ou colonne). Toutes les tuiles jouees a partir de la main du joueur doivent partager une caracteristique, a savoir\n");
    printf("la couleur ou la forme. Les tuiles du joueur doivent toujours etre posees sur la meme ligne (ou colonne) (il se peut qu elles ne se touchent pas).\n");
    printf("Ensuite, l ordinateur masque les tuiles restantes sur le pupitre et pioche une ou plusieurs tuiles dans la reserve pour en avoir a nouveau six sur le pupitre du joueur.\n");
    //une partie en gras
    printf("C. Echanger tout ou partie des tuiles de sa main contre differentes tuiles de la reserve, et passer son tour (sans jouer de tuile).\n\n");
    printf("Ajouter des tuiles a une ligne (ou colonne)\n"); //Couleur orange
    printf("Chacun a leur tour, les joueurs ajoutent des tuiles a la ligne creee au premier tour sans deborder l espace de jeu. Tous les coups joues doivent etre lies a la ligne existante.");
    while (!kbhit());
    char c;
    getc(c);

}

void ModeJeu()
{
    int ch2;

    do{
        printf("Veuillez choisir votre mode de jeu\n");
        printf("1. Mode normal\n");
        printf("2. Mode degrade\n");

    fflush(stdin);
    scanf("%d", &ch2);

    switch(ch2){
        case 1:
            PartieNormale();
            break;
        case 2:
            PartieDegradee();
            break;
        }
    }while(0);
}

void afficherMenu()
{
    int ch1;
    char key='q';

    do{
        system("cls");
        printf("Bonjour et bienvenue dans le Qwirkle!\n");
        printf("1. Consulter les regles du jeu\n");
        printf("2. Demarrer une nouvelle partie\n");
        printf("3. Reprendre une partie sauvegardee\n");
        printf("4. Consulter l'ensemble des scores des joueurs\n");
        printf("5. Quitter le jeu\n");
        fflush(stdin);
        scanf("%d", &ch1);

    switch(ch1){
        case 1:
            printf("Pour retourner au menu principal, tapez q");
            ReglesJeu();
            if (kbhit()){
                system("CLS");
                afficherMenu();
            }
            break;
        case 2:
            ModeJeu();
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            printf("Au revoir et a bientot !");
            break;
        default :
            printf("Faux");
        }
    }while((ch1<1)||(ch1>4));
}

void emmaPrgm() {
    printf("Wow c'est Emma");
    afficherMenu();
    ReglesJeu;

}
