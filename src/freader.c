#include "headers/freader.h"
#include "headers/tools.h"
#include "headers/cmdChecker.h"



BOOL startReader(fileInfo* info){
    data data;
    data.path = NULL;
    WCHAR* context;
    FILE* file = _wfopen(info->fileName, L"r");
    if(file == NULL){
        _wperror(L"Failed Opening File\n");
        return FALSE;
    }
    while(fgetws(info->fileContentBuffer, BUFSIZE, file)){
        info->nonNewLineChar = wcstok(info->fileContentBuffer, L"\n", &context);
        //if(info->nonNewLineChar == NULL) goto PASS;
        lineParser(info->nonNewLineChar, &data);
        cmdChecker(&data);
    }
    

    return TRUE;
}
