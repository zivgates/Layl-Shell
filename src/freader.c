#include "headers/freader.h"
#include "headers/tools.h"
#include "headers/cmdChecker.h"



BOOL startReader(fileInfo* info){
    data data;
    data.state = 0;
    WCHAR* context;
    FILE* file = _wfopen(info->fileName, L"r");
    info->fileContentBuffer = (WCHAR*)malloc(BUFSIZE + 1);
    if(file == NULL){
        _wperror(L"Failed Opening File");
        return FALSE;
    }
    while(fgetws(info->fileContentBuffer, BUFSIZE, file)){
        if(info->fileContentBuffer != NULL){
            WCHAR* token = wcstok(info->fileContentBuffer, L"\n", &context);
            while (token != NULL) {
                info->nonNewLineChar = token;
                if (info->nonNewLineChar != NULL) {
                    lineParser(info->nonNewLineChar, &data);
                    cmdChecker(&data);
                }
                token = wcstok(NULL, L"\n", &context);
            }
        }
    }
    return TRUE;
}

