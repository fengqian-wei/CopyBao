@echo off
if "%1" == "" goto usage
echo Un-installation started.

echo Deleting files...
rd /s /q %1\spicy
del %1\spice\spicec.exe
ren %1\spice\_spicec.exe spicec.exe

echo Un-installation finished.
goto quit

:usage
echo usage: uodo.bat [XueBao dir]

:quit
if "%2" == "" pause