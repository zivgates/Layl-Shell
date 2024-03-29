#include "headers/processconfig.h"
#include <tchar.h>
#include <psapi.h>
#include <winnt.h>




static inline VOID printProcess(DWORD processID, BOOL* isValid) {
    TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");

    HANDLE hProcess = OpenProcess(
        PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
        FALSE,
        processID
    );
    if (NULL != hProcess) {
        HMODULE hMods[BUFSIZE];
        DWORD cbNeeded;

        if (EnumProcessModules(hProcess, hMods, sizeof(hMods), &cbNeeded)) {
            GetModuleBaseName(hProcess, hMods[0], szProcessName, sizeof(szProcessName) / sizeof(TCHAR));
        }
    }

    if (_tcscmp(szProcessName, TEXT("<unknown>")) != 0) {
        _tprintf(TEXT(" - (Process %s [PID: %lu]) - \n"), szProcessName, processID);
        CloseHandle(hProcess);
        *isValid = TRUE;
        return;
    }
    CloseHandle(hProcess);
    isValid = FALSE;
}

static inline VOID listProcesses(){
    DWORD aProcesses[BUFSIZE], cbNeeded, cProcesses;
    if(!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded)){
        wprintf(L"Error Printing Processes\n");
        return;
    }
    cProcesses = cbNeeded / sizeof(DWORD);

    BOOL isValid = FALSE;

    for(unsigned int i = 0; i < cProcesses; i++){
        if(aProcesses[i] != 0){
            printProcess(aProcesses[i], &isValid);
            if(isValid && i % 5 == 0) wprintf(L"\n");
        }
    }
    return;
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
    wprintf(L"PROCESS COMMAND:\n");
    wprintf(L"process [command] (arguments (optional))\n");
    wprintf(L"commands can be -k (to kill processes), -l (to list processes), or -g (to get a pid of a window)\n\n");
    wprintf(L"----------------------------------------------------------------------------------------------------------\n");
    wprintf(L"-- For -k, you have to pass the PID of the process you want to kill into the argument                   --\n");
    wprintf(L"-- For -g, you have to pass the title-name of the window you want to get the pid from into the argument --\n");
    wprintf(L"-- For -l, no arguments are needed                                                                      --\n");
    wprintf(L"----------------------------------------------------------------------------------------------------------\n");
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
        printf("type 'process -?' to get how to use the command\n"); 
        return;
    }
    if(!type[1]){
        printf("type 'process -?' to get how to use the command\n"); 
        return;
    }
    switch(type[1]){
        case L'k':
            if(!arg){
                printf("No PID passed\n");
                return;
            }
            DWORD pid = wcstol(arg, &token, 10);
            killProcess(pid);
            break;
        case L'l':
            listProcesses();
            break;
        case L'g':
            if(!arg){
                printf("No Window Name passed\n");
                return;
            }
            getPid(arg);
            break;
        case L'?':
            printHelp();
            break;
        default:
            printf("%c isn't a valid argument\ntype 'process -?' to get how to use the command\n", type[1]);
            break;
    }

}