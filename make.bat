@echo off

windres resources/resource.rc -O coff -o resources/res.o
cl /Os /GL /arch:AVX2 src/*.c resources/res.o DbgHelp.lib /Fe:layl.exe
strip layl.exe
del *.obj
start layl.exe
