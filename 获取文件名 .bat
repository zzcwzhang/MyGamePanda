echo off
for /r %%a in (*.cpp) do echo ../../Classes/%%~nxa\>> 包名.txt
for /r "\XAnimation" in (*.cpp) do echo Classes/XAnimation/%%~nxa\>> 包名.txt
pause