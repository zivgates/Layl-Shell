#include "headers/cmdChecker.h"
#include "headers/cmdExecuter.h"
#include "headers/fallback.h"


WCHAR* cmds[] = {L"echo", L"crash"};



static LONG WINAPI failureHandler(struct _EXCEPTION_POINTERS* exceptionInfo){
    startRecovery(exceptionInfo);
    return 0;
}

static DWORD WINAPI cmdRunning(LPVOID param){
    SetUnhandledExceptionFilter(failureHandler);
    data* dta = (data*)param;
    cmdExecuter(dta);
    ExitThread(0);
    return 0;
}


VOID cmdChecker(data* data){
    int cmdsize = sizeof(cmds)/sizeof(cmds[0]);
    for(int i = 0; i < cmdsize; i++){
        if(wcscmp(data->cmd, cmds[i]) == 0){
            data->currentCmd = i;
            HANDLE hThread = CreateThread(NULL, 0, cmdRunning, (LPVOID)data, 0, NULL);
            WaitForSingleObject(hThread, INFINITE);
            return;
        }
    }
    wprintf(L"%s isn't a valid command\n", data->cmd);
}