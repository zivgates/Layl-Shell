#include "headers/cli.h"
#include "headers/tools.h"
#include "headers/cmdChecker.h"



BOOL startCli(cliInfo *info){
    data data;
    data.path = NULL;
    WCHAR* context;
    while(1){
PASS:
        wprintf(L"-> ");
        if(fgetws(info->buffer, BUFSIZE, stdin) == NULL) goto PASS;
        info->nonNewLineChar = wcstok(info->buffer, L"\n", &context);
        if(info->nonNewLineChar == NULL) goto PASS;
        lineParser(info->nonNewLineChar, &data);
        cmdChecker(&data);
    }
    return TRUE;
}