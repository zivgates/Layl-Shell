#include "headers/cmdChecker.h"
#include "headers/cmdExecuter.h"
#include "headers/fallback.h"
#include "headers/tools.h"


WCHAR* cmds[] = {L"echo", L"crash", L"lylapi", L"fcreate", L"fdelete", L"fcopy"};



static LONG WINAPI failureHandler(struct _EXCEPTION_POINTERS* exceptionInfo){
    startRecovery(exceptionInfo);
    return 0;
}

static DWORD WINAPI cmdRunning(LPVOID param){
    SetUnhandledExceptionFilter(failureHandler);
    data* dta = (data*)param;
    debugPrint(dta, L"Started A New Thread\n");
    cmdExecuter(dta);
    debugPrint(dta, L"Exiting  Thread\n");
    ExitThread(0);
    return 0;
}


VOID cmdChecker(data* data){
    if(!data->cmd) return;
    data->cmd = toLowerCase(data->cmd);
    int cmdsize = sizeof(cmds)/sizeof(cmds[0]);
    for(int i = 0; i < cmdsize; i++){
        debugPrint(data, L"Current Iteration Is %d\n", i);
        if(wcscmp(data->cmd, cmds[i]) == 0){
            data->currentCmd = i;
            HANDLE hThread = CreateThread(NULL, 0, cmdRunning, (LPVOID)data, 0, NULL);
            WaitForSingleObject(hThread, INFINITE);
            return;
        }
    }
    wprintf(L"%s isn't a valid command\n", data->cmd);
}