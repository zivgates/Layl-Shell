#include "headers/freader.h"
#include "headers/cli.h"





int wmain(int argc, WCHAR* argv[]){
    if(argc < 2){
        wprintf(L"  -------------------------------------------\n");
        wprintf(L"  | Layl Shell Version %0.1f                  |\n", VER);
        wprintf(L"  | Copyright \"zvqle\", All Rights Reserved  |\n", VER);
        wprintf(L"  -------------------------------------------\n\n\n");
        cliInfo info;
        startCli(&info);
        return 1;
    }
    else{
        fileInfo info;
        info.fileName = argv[1];
        readFile(&info);
    }
    return 0;
}