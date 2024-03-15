#include "headers/fileio.h"
#include "headers/tools.h"





BOOL createFile(data* data){
    if(!data->arg){
        wprintf(L"Usage: fcreate [filename]");
        return FALSE;
    }
    HANDLE hFile = CreateFileW(data->arg, 
                              GENERIC_READ | GENERIC_WRITE, 
                              0,
                              NULL,
                              CREATE_ALWAYS,
                              FILE_ATTRIBUTE_NORMAL,
                              NULL);
    if(hFile == INVALID_HANDLE_VALUE){
        wprintf(L"Failed Creating File, Error Code %d\n", GetLastError());
        CloseHandle(hFile);
        return FALSE;
    }
    CloseHandle(hFile);
    return TRUE;
}

BOOL deleteFile(data* data){
    if(!data->arg){
        wprintf(L"Usage: fdelete [filename]");
        return FALSE;
    }
    BOOL result = DeleteFileW(data->arg);
    if(result == FALSE){
        wprintf(L"Failed Deleting File, Error Code %d\n", GetLastError());\
        return FALSE;
    }
    return TRUE;
}

BOOL copyFile(data* data){
    if(!data->arg){
        wprintf(L"Usage: fcopy [filename1] [filename2]");
        return FALSE;
    }
    WCHAR* firstFile;
    WCHAR* secondFile;
    WCHAR* holder;
    firstFile = wcstok(data->arg, L" ", &holder);
    secondFile = wcstok(NULL, L"\n", &holder);
    if(!secondFile){
        wprintf(L"Usage: fcopy [filename1] [filename2]");
        return FALSE;
    }
    debugPrint(data, L"First File is %s, Second is %s\n", firstFile, secondFile);
    BOOL result = CopyFileW(firstFile, secondFile, FALSE);
    if(result == FALSE){
        wprintf(L"Failed Copying File, Error Code %d\n", GetLastError());\
        return FALSE;
    }
    return TRUE;
}