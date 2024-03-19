#include "headers/misc.h"


VOID help(){
    wprintf(L"echo [a] - prints a                                                    | fcreate [file] - creates file\n");   
    wprintf(L"fdelete [file] - deletes file                                          | fcopy [file] [file2] - copys file to file2\n");
    wprintf(L"fread [file] - reads file                                              | fwrite [file] [content] - writes file\n");
    wprintf(L"fprint [file] [content] - writes file without erasing everything       | MORE COMMANDS COMING!!!!\n");



}

VOID crash(){
    WCHAR* idk;
    wcscpy(idk, L"lol");
}


VOID pause(){
    wprintf(L"Press Any Key To Continue To Layl\n");
    _getwch();
}