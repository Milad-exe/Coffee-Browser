@echo off
setlocal

echo starting CMake...
echo.

rd /s /q .\build
mkdir build
cd .\build
cmake ..

endlocal
pause >nul

pause >nul