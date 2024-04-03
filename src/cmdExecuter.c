#include "headers/cmdExecuter.h"
#include "headers/misc.h"
#include "headers/lylapi.h"
#include "headers/fileio.h"
#include "headers/dirio.h"
#include "headers/startProcess.h"
#include "headers/processConfig.h"
#include "headers/power.h"
#include "headers/reg.h"
#include "headers/driveMgmt.h"
#include "headers/freader.h"
#include "headers/color.h"



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
        case 19:
            powerManagement(data);
            break;
        case 20:
            editReg(data);
            break;
        case 21:
            wprintf(L"Layl-Shell Build %0.3f\n", VER);
            break;
        case 22:
            WCHAR buffer[BUFSIZE];
            swprintf(buffer, BUFSIZE, L"Layl Shell\nBuild %0.3f\nCopyright \"zvqle\", All Rights Reserved", VER);
            MessageBoxW(NULL, buffer, L"About Layl-Shell", MB_OK);
            break;
        case 23:
            getDriveInfo(data);
            break;
        case 24:
            break;
        case 25:
            if(!data->arg) return; 
            fileInfo info;
            info.fileName = data->arg;
            startReader(&info);
            break;
        case 26:
            if(data->path) free(data->path);
            wprintf(L"Exiting...\n");
            Sleep(2000);
            ExitProcess(0);
            break;
        case 27:
            clrscr();
            break;
        case 28:
            changeBackGroundConsoleColor(data);
            break;
        case 29:
            changeConsoleColor(data);
            break;
        default:
            wprintf(L"%s is the incorrect command!\n", data->cmd);
            break;
    }
}