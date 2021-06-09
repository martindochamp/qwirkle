#ifndef TUILES_H_INCLUDED
#define TUILES_H_INCLUDED
#include <windows.h>

typedef struct Tuiles
{
    int couleur[6];
    char forme[6];
} t_Tuiles

void remplirStructure(t_Tuiles *Tuiles )
{
    (*Tuiles).couleur[0]= {4};
    (*Tuiles).forme[6]= {0x03, 0x04, 0x05, 0x06, 0x07, 0xDB,};

    return t_Tuiles *Tuiles;

}
void afficherStructure (t_Tuiles Tuiles )
{
    printf("%s",(Tuiles).couleur);

}


int main() // La fonction "main"
{
    t_Tuiles Tuiles;
    remplirStructure(&Tuiles);
    afficherStructure (Tuiles);
    return 0;
}

void Color(t_Tuiles *Tuiles )
HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
SetConsoleTextAttribute(H,(*Tuiles).couleur);
}


#endif // TUILES_H_INCLUDED
