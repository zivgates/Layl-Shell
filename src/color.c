#include "headers/color.h"





VOID changeBackGroundConsoleColor(data *data){
    WORD color = 0;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
    GetConsoleScreenBufferInfo(hConsole, &bufferInfo);
    if(!data->arg) {
        wprintf(L"bcolor [color] - changes background color to that specifc color code\n\nCOLORS: RED, GREEN, BLUE, GRAY, WHITE, NORMAL\n");
        return;
    }
    if(wcscmp(data->arg, L"red") == 0){
        color = BACKGROUND_RED;
        SetConsoleTextAttribute(hConsole, color); 
    } 
    else if(wcscmp(data->arg, L"green")== 0){
        color = BACKGROUND_GREEN;
        SetConsoleTextAttribute(hConsole, color);
    } 
    else if(wcscmp(data->arg, L"blue") == 0){
        color = BACKGROUND_BLUE;
        SetConsoleTextAttribute(hConsole, color);
    } 
    else if(wcscmp(data->arg, L"gray") == 0){
        color = BACKGROUND_INTENSITY;
        SetConsoleTextAttribute(hConsole, color);
    } 
    else if(wcscmp(data->arg, L"white") == 0){
        color = BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN;
        SetConsoleTextAttribute(hConsole, color);
    } 
    
    else if(wcscmp(data->arg, L"normal") == 0 ){
        WORD newAttributes = bufferInfo.wAttributes & ~(BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
        newAttributes &= ~FOREGROUND_INTENSITY;
        SetConsoleTextAttribute(hConsole, newAttributes);
        color = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN;
        SetConsoleTextAttribute(hConsole, color);
    }

    else {
        wprintf(L"bcolor *color - changes background color to that specifc color code\n\nCOLORS: RED, GREEN, BLUE, GRAY, WHITE, NORMAL\n");
        return;
    }
    
    return;
}

VOID changeConsoleColor(data* data){
    WORD color = 0;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if(!data->arg){
        wprintf(L"color *color - changes color to that specifc color code\n\nCOLORS: RED, GREEN, BLUE, GRAY, WHITE, NORMAL\n");
        return;
    }
    if(wcscmp(data->arg, L"red") == 0){
        color = FOREGROUND_RED;
        SetConsoleTextAttribute(hConsole, color);
    } 
    else if(wcscmp(data->arg, L"green")== 0){
        color = FOREGROUND_GREEN;
        SetConsoleTextAttribute(hConsole, color);
    } 
    else if(wcscmp(data->arg, L"blue") == 0){
        color = FOREGROUND_BLUE;
        SetConsoleTextAttribute(hConsole, color);
    } 
    else if(wcscmp(data->arg, L"gray") == 0){
        color = FOREGROUND_INTENSITY;
        SetConsoleTextAttribute(hConsole, color);
    } 
    else if(wcscmp(data->arg, L"white") == 0 ||wcscmp(data->arg, L"normal") == 0 ){
        color = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN;
        SetConsoleTextAttribute(hConsole, color);
    }
    else{
        wprintf(L"color *color - changes color to that specifc color code\n\nCOLORS: RED, GREEN, BLUE, GRAY, WHITE, NORMAL\n");
        return;
    }

    return;
}