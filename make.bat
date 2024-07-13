@echo off

rc resources/resource.rc
cl /Os /GL /arch:AVX2 src/*.c resources/resource.res DbgHelp.lib Shell32.lib User32.lib ntdll.lib Advapi32.lib PowrProf.lib Lz32.lib /Fe:layl.exe
strip layl.exe
del *.obj
start layl.exe
