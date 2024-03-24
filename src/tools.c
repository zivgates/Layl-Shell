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

char* wcharToChar(const wchar_t* str) {
    int size = WideCharToMultiByte(CP_UTF8, 0, str, -1, NULL, 0, NULL, NULL);
    char* buffer = (char*)malloc(size);
    if (buffer != NULL) {
        WideCharToMultiByte(CP_UTF8, 0, str, -1, buffer, size, NULL, NULL);
    }
    return buffer;
}


WCHAR* toLowerCase(WCHAR* string){
    for(int i = 0; string[i]; i++){
        string[i] = towlower(string[i]);
    }
    return string;
}

void debugPrint(data *data, const wchar_t *format, ...) {
    if(data->isDebug != TRUE) return;
    va_list args;
    va_start(args, format);
    vwprintf(format, args);
    va_end(args);
}