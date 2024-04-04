#include "headers/lylapi.h"
#include "headers/tools.h"



VOID lylapi(data* data){
    if(!data->arg) return;
    data->arg = toLowerCase(data->arg);
    if(wcscmp(data->arg, L"startdebugmode") == 0){
        data->isDebug = TRUE;
        debugPrint(data, L"[+] Started Debug Mode\n");
        return;
    } 
    if(wcscmp(data->arg, L"exitdebugmode") == 0){
        data->isDebug = FALSE;
        debugPrint(data, L"[+] Exited Debug Mode\n");
        return;
    } 
    
}