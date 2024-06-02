#include "headers/misc.h"


VOID help(){
    wprintf(L"https://github.com/realzvqle/layl-shell\n");
}

VOID crash(){
    WCHAR* idk;
    wcscpy(idk, L"lol");
}


VOID pause(){
    wprintf(L"Press Any Key To Continue To Layl\n");
    _getwch();
}

static VOID cls(HANDLE hConsole)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    SMALL_RECT scrollRect;
    COORD scrollTarget;
    CHAR_INFO fill;
    if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
    {
        return;
    }
    scrollRect.Left = 0;
    scrollRect.Top = 0;
    scrollRect.Right = csbi.dwSize.X;
    scrollRect.Bottom = csbi.dwSize.Y;
    scrollTarget.X = 0;
    scrollTarget.Y = (SHORT)(0 - csbi.dwSize.Y);
    fill.Char.UnicodeChar = TEXT(' ');
    fill.Attributes = csbi.wAttributes;
    ScrollConsoleScreenBuffer(hConsole, &scrollRect, NULL, scrollTarget, &fill);
    csbi.dwCursorPosition.X = 0;
    csbi.dwCursorPosition.Y = 0;
    SetConsoleCursorPosition(hConsole, csbi.dwCursorPosition);
}

VOID clrscr(){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    cls(hConsole);
}





VOID memleak(int size){
    while(1){
        malloc(size);
        Sleep(50);
    }
}