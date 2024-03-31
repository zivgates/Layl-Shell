#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include <Windows.h>
#include <wchar.h>
#include <DbgHelp.h>

#define BUFSIZE 4096
#define VER 0.201


typedef struct _fileInfo{
    WCHAR* fileName;
    WCHAR fileContentBuffer[BUFSIZE];
    WCHAR* nonNewLineChar;
} fileInfo;

typedef struct _cliInfo{
    WCHAR buffer[BUFSIZE];
    WCHAR* nonNewLineChar;
} cliInfo;

typedef struct _data{
    WCHAR* cmd;
    WCHAR* arg;
    WCHAR* path;
    BOOL isDebug;
    int currentCmd;
} data;

#endif