#include "headers/reg.h"
#include "headers/tools.h"




static inline DWORD convertRegType(WCHAR* dwtype) {
    dwtype = toLowerCase(dwtype);
    if (wcscmp(dwtype, L"dword") == 0) {
        return REG_DWORD;
    }
    else if (wcscmp(dwtype, L"sz") == 0) {
        return REG_SZ;
    }
    else if (wcscmp(dwtype, L"expand_sz") == 0) {
        return REG_EXPAND_SZ;
    }
    else{
        wprintf(L"Type Can be a dword, sz, or expand_sz\nDEFAULT: setting as sz...\n");
        return REG_SZ;
    }

}

static inline BOOL createReg(WCHAR* hkey, WCHAR* regpath){
    HKEY key;
    HKEY closing;
    if(wcscmp(hkey, L"HKLM") == 0){
        key = HKEY_LOCAL_MACHINE;
    }
    else if(wcscmp(hkey, L"HKCR") == 0){
        key = HKEY_CLASSES_ROOT;
    }
    else if(wcscmp(hkey, L"HKCU") == 0){
        key = HKEY_CURRENT_USER;
    }
    else if(wcscmp(hkey, L"HKU") == 0){
        key = HKEY_USERS;
    }
    else if(wcscmp(hkey, L"HKCC") == 0){
        key = HKEY_CURRENT_CONFIG;
    }
    else{
        wprintf(L"Invalid Registry Key, hkey can be HKCR, HKCU, HKLM, HKU, or HKCC\n");
        return FALSE;
    }

    LSTATUS checkResult = RegOpenKeyExW(
        key,
        regpath,
        0,
        KEY_READ,
        &closing
    );
    if (checkResult == ERROR_SUCCESS) {
        wprintf(L"Registry key already exists: %s\\%s\n", hkey, regpath);
        RegCloseKey(closing);
        return FALSE;
    }

    LSTATUS result = RegCreateKeyW(
        key,
        regpath,
        &closing
    );
    if(result == ERROR_SUCCESS){
        RegCloseKey(closing);
        return TRUE;
    }
    else{
        RegCloseKey(closing);
        wprintf(L"Can't Create Key, Error Code %lu\n", (DWORD)result);
        return TRUE;
    }


}

static inline BOOL deleteReg(WCHAR* hkey, WCHAR* regpath){
    HKEY key;
    HKEY closing;
    if(wcscmp(hkey, L"HKLM") == 0){
        key = HKEY_LOCAL_MACHINE;
    }
    else if(wcscmp(hkey, L"HKCR") == 0){
        key = HKEY_CLASSES_ROOT;
    }
    else if(wcscmp(hkey, L"HKCU") == 0){
        key = HKEY_CURRENT_USER;
    }
    else if(wcscmp(hkey, L"HKU") == 0){
        key = HKEY_USERS;
    }
    else if(wcscmp(hkey, L"HKCC") == 0){
        key = HKEY_CURRENT_CONFIG;
    }
    else{
        wprintf(L"Invalid Registry Key, hkey can be HKCR, HKCU, HKLM, HKU, or HKCC\n");
        return FALSE;
    }

    LSTATUS checkResult = RegOpenKeyExW(
        key,
        regpath,
        0,
        KEY_SET_VALUE,
        &closing
    );

    if (checkResult != ERROR_SUCCESS) {
        wprintf(L"Cannot Open Key: %s\\%s, Error Code %ld\n", hkey, regpath, checkResult);
        RegCloseKey(closing);
        return FALSE;
    }
    LSTATUS result = RegDeleteKeyW(
        key,
        regpath
    );
    if (result != ERROR_SUCCESS) {
        wprintf(L"Cannot Delete Key: %s\\%s, Error Code %ld\n", hkey, regpath, result);
        RegCloseKey(closing);
        return FALSE;
    }
    return TRUE;


}

