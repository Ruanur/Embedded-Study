#include <stdio.h>
#include "sensor.h"

int main()
{
    int Temperature = GetTemperature();
    printf("Temperature: %d\n", Temperature);
    return 0;
}

/*
    cmd /c chcp 65001>nul && C:\msys64\ucrt64\bin\gcc.exe 
    -fdiagnostics-color=always -g 
    "C:\Develop Environment\Embedded-Study\01_C_Basic\11.Function_Header\main.c" 
    -o "C:\Develop Environment\Embedded-Study\01_C_Basic\11.Function_Header\main.exe"
    C:/msys64/ucrt64/bin/../lib/gcc/x86_64-w64-mingw32/16.2.0/../../../../x86_64-w64-mingw32/bin/ld.exe: 
    C:\Users\mkj46\AppData\Local\Temp\ccrYUYjh.o: in function `main':
*/
