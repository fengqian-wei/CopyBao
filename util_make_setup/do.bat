@echo off
if "%1" == "" goto usage
echo Installation started.
ren %1\spice\spicec.exe _spicec.exe

echo Extracting files...
7za x -o%1 -y data.zip >NUL

echo Installation finished.
goto quit

:usage
echo usage: do.bat [XueBao dir]

:quit
if "%2" == "" pause