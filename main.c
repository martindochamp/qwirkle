#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>

#include "interfaces.h"
#include "tuiles.h"
#include "etatJeu.h"
#include "plateau.h"

HANDLE wHnd;
HANDLE rHnd;

void tailleConsole();
void enleverScrollBar();

int main()
{
    tailleConsole();
    enleverScrollBar();
    int res;
    do {
        printf("Mode de fonctionnement du prgm : \n");
        printf("1. Test menu\n");
        printf("2. Lisa\n");
        printf("3. Martin\n");
        scanf("%d", &res);
    } while(!(res > 0 && res < 4));

    switch(res) {
    case 1:
        emmaPrgm();
        return 0;
    case 2:
        prgmTuiles();
        return 0;
    case 3:
        preparationJeu();
        return 0;
    }
    return 0;
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
