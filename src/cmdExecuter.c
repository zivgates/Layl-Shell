#include "headers/cmdExecuter.h"
#include "headers/misc.h"


VOID cmdExecuter(data* data){
    switch(data->currentCmd){
        case 0:
            wprintf(L"%s\n", data->arg);
            break;
        case 1:
            crash();
            break;
    }
}