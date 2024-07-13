#include "headers/cmdChecker.h"
#include "headers/cmdExecuter.h"
#include "headers/fallback.h"
#include "headers/tools.h"
#include "headers/startProcess.h"
#include <handleapi.h>
#include <processthreadsapi.h>
//#include <signal.h>


WCHAR* cmds[] = {L"echo", L"crash", L"lylapi", L"fcreate", L"fdelete", L"fcopy",
                 L"fread", L"fwrite", L"fprint", L"help", L"moveto", L"wait", 
                 L"pause", L"dcreate", L"ddelete", L"pd", L"cd", L"start",
                 L"process", L"power", L"reg", L"ver", L"about", L"driveinfo",
                 L"-", L"run", L"exit", L"cls", L"bcolor", L"color",
                 L"system", L"changetitlebar", L"memleak", L"lywrite"};



static inline LONG WINAPI failureHandler(struct _EXCEPTION_POINTERS* exceptionInfo){
    startRecovery(exceptionInfo);
    return 0;
}

void ctrlc(int signal){
    ExitThread(0);
}

void returnToPrompt(){

    ExitThread(0);
}
static DWORD WINAPI cmdRunning(LPVOID param){
    SetUnhandledExceptionFilter(failureHandler);
    //signal(SIGINT, ctrlc);   
    data* dta = (data*)param;
    debugPrint(dta, L"Started A New Thread\n");
    cmdExecuter(dta);
    debugPrint(dta, L"Exiting  Thread\n");
    ExitThread(0);
    return 0;
}


VOID cmdChecker(data* data){
    if(!data->cmd) return;
    if(data->cmd[0] == L',' && data->cmd[0] == L','){
        quickStartProcess(data);
        return;
    } 
    else if(data->cmd[0] == L'>' && data->cmd[0] == L'>'){
        quickStartProcessinNewWindow(data);
        return;
    } 
RETURN:
    data->cmd = toLowerCase(data->cmd);
    int cmdsize = sizeof(cmds)/sizeof(cmds[0]);
    for(int i = 0; i < cmdsize; i++){
        debugPrint(data, L"Current Iteration Is %d\n", i);
        if(wcscmp(data->cmd, cmds[i]) == 0){
            data->currentCmd = i;
            HANDLE hThread = CreateThread(NULL, 0, cmdRunning, (LPVOID)data, 0, NULL);
            WaitForSingleObject(hThread, INFINITE);
            CloseHandle(hThread);
            return;
        }
    }
    INT result = createProcess(data->cmd, data->arg);
    if(result == 1){
        wprintf(L"%s isn't a valid command\n", data->cmd);
    }
}