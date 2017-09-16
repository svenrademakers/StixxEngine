@echo off
if exist ..\build_vs ( 
	del /Q ..\build_vs
) else (
	mkdir ..\build_vs    
)

chdir ..\build_vs
cmake ..\stixx -G "Visual Studio 15 2017 Win64" -DCMAKE_INSTALL_PREFIX=./
pause