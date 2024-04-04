#include "headers/freader.h"
#include "headers/cli.h"
#include "headers/tools.h"



int wmain(int argc, WCHAR* argv[]){
    SetConsoleTitleW(L"Layl-Shell");
    if(argc < 2){
        WCHAR begin[BUFSIZE]; 
        if(checkIfFileExist(L"C:\\ProgramData\\init.lys")){
            fileInfo info;
            info.fileName = L"C:\\ProgramData\\init.lys";
            startReader(&info);
        }
        else if(checkIfFileExist(L"init.lys")){
            fileInfo info;
            info.fileName = L"init.lys";
            startReader(&info);
        }
        else{
            swprintf(begin, BUFSIZE, 
                       L"-------------------------------------------\n"
                               "| Layl Shell Version %.1f                  |\n"
                               "| Copyright \"zvqle\", All Rights Reserved  |\n"
                               "-------------------------------------------\n\n", VER);
            wprintf(L"%s\n", begin);
        }
        cliInfo info;
        startCli(&info);
        return 1;
    }
    else{
        fileInfo info;
        info.fileName = argv[1];
        startReader(&info);
    }
    return 0;
}