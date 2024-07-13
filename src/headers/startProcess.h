#ifndef STARTPROCESS_H_INCLUDED
#define STARTPROCESS_H_INCLUDED


#include "main.h"

INT createProcess(WCHAR* process, WCHAR* arguments);
VOID startProcess(data* data);
VOID quickStartProcess(data* data);
VOID quickStartProcessinNewWindow(data* data);

typedef struct _processCreation{
    WCHAR* processName;
    WCHAR* processArgs;
} processCreation;

#endif