echo off
windres ../resources/resource.rc -o ../resources/resource.o
gcc -Wall ../source/main.c ../source/windowsFunction.c ../source/utilities.c ../source/calculator.c -lgdi32 ../resources/resource.o  -o Calculator.exe 
rm ../resources/resource.o

