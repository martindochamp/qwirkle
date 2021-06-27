#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#include <winver.h>

#include "interfaces.h"
#include "tuiles.h"
#include "etatJeu.h"
#include "plateau.h"
#include "sauvegarde.h"

#define _WIN32_WINNT 0x0500

HANDLE wHnd;
HANDLE rHnd;

void tailleConsole();
void enleverScrollBar();
int menuLancement();
void cacherCurseur();
void afficherKb();
void afficherCurseurCoeur(int phrase, int choix);

int main()
{
    HWND consoleWindow = GetConsoleWindow();
    SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);

    tailleConsole();
    enleverScrollBar();
    cacherCurseur();

    int choixMenu;
    do {
        choixMenu = menuLancement();
        switch (choixMenu) {
            case 1:
                preparationJeu();
                break;
            case 2:
                menuSauvegardes();
                break;
            case 3:
                reglesDuJeu();
                break;
            case 4:
                afficherKb();
                break;
            case 5:
                PostMessage(GetConsoleWindow(), WM_CLOSE, 0, 0);
        }
    } while (choixMenu != 5);

    return 0;
}

void afficherKb() {
    system("cls");
    for (int i = 0; i < 16; i++) {
        Color(i, 0);
        printf("Couleur #%d ", i);
    }
    int res;
    while(true) {
        while(!kbhit());
        res = getch();
        system("cls");
        printf("%d", res);
    }
}

int menuLancement() {
    system("cls");
    int res;
    positionnerCurseur(44, 11);

    int couleurs[] = {4, 15, 4, 15, 4, 15};
    char formes[] = {0x03, 0x04, 0x05, 0x0F, 0x06, 0xFE};

    for (int i = 0; i < 6; i++) {
        Color(couleurs[i], 0);
        printf("%c ", formes[i]);
    }

    Color(14, 0);
    printf("Qwirkle ");

    for (int i = 5; i >= 0; i--) {
        Color(couleurs[i], 0);
        printf("%c ", formes[i]);
    }

    Color(15, 0);

    int selection = 1;
    int marges[5] = {2, 1, 4, 7, 7};
    for (int i = 0; i < 5; i++) {
        positionnerCurseur(45+marges[i], 13+i);
        afficherCurseurCoeur(i, selection);
    }

    do {
        while (!kbhit());
        res = getch();

        int surplus = selection;
        if (res == 72 && selection > 1)
            selection--;

        if (res == 80 && selection < 5)
            selection++;

        //On efface les choix qui changent
        for (int i = 0; i < 40; i++) {
            positionnerCurseur(50+i, 12+selection);
            printf(" ");
            positionnerCurseur(50+i, 12+surplus);
            printf(" ");
        }

        positionnerCurseur(45+marges[selection-1], 12+selection);
        afficherCurseurCoeur(selection-1, selection);

        positionnerCurseur(45+marges[surplus-1], 12+surplus);
        afficherCurseurCoeur(surplus-1, selection);
    } while(res != 13);
    return selection;
}

void afficherCurseurCoeur(int phrase, int choix) {
    char phrases[5][30] = {"Lancer une partie", "Reprendre la partie", "Regles du jeu", "Credits", "Quitter"};
    if (phrase+1 == choix) {
        Color(11, 0);
        printf("%c %c ", 0x06, 0x04);
        Color(15, 0);
        printf("%s", phrases[phrase]);
        Color(11, 0);
        printf(" %c %c", 0x04, 0x06);
    } else {
        Color(7, 0);
        printf("    %s", phrases[phrase]);
    }
}

//Source : https://cboard.cprogramming.com/cplusplus-programming/97959-[ask]-how-remove-scrollbar.html
void enleverScrollBar()
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(handle, &info);
    COORD new_size =
    {
        info.srWindow.Right - info.srWindow.Left + 1,
        info.srWindow.Bottom - info.srWindow.Top + 1
    };
    SetConsoleScreenBufferSize(handle, new_size);
}

//Source : https://stackoverflow.com/questions/30126490/how-to-hide-console-cursor-in-c
void cacherCurseur()
{
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}

//Source : https://followtutorials.com/2011/09/how-to-resize-console-window-using-c.html
void tailleConsole() {
    wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
    rHnd = GetStdHandle(STD_INPUT_HANDLE);
    SetConsoleTitle("Qwirkle : Alignez les tuiles !");
    SMALL_RECT windowSize = {0, 0, 120, 25};
    SetConsoleWindowInfo(wHnd, 1, &windowSize);
    COORD bufferSize = {10, 10};
    SetConsoleScreenBufferSize(wHnd, bufferSize);
}
