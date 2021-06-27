#ifndef TUILES_H_INCLUDED
#define TUILES_H_INCLUDED

typedef struct Tuiles
{
    int couleur;
    char forme;
} t_tuile;

void afficherStructure(t_tuile* tuile);

void remplirStructure(t_tuile *tuile);

void prgmTuiles();

void genererPioche(t_tuile tuiles[108], int modeDeJeu);

void afficherMainsJoueurs(t_tuile mains[4][6], char pseudos[4][20], int nbJoueurs);

void Color(int couleurDuTexte,int couleurDeFond);

void retournerNomTuile(t_tuile tuile, char* nomTuile);

void distribuerTuiles(t_tuile main[6], t_tuile pioche[108], int* index);

void remplacerTuile(t_tuile* tuile, t_tuile pioche[108], int* index, int modeDeJeu);

void echangerTuile(t_tuile* tuile, t_tuile pioche[108], int index, int modeDeJeu);

#endif // TUILES_H_INCLUDED
