#include "headers/misc.h"


VOID help(){
    wprintf(L"echo [a] - prints a                                                    | fcreate [file] - creates file\n\n");   
    wprintf(L"fdelete [file] - deletes file                                          | fcopy [file] [file2] - copys file to file2\n\n");
    wprintf(L"fread [file] - reads file                                              | fwrite [file] [content] - writes file\n\n");
    wprintf(L"fprint [file] [content] - writes file without erasing everything       | moveto [directory] - moves to the directory\n\n");
    wprintf(L"wait [ms] - pauses the shell for specified seconds                     | pause - Pauses Layl till Key-Press is found\n\n");
    wprintf(L"dcreate [dirName] - creates that directory                             | ddelete [directory] - deletes that directory\n\n");
    wprintf(L"pd {directory (optional)} - prints that directory content              | cd - prints what directory you are in\n\n");
    wprintf(L"start [perms] [process] {parameter (optional)} - starts a process with the perms you gived it with the parameter\n(for more info do start with nothing else)\n\n");
    wprintf(L"process [arg] - runs the process cmd with the args (more info type process /?)\n\n");
    wprintf(L"power [type] [isImmediate], does specifc power settings and checks if isImmediate (if 1)\n\n");
    wprintf(L"reg [dowhat] [hkey] [regpath] {valuename} (only for -w) {datatype} (only for -w)\nEdits Registry with Values\n\n");
    wprintf(L"driveinfo [drive], drive is the drive name (C: or D:), gives drive info\n\n");
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