#include "headers/processconfig.h"
#include <tchar.h>
#include <psapi.h>
#include <winnt.h>
#include "headers/tools.h"
#include <winternl.h>



VOID suspend_process(WCHAR* pidstring){
    wprintf(L"ZivGates Suspender\n" 
                   "Copyright ZivGates, All Rights Reserved\n\n");
    if(!pidstring){
        wprintf(L"usage: process -w [pid]\n");
        return;
    }
    INT pid = _wtoi(pidstring);
    if(!pid){
        wprintf(L"pid must be an integer\n");
        return;
    }

    HANDLE process = OpenProcess(PROCESS_ALL_ACCESS , FALSE, pid);
    if(process == NULL){
        GetErrorMessage(GetLastError());
        
        return;
    }
    NTSTATUS status = NtSuspendProcess(process);
    if(!NT_SUCCESS(status)){
        wprintf(L"NtSuspendProcess failed with NTSTATUS 0x%lx", status);
        CloseHandle(process);
        return;
    }
    wprintf(L"[!] Press W to unsuspend the process with PID %d\n", pid);
    while(1){
        Sleep(10);
        if(GetAsyncKeyState('W') & 0x8000){
            NTSTATUS status = NtResumeProcess(process);
            if(!NT_SUCCESS(status)){
                wprintf(L"NtResumeProcess failed with NTSTATUS 0x%lx", status);
                CloseHandle(process);
                return;
            }
            CloseHandle(process);
            break;
        }
    }
}

static inline VOID getPid(WCHAR* windowName){
    DWORD pidnum;
    HWND hwnd = FindWindowW(NULL, windowName);
    if (hwnd == NULL) {
        if(GetLastError() == 2){
            wprintf(L"Couldn't Find Window\n");
        }
        else if(GetLastError() == 5){
            wprintf(L"Access is Denied\n");
        }
        else if(GetLastError() == 87){
            wprintf(L"Incorrect Parameter\n");
        }
        else
        {
            wprintf(L"Failed Getting Handle To Window %s!\nCheck If You Have The Permissions To Run It!\nOr If It Exists!\n", windowName);
        }
        
        return;
    }

    GetWindowThreadProcessId(hwnd, &pidnum);

    wprintf(L"ProcessID of %s Window Process is %lu\n", windowName, pidnum);
}


static inline VOID killProcess(DWORD pidnum){
    if(!pidnum){
        wprintf(L"Please Enter A Valid PID!\n");
        return;
    }
    HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, pidnum);
    if(!hProcess){
        if(GetLastError() == 2){
            wprintf(L"Process Couldn't Be Found\n");
        }
        else if(GetLastError() == 5){
            wprintf(L"Access is Denied\n");
        }
        else if(GetLastError() == 87){
            wprintf(L"Incorrect Parameter\n");
        }
        else
        {
            wprintf(L"Failed Getting Killing Process with PID of %lu! Error Code: %lu\n", pidnum, GetLastError());
        }
        return;
    }
    BOOL sucsess = TerminateProcess(hProcess, -2);

    if(!sucsess){
        wprintf(L"Failed Killing Process %lu\n", pidnum);
        return;
    }
    wprintf(L"Killed Process %lu!\n", pidnum);

    CloseHandle(hProcess);
}

static inline VOID printHelp(){
    wprintf(L"PROCESS COMMAND:\n"
    L"process [command] (arguments (optional))\n"
    L"commands can be -k (to kill processes), -l (to list processes), or -g (to get a pid of a window)\n\n"
    L"----------------------------------------------------------------------------------------------------------\n"
    L"-- For -k, you have to pass the PID of the process you want to kill into the argument                   --\n"
    L"-- For -g, you have to pass the title-name of the window you want to get the pid from into the argument --\n"
    L"-- For -s, you need to pass the PID of the process you want to suspend                                  --\n"
    L"----------------------------------------------------------------------------------------------------------\n");
}

VOID processConfigurer(data* data){
    if(!data->arg){ 
        printHelp();
        return;
    }
    WCHAR* token;
    WCHAR* type = wcstok(data->arg, L" ", &token);
    WCHAR* arg = wcstok(NULL, L"\n", &token);
    if(!type){
        wprintf(L"type 'process -?' to get how to use the command\n"); 
        return;
    }
    if(!type[1]){
        wprintf(L"type 'process -?' to get how to use the command\n"); 
        return;
    }
    switch(type[1]){
        case L'k':
            if(!arg){
                wprintf(L"No PID passed\n");
                return;
            }
            DWORD pid = wcstol(arg, &token, 10);
            killProcess(pid);
            break;
        case L'g':
            if(!arg){
                wprintf(L"No Window Name passed\n");
                return;
            }
            getPid(arg);
            break;
        case L's':
            suspend_process(arg);
            break;
        case L'?':
            printHelp();
            break;
        default:
            wprintf(L"%c isn't a valid argument\ntype 'process -?' to get how to use the command\n", type[1]);
            break;
    }
}