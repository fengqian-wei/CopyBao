@echo off
if "%1" == "" goto usage
echo Re-installation started.

echo Do Un-installation...
call undo.bat %1 nopause
echo Do Installation...
call do.bat %1 nopause

echo Re-installation finished.
goto quit

:usage
echo usage: redo.bat [XueBao dir]

:quit
pause