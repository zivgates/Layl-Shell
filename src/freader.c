#include "headers/freader.h"
#include "headers/tools.h"
#include "headers/cmdChecker.h"



BOOL startReader(fileInfo* info){
    char buffer[BUFSIZE];
    HANDLE hFile = CreateFileW(info->fileName, 
                              GENERIC_READ, 
                              0, 
                              NULL, 
                              OPEN_EXISTING, 
                              FILE_ATTRIBUTE_NORMAL, 
                              NULL);
    if(hFile == INVALID_HANDLE_VALUE){
        wprintf(L"Failed Opening File, Error Code %d\n", GetLastError());
        return FALSE;
    }
    BOOL readFileStatus = ReadFile(hFile, 
                                  buffer, 
                                  BUFSIZE, 
                                  NULL, 
                                  NULL);
    if(readFileStatus != TRUE){
        wprintf(L"Failed Reading File, Error Code %d\n", GetLastError());
        CloseHandle(hFile);
        return FALSE;
    }
    CloseHandle(hFile);
    info->fileContentBuffer = charToWchar(buffer);
    WCHAR* holder;
    WCHAR* token = wcstok(info->fileContentBuffer, L"\n", &holder);
    
    while(token != NULL){
        data currentdata;
        lineParser(token, &currentdata);
        cmdChecker(&currentdata);
        token = wcstok(NULL, L"\n", &holder);
    }
    return TRUE;
}
