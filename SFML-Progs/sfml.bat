@echo off
rem Check if filename is provided
if "%1"=="" (
    echo Please provide the file name.
    exit /b
)

rem Replace %1 with the file name provided
g++ -c %1.cpp -IC:\SFML-Progs\SFML-2.5.1\SFML-2.5.1\include

rem Notify if successful or failed
if %errorlevel% equ 0 (
    echo Compilation successful.
) else (
    echo Compilation failed.
)

g++ %1.o -o %1 -LC:\SFML-Progs\SFML-2.5.1\SFML-2.5.1\lib -lsfml-graphics -lsfml-window -lsfml-system

rem Notify if successful or failed
if %errorlevel% equ 0 (
    echo Linking successful.
) else (
    echo Linking failed.
)