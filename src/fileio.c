#include "headers/fileio.h"
#include "headers/tools.h"
#include <fileapi.h>





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
        wprintf(L"Failed Creating File, Error Code %d\n", GetLastError());
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
    if(result == FALSE){
        wprintf(L"Failed Deleting File, Error Code %d\n", GetLastError());\
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
    debugPrint(data, L"First File is %s, Second is %s\n", firstFile, secondFile);
    BOOL result = CopyFileW(firstFile, secondFile, FALSE);
    if(result == FALSE){
        wprintf(L"Failed Copying File, Error Code %d\n", GetLastError());\
        return FALSE;
    }
    return TRUE;
}

BOOL writeFile(data* data){
    if(!data->arg){
        wprintf(L"Usage: fwrite [filename] [content]\n");
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
    debugPrint(data, L"First File is %s, Content is %s\n", firstFile, content);

    HANDLE hFile = CreateFileW(firstFile, 
                             GENERIC_WRITE, 
                             0, 
                             NULL,
                             OPEN_ALWAYS,
                             FILE_ATTRIBUTE_NORMAL,
                             NULL);
    if(hFile == INVALID_HANDLE_VALUE){
        wprintf(L"Failed Creating File, Error Code %d\n", GetLastError());
        CloseHandle(hFile);
        return FALSE;
    }
    BOOL result = WriteFile(hFile, 
             content, 
             wcslen(content), 
             NULL, 
             NULL);
    if(result == FALSE){
        wprintf(L"Failed Writing File, Error Code %d\n", GetLastError());
        CloseHandle(hFile);
        return FALSE;
    }
    CloseHandle(hFile);
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
        wprintf(L"Failed Creating File, Error Code %d\n", GetLastError());
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
        wprintf(L"Failed Reading File, Error Code %d\n", GetLastError());
        return FALSE;
    }
    CloseHandle(hFile);
    return TRUE;
}