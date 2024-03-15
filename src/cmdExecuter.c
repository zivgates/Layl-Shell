#include "headers/cmdExecuter.h"
#include "headers/misc.h"
#include "headers/lylapi.h"
#include "headers/fileio.h"



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
        

    }
}