#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>

#include "interfaces.h"
#include "tuiles.h"
#include "etatJeu.h"
#include "plateau.h"

#define _WIN32_WINNT 0x0500
HANDLE wHnd;
HANDLE rHnd;

void tailleConsole();
void enleverScrollBar();
void menuLancement();

int main()
{
    HWND consoleWindow = GetConsoleWindow();
    SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);

    tailleConsole();
    enleverScrollBar();
    int res;
    do {
        printf("Mode de fonctionnement du prgm : \n");
        printf("1. Test menu\n");
        printf("2. Lisa\n");
        printf("3. Martin\n");
        scanf("%d", &res);
    } while(!(res > 0 && res <= 4));

    switch(res) {
    case 1:
        emmaPrgm();
        return 0;
    case 2:
        prgmTuiles();
        return 0;
    case 3:
        menuLancement();
        preparationJeu();
        return 0;
    case 4:
        afficherKb();
    }
    return 0;
}

void afficherKb() {
    int res;
    while(true) {
        while(!kbhit());
        res = getch();
        system("cls");
        printf("%d", res);
    }
}

void menuLancement() {
    system("cls");
    positionnerCurseur(44, 12);

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

    positionnerCurseur(41, 17);
    Color(15, 0);
    printf("Appuyer sur une touche pour commencer");

    while(!kbhit());

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
