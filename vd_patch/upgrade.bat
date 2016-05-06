@echo off
set target=C:\Program Files\SaiwayGuestAgent\vdagent

copy /y "%target%\vdagent.exe" vdagent0.exe
copy /y "%target%\vdservice.exe" vdservice0.exe

bspatch vdagent0.exe vdagent.exe vdagent.diff
bspatch vdservice0.exe vdservice.exe vdservice.diff

:retry
taskkill /f /im vdservice.exe /im vdagent.exe
del "%target%\vdagent.exe" "%target%\vdservice.exe" 2>NUL
if exist "%target%\vdagent.exe" goto retry
if exist "%target%\vdservice.exe" goto retry

copy /y vdagent.exe "%target%\"
copy /y vdservice.exe "%target%\"

del vdagent.exe vdservice.exe

"%target%\vdservice.exe" uninstall
"%target%\vdservice.exe" install

net start vdservice

pause
