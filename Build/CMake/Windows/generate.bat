@ECHO OFF

:: ========================
::  Check CMake is install
:: ========================
where /q cmake
IF ERRORLEVEL 1 (
ECHO CMake not found
EXIT 1
)

IF /I "%~1" EQU "Visual Studio 2019" (
    CALL %~dp0generate_msvc.bat "%~1" "%~2" "%~3"
    EXIT /B %ERRORLEVEL% 
)
IF /I "%~1" EQU "Visual Studio 2022" (
    CALL %~dp0generate_msvc.bat "%~1" "%~2" "%~3"
    EXIT /B %ERRORLEVEL% 
)
IF /I "%~1" EQU "NMake Visual Studio 2019" (
    CALL %~dp0generate_nmake_makefile.bat "%~1" "%~2" "%~3" "%~4"
    EXIT /B %ERRORLEVEL%
)
IF /I "%~1" EQU "NMake Visual Studio 2022" (
    CALL %~dp0generate_nmake_makefile.bat "%~1" "%~2" "%~3" "%~4"
    EXIT /B %ERRORLEVEL%
)


:: ===================================
:: Error if not genertor are selected
:: ===================================
ECHO.
ECHO No generator specified. Generator should be :
ECHO     * Visual Studio 2019
ECHO     * Visual Studio 2022
ECHO     * NMake Visual Studio 2019
ECHO     * NMake Visual Studio 2022
ECHO.
EXIT /B 1
