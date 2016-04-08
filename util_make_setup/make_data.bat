@echo off
if exist data.zip del data.zip
mkdir spice
copy switcher.exe spice\spicec.exe >NUL
7za a data.zip spice spicy >NUL
rd /s /q spice
