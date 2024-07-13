#ifndef PROCESSCONFIG_H_INCLUDED
#define PROCESSCONFIG_H_INCLUDED

#include "main.h"

extern NTSTATUS NTAPI NtSuspendProcess(HANDLE);
extern NTSTATUS NTAPI NtResumeProcess(HANDLE);

VOID processConfigurer(data* data);

#endif