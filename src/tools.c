#include "headers/tools.h"




VOID lineParser(WCHAR buffer[], data* data){
    WCHAR buffr[BUFSIZE];
    wcscpy(buffr, buffer);
    data->cmd = wcstok(buffr, L" \n", &buffer);
    data->arg = wcstok(NULL, L"\n", &buffer);
}

WCHAR* charToWchar(const char* str){
    int wstrLength = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
    WCHAR* wstr = (WCHAR*)malloc((wstrLength + 1) * sizeof(WCHAR));
    if(MultiByteToWideChar(CP_UTF8, 0, str, -1, wstr, wstrLength) == 0){
        free(wstr);
        return NULL;
    }
    wstr[wstrLength] = L'\0';
    return wstr;

}