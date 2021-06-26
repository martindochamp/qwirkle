#ifndef IA_H_INCLUDED
#define IA_H_INCLUDED

/*

Tester chaque coup possible, si vrai, calculer point
Stocker coups vraies et scores qu'ils apportent
Jouer le meilleur coup

*/

typedef struct Coup {
    int x;
    int y;
    int point;
    int numeroTuile;
} t_coup;

void testerCoups(t_tuile plateau[26][12], t_tuile main[6], int* x, int* y, int* tuile, int coup);


#endif // IA_H_INCLUDED
