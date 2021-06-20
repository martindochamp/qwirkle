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

void genererPioche(t_tuile* tuiles, int modeDeJeu);

void afficherMainsJoueurs(t_tuile** mains, char** pseudos, int nbJoueurs);

void Color(int couleurDuTexte,int couleurDeFond);

void retournerNomTuile(t_tuile tuile, char* nomTuile);

void distribuerTuiles(t_tuile** mains, t_tuile* pioche, int nbJoueurs, int modeDeJeu, int* index);

void remplacerTuile(t_tuile* tuile, t_tuile* pioche, int* index);

#endif // TUILES_H_INCLUDED
