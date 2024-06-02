#ifndef FILEIO_H_INCLUDED
#define FILEIO_H_INCLUDED

#include "main.h"

BOOL createFile(data* data);
BOOL deleteFile(data* data);
BOOL copyFile(data* data);
BOOL readFile(data* data);
BOOL writeFile(data* data);
VOID lywrite(data* data);

#endif