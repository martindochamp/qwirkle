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

void distribuerTuiles(t_tuile** mains, t_tuile* pioche, int nbJoueurs, int modeDeJeu);

void afficherMainsJoueurs(t_tuile** mains, char** pseudos, int nbJoueurs);

Color(int couleurDuTexte,int couleurDeFond);

#endif // TUILES_H_INCLUDED
