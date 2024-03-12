#include "headers/freader.h"
#include "headers/cli.h"





int wmain(int argc, WCHAR* argv[]){
    if(argc < 2){
        WCHAR begin[BUFSIZE]; 
        swprintf(begin, BUFSIZE, 
                       L"-------------------------------------------\n"
                               "| Layl Shell Version %.1f                  |\n"
                               "| Copyright \"zvqle\", All Rights Reserved  |\n"
                               "-------------------------------------------\n\n\n", VER);
        wprintf(L"%s\n", begin);
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