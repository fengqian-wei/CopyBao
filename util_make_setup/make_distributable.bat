@echo off
if not exist CopyBao.zip goto fresh
echo Removing last build...
del CopyBao.zip
:fresh
if exist data.zip goto data_exists
echo Making data.zip...
call make_data.bat
:data_exists
mkdir CopyBao
echo Copying files...
copy installer.exe CopyBao\setup.exe >NUL
copy *do.bat CopyBao\ >NUL
copy data.zip CopyBao\ >NUL
copy 7za.exe CopyBao\ >NUL
copy readme.txt CopyBao\ >NUL
echo Making target archive...
7za a CopyBao.zip CopyBao >NUL
echo Deleting temporary files...
rd /s /q CopyBao
echo Finished.
pause
