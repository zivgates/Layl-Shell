@echo off

windres resources/resource.rc -O coff -o resources/res.o
cl /Os /GL /arch:AVX2 src/*.c resources/res.o DbgHelp.lib Shell32.lib User32.lib Advapi32.lib PowrProf.lib /Fe:layl.exe
strip layl.exe
del *.obj
start layl.exe
