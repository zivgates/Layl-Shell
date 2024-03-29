#include "headers/power.h"
#include <winternl.h>
#include <powrprof.h>



typedef NTSTATUS(WINAPI *PNtShutdownSystem)(ULONG);


static inline BOOL giveShutDownPerms(){
    HANDLE hToken;
    TOKEN_PRIVILEGES tkp;
    if(!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)){
        wprintf(L"Cannot Open Process Token, Error Code %lu\n", GetLastError());
        return FALSE;
    }
    LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, (PLUID)&tkp.Privileges);
    tkp.PrivilegeCount = 1;
    tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
    if(!AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0)){
        wprintf(L"Cannot Change Token Privlages, Error Code %lu\n", GetLastError());
        CloseHandle(hToken);
        return FALSE;
    }
    CloseHandle(hToken);
    return TRUE;
}


static VOID forceShutdown(WCHAR* type, WCHAR* isValid){
    if(wcscmp(isValid, L"1") != 0) return;
     if (!giveShutDownPerms()) {
        wprintf(L"Failed to obtain shutdown privileges\n");
        return;
    }
    HMODULE ntdll = GetModuleHandleA("ntdll.dll");
    if(!ntdll){
        wprintf(L"Failed Opening NTDLL\n");
        return;
    }
    PNtShutdownSystem NTShutdown = (PNtShutdownSystem)GetProcAddress(ntdll, "NtShutdownSystem");
    if(!NTShutdown){
        wprintf(L"Failed Extracting Function From NTDLL\n");
        return;
    }
    switch(type[1]){
        case L'r':
            NTSTATUS restartStatus = NTShutdown(1);
            if(!NT_SUCCESS(restartStatus)){
                wprintf(L"Failed Shutting Down Windows, Error Code %lx\n", restartStatus);
            }
            break;

        case L's':
            NTSTATUS shutdownStatus = NTShutdown(0);
            if(!NT_SUCCESS(shutdownStatus)){
                wprintf(L"Failed Shutting Down Windows, Error Code %lx\n", shutdownStatus);
            }
            break;
        case L'y':
            NTSTATUS recStatus = NTShutdown(3);
            if(!NT_SUCCESS(recStatus)){
                wprintf(L"Failed Shutting Down Windows, Error Code %lx\n", recStatus);
            }
            break;
        case L'?':
            wprintf(L"power [type] [isImmediate?]\ntype can be -r to restart, -s to shutdown.\nisImmediate can be 1 if true, else 0 or leave empty\n");
            break;
        case L'h':
            SetSuspendState(TRUE, TRUE, FALSE);
            break;
        case L'q':
            SetSuspendState(FALSE, FALSE, FALSE);
            break;
        default:
            wprintf(L"Incorrect Argument, Use -s to shutdown or -r to restart\n");
            break;
    }
    
}

VOID powerManagement(data* data){
    if(!data->arg){
        wprintf(L"power [type] [isImmediate?]\ntype can be -r to restart, -s to shutdown, -l to logoff, -h to hibernate, and -q to suspend the machine (if isImmediate isn't 1).\nisImmediate can be 1 if true, else 0 or empty\n");
        return;
    }
    WCHAR* token;
    WCHAR* type = wcstok(data->arg, L" ", &token);
    WCHAR* isImmediate = wcstok(NULL, L"\n", &token);
    if(!giveShutDownPerms()){
        return;
    }
    if(!type){
        wprintf(L"power [type] [isImmediate?]\ntype can be -r to restart, -s to shutdown, -l to logoff (if isImmediate isn't 1).\nisImmediate can be 1 if true, else 0 or empty\n");
    }
    if(isImmediate){
        forceShutdown(type, isImmediate);
        return;
    }
    
    switch(type[1]){
        case L'r':
            if(!ExitWindowsEx(EWX_REBOOT, SHTDN_REASON_MAJOR_SYSTEM)){
                wprintf(L"Cannot Restart Windows, Error Code %lu\n", GetLastError());
            }
            break;
        case L's':
            if(!ExitWindowsEx(EWX_SHUTDOWN, SHTDN_REASON_MAJOR_SYSTEM)){
                wprintf(L"Cannot Shutdown Windows, Error Code %lu\n", GetLastError());
            }
            break;
        case L'l':
            if(!ExitWindowsEx(EWX_RESTARTAPPS, SHTDN_REASON_MAJOR_SYSTEM)){
                wprintf(L"Cannot LogOff, Error Code %lu\n", GetLastError());
            }
            break;
        case L'?':
            wprintf(L"power [type] [isImmediate?]\ntype can be -r to restart, -s to shutdown, -l to logoff (if isImmediate isn't 1).\nisImmediate can be 1 if true, else 0 or empty\n");
            break;
        case L'h':
            SetSuspendState(TRUE, FALSE, FALSE);
            break;
        case L'q':
            SetSuspendState(FALSE, FALSE, FALSE);
            break;
        default:
            wprintf(L"Incorrect Argument, Use -s to shutdown or -r to restart\n");
            break;
    }
}