#include "headers/fileio.h"
#include "headers/tools.h"
#include <corecrt_wstdio.h>
#include <corecrt_wstdlib.h>
#include <stdio.h>
#include <wchar.h>


BOOL createFile(data* data){
    if(!data->arg){
        wprintf(L"Usage: fcreate [filename]\n");
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
        GetErrorMessage(GetLastError());
        CloseHandle(hFile);
        return FALSE;
    }
    CloseHandle(hFile);
    return TRUE;
}

BOOL deleteFile(data* data){
    if(!data->arg){
        wprintf(L"Usage: fdelete [filename]\n");
        return FALSE;
    }
    
    BOOL result = DeleteFileW(data->arg);
    debugPrint(data, L"File is %s\n", data->arg);
    if(result == FALSE){
        GetErrorMessage(GetLastError());
        return FALSE;
    }
    return TRUE;
}

BOOL copyFile(data* data){
    if(!data->arg){
        wprintf(L"Usage: fcopy [filename1] [filename2]\n");
        return FALSE;
    }
    WCHAR* firstFile;
    WCHAR* secondFile;
    WCHAR* holder;
    firstFile = wcstok(data->arg, L" ", &holder);
    secondFile = wcstok(NULL, L"\n", &holder);
    if(!secondFile){
        wprintf(L"Usage: fcopy [filename1] [filename2]\n");
        return FALSE;
    }
  

    BOOL result = CopyFileW(firstFile, secondFile, FALSE);
    if(result == FALSE){
        GetErrorMessage(GetLastError());
        return FALSE;
    }
    return TRUE;
}


BOOL writeFile(data* data){
    if(!data->arg){
        wprintf(L"Usage: fprint [filename] [content]\n");
        return FALSE;
    }
    WCHAR* firstFile;
    WCHAR* content;
    WCHAR* holder;
    firstFile = wcstok(data->arg, L" ", &holder);
    content = wcstok(NULL, L"\n", &holder);
    if(!content){
        wprintf(L"Usage: fwrite [filename] [content]\n");
        return FALSE;
    }
    
    FILE* file = _wfopen(firstFile, L"a");
    if(file == NULL){
        wprintf(L"Failed Opening File\n");
        return FALSE;
    }
    fwprintf(file, content);
    fwprintf(file, L"\n");
    fclose(file);
    return TRUE;
}

BOOL readFile(data* data){
    if(!data->arg){
        wprintf(L"Usage: fread [filename]\n");
        return FALSE;
    }
    WCHAR buffer[BUFSIZE];
    HANDLE hFile = CreateFileW(data->arg, 
                              GENERIC_READ | GENERIC_WRITE, 
                              0,
                              NULL,
                              OPEN_EXISTING,
                              FILE_ATTRIBUTE_NORMAL,
                              NULL);
    if(hFile == INVALID_HANDLE_VALUE){
        GetErrorMessage(GetLastError());
        CloseHandle(hFile);
        return FALSE;
    }
    BOOL result = ReadFile(hFile,
                          buffer,
                          BUFSIZE,
                          NULL,
                          NULL);
    if(result == FALSE){
        CloseHandle(hFile);
        GetErrorMessage(GetLastError());
        return FALSE;
    }
    wprintf(L"%hs\n", buffer);
    CloseHandle(hFile);
    return TRUE;
}


VOID lywrite(data* data){
    if(!data->arg){
        wprintf(L"usage: lywrite [filename]\n");
        return;
    }
    FILE* file = _wfopen(data->arg, L"a");
    if(!file){
        _wperror(L"Couldn't Open File");
        return;
    }
    WCHAR buffer[521];
    WCHAR* context;
    int i = 0;
    WCHAR intro[512];
    swprintf(intro, 512, L"Layl LyWrite Build %.3f\nCopyright ZivGates Community, all rights reserved\n\ntype '$exit' to exit the editor", VER);
    wprintf(L"%s\n\n", intro);
    while(TRUE){
        PASS:
        i++;
        wprintf(L"%d~ ", i);
        fgetws(buffer, BUFSIZE, stdin);
        WCHAR* new = wcstok(buffer, L"\n", &context);
        if(!new){
            goto PASS;
        }
        if(wcscmp(new, L"$exit") == 0){
            break;
        }
        fwprintf(file, L"%s\n", new);
    }
    fclose(file);
    return;
}