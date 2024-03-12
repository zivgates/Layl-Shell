#include "headers/fallback.h"



static BOOL createMemoryDump(char* filename){
    HANDLE pHandle = GetCurrentProcess();
    if(!pHandle){
        wprintf(L"Cannot Create Handle For Process\n");
        return FALSE;
    }
    HANDLE dumpFile = CreateFile(filename, GENERIC_ALL, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if(!dumpFile){
        wprintf(L"Cannot Create File For Dump\n");
        return FALSE;
    }
    MiniDumpWriteDump(pHandle, GetCurrentProcessId(), dumpFile, MiniDumpWithFullMemory, NULL, NULL, NULL);
    CloseHandle(dumpFile);
    return TRUE;
}

VOID startRecovery(struct _EXCEPTION_POINTERS* info){
    wprintf(L"Layl Shell Has Crashed\nWriting Dump File Into C:\\ProgramData\\LaylShellDump.dmp\n");
    if(!createMemoryDump("C:\\ProgramData\\LaylShellDump.dmp")) wprintf(L"Cannot Create Dump");
    wprintf(L"Crash Info: \n");
    wprintf(L"Exception Code is 0x%1lx\n", info->ExceptionRecord->ExceptionCode);
    wprintf(L"Exception Address in 0x%1llx\n", (unsigned long long)info->ExceptionRecord->ExceptionAddress);
    wprintf(L"\n\nWill Return To Shell in 10 Seconds\n");
    Sleep(10000);
    ExitThread(-1);
    return;
}