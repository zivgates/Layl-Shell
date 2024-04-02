#ifndef TOOLS_H_INCLUDED
#define TOOLS_H_INCLUDED

#include "main.h"


WCHAR* charToWchar(const char* str);
VOID lineParser(WCHAR buffer[], data* data);
WCHAR* toLowerCase(WCHAR* string);
VOID debugPrint(data* data, const WCHAR* format, ...);
char* wcharToChar(const wchar_t* str);
BOOL checkAdmin();
BOOL checkIfFileExist(WCHAR* fileName);

#endif