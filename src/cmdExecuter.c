#include "headers/cmdExecuter.h"
#include "headers/misc.h"
#include "headers/lylapi.h"
#include "headers/fileio.h"
#include "headers/dirio.h"
#include "headers/startProcess.h"
#include "headers/processConfig.h"





VOID cmdExecuter(data* data){
    switch(data->currentCmd){
        case 0:
            wprintf(L"%s\n", data->arg);
            break;
        case 1:
            if(data->isDebug == TRUE) crash();
            else wprintf(L"Start Debug Mode To Crash The Shell\n");
            break;
        case 2:
            lylapi(data);
            break;
        case 3:
            createFile(data);
            break;
        case 4:
            deleteFile(data);
            break;
        case 5:
            copyFile(data);
            break;
        case 6:
            readFile(data);
            break;
        case 7:
            writeFile(data);
            break;
        case 8:
            writeFileNoReset(data);
            break;
        case 9:
            help();
            break;
        case 10:
            moveDirectory(data);
            break;
        case 11:
            if(!data->arg){
                wprintf(L"usage: wait [ms], pauses the shell for specifc ms\n");
                return;
            }
            Sleep(wcstol(data->arg, NULL, 0));
            break;
        case 12:
            pause();
            break;
        case 13:
            createDirectory(data);
            break;
        case 14:
            deleteDirectory(data);
            break;
        case 15:
            printDirectory(data);
            break;
        case 16:
            printCurrentDirectory();
            break;
        case 17:
            startProcess(data);
            break;
        case 18:
            processConfigurer(data);
            break;
        default:
            wprintf(L"%s is the incorrect command!\n", data->cmd);
            break;
    }
}