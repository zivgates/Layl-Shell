#include "headers/driveMgmt.h"
#include "headers/tools.h"





VOID getDriveInfo(data* data){
    if(!data->arg){
        wprintf(L"driveinfo [drive], drive is the drive name (C: or D:), gives drive info\n");
        return;
    }
    ULARGE_INTEGER spaceGivenForProgram;
    ULARGE_INTEGER totalSizeOfVolume;
    ULARGE_INTEGER freeSpaceOfDrive;
    BOOL result = SHGetDiskFreeSpaceExW(data->arg, &spaceGivenForProgram, &totalSizeOfVolume, &freeSpaceOfDrive);
    if(!result){
        GetErrorMessage(GetLastError());
        return;
    }
    WCHAR buffer[BUFSIZE]; 
    swprintf(buffer, BUFSIZE, 
        L"Drive Name %s\nTotal Space For Drive %lldGB (in bytes %lld)\n"
        "Free Space %lldGB (in bytes %lld)\n"
        "Used Space %lldGB (in bytes %lld)\n", 
        data->arg, totalSizeOfVolume.QuadPart / 1000000000, totalSizeOfVolume.QuadPart, freeSpaceOfDrive.QuadPart / 1000000000, freeSpaceOfDrive.QuadPart, (totalSizeOfVolume.QuadPart - freeSpaceOfDrive.QuadPart) / 1000000000
        , totalSizeOfVolume.QuadPart - freeSpaceOfDrive.QuadPart
    );
    wprintf(L"%s\n", buffer);
}