#include "headers/dirio.h"




VOID moveDirectory(data* data){
    if(!data->arg){
        wprintf(L"Usage: moveto [direcotry], moves to that directory\n");
        return;
    }
    
    BOOL result = SetCurrentDirectoryW(data->arg);
    if(!result){
        wprintf(L"Error Changing Directory, Error Code %d\n", GetLastError());
        return;
    }
    if(data->path == NULL){
        data->path = (WCHAR*)malloc(BUFSIZE);
        GetCurrentDirectoryW(BUFSIZE, data->path);
        goto PRINT;
        return;
    }
    GetCurrentDirectoryW(BUFSIZE, data->path);
PRINT:
    wprintf(L"Current Directory is %s\n", data->path);
}

VOID createDirectory(data* data){
    if(!data->arg){
        wprintf(L"Usage: dcreate [direcotry], creates that directory\n");
        return;
    }
    BOOL result = CreateDirectoryW(data->arg, NULL);
    if(!result){
        wprintf(L"Failed Creating Direcotry, Error Code %d\n", GetLastError());
    }
    return;
}

VOID deleteDirectory(data* data){
    if(!data->arg){
        wprintf(L"Usage: ddelete [direcotry], deletes that directory\n");
        return;
    }
    BOOL result = RemoveDirectoryW(data->arg);
    if(!result){
        wprintf(L"Failed Deleting Direcotry, Error Code %d\n", GetLastError());
    }
    return;
}