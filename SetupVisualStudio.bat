@echo off
if exist ..\build_vs ( 
	del /Q ..\build_vs
) else (
	mkdir ..\build_vs    
)

chdir ..\build_vs
cmake ..\stixx
pause