static inline BOOL writeReg(WCHAR* hkey, WCHAR* regpath) {
    WCHAR* token;
    HKEY key;
    HKEY closing;
    if (wcscmp(hkey, L"HKLM") == 0) {
        key = HKEY_LOCAL_MACHINE;
    } else if (wcscmp(hkey, L"HKCR") == 0) {
        key = HKEY_CLASSES_ROOT;
    } else if (wcscmp(hkey, L"HKCU") == 0) {
        key = HKEY_CURRENT_USER;
    } else if (wcscmp(hkey, L"HKU") == 0) {
        key = HKEY_USERS;
    } else if (wcscmp(hkey, L"HKCC") == 0) {
        key = HKEY_CURRENT_CONFIG;
    } else {
        wprintf(L"Invalid Registry Key, hkey can be HKCR, HKCU, HKLM, HKU, or HKCC\n");
        return FALSE;
    }
    WCHAR* keypath = wcstok(regpath, L" ", &token);
    WCHAR* valuename = wcstok(NULL, L" ", &token);
    WCHAR* dwtype = wcstok(NULL, L" ", &token);
    WCHAR* lpdata = wcstok(NULL, L" \n", &token);

    if (!valuename || !dwtype) {
        wprintf(L"reg -w takes two extra parameters, the name of the value and what type of data\n");
        return FALSE;
    }

    DWORD cbdata;
    if (!lpdata) {
        cbdata = 0;
    } else {
        cbdata = wcslen(lpdata);
    }
    LSTATUS checkResult = RegOpenKeyExW(
        key,
        keypath,
        0,
        KEY_SET_VALUE,
        &closing
    );

    if (checkResult != ERROR_SUCCESS) {
        wprintf(L"Cannot Open Key: %s\\%s, Error Code %ld\n", hkey, keypath, checkResult);
        RegCloseKey(closing);
        return FALSE;
    }
    // THIS HAS NO SUPPORT IN XP, But it works well
    // LSTATUS result = RegSetKeyValueA(
    //     closing,
    //     NULL,
    //     valuename,
    //     convertRegType(dwtype),
    //     lpdata,
    //     cbdata
    // );
    LSTATUS result = RegSetValueExW(
        closing,
        valuename,
        0,
        convertRegType(dwtype),
        (const BYTE *)lpdata,
        cbdata
    );



    if (result != ERROR_SUCCESS) {
        wprintf(L"Cannot Set Key: %s\\%s, Error Code %ld\n", hkey, keypath, result);
        RegCloseKey(closing);
        return FALSE;
    }

    RegCloseKey(closing);
    return TRUE;
}

VOID editReg(data *data){
    WCHAR* token;
    if(!checkAdmin()){
        wprintf(L"Please Run Layl As An Administrator To Use the reg Command!\n");
        return;
    }
    if(!data->arg){
        wprintf(L"reg [dowhat] [hkey] [regpath] {valuename} (only for -w) {datatype} (only for -w)\ndowhat path can be -c to create a reg, -d to delete, and -w to write\nhkey can be HKCR, HKCU, HKLM, HKU, or HKCC\npath is the path to the registry key\n");
        return;
    }
    WCHAR* dowhat = wcstok(data->arg, L" ", &token);
    WCHAR* hkey = wcstok(NULL, L" ", &token);
    WCHAR* regpath = wcstok(NULL, L"\n", &token);

    if(!dowhat || !hkey || !regpath){
        wprintf(L"reg [dowhat] [hkey] [regpath]\ndowhat path can be -c to create a reg, -d to delete, and -w to write\nhkey can be HKCR, HKCU, HKLM, HKU, or HKCC\npath is the path to the registry key\n");
        return;
    }
    if(wcscmp(dowhat, L"-c") == 0){
        if(!createReg(hkey, regpath)){
            wprintf(L"Error Creating Registry Key!\n");
            return;
        }
        wprintf(L"Succsessfully Created %s\\%s\n", hkey, regpath);
        return;
    }
    else if(wcscmp(dowhat, L"-d") == 0){
        if(!deleteReg(hkey, regpath)){
            wprintf(L"Error Deleting Registry Key!\n");
            return;
        }
        wprintf(L"Succsessfully Deleted %s\\%s\n", hkey, regpath);
        return;
    }
    else if(wcscmp(dowhat, L"-w") == 0){
        if(!writeReg(hkey, regpath)){
            wprintf(L"Error Writing Into Registry Key!\n");
            return;
        }
        wprintf(L"Succsessfully Written Into %s\\%s\n", hkey, regpath);
        return;
    }
    else{
        wprintf(L"%s is an invalid argument, use either -c to create, -d to delete, or -w to write\n", hkey);
        return;
    }
}
