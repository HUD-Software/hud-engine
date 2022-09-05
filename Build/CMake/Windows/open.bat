@ECHO OFF

:: Print the help if requested
IF /I "%~1" EQU "-help" GOTO PRINT_HELP

:: ============================
::  Check [generator] parameter
:: ============================
IF /I "%~1" NEQ "Visual Studio 2019" (
IF /I "%~1" NEQ "Visual Studio 2022" (
ECHO. 
ECHO Error: [generator] is invalid : "%~1"
ECHO.
CALL:PRINT_HELP
EXIT 1
))
SET generator=%~1

:: ============================
::  Check [arch] parameter
:: ============================
IF /I "%~2" EQU "NMake" (
IF /I "%~2" NEQ "Win32" (
IF /I "%~2" NEQ "Win64" (
IF /I "%~2" NEQ "ARL" (
IF /I "%~2" NEQ "ARM64" (
ECHO.
ECHO Error: [arch] is invalid : "%~2"
ECHO.
CALL:PRINT_HELP
EXIT 1
)))))
SET arch=%~2

:: =============================
:: Check [toolset] parameter
:: =============================
IF /I "%~3" NEQ "V142" (
IF /I "%~3" NEQ "Clang" (
ECHO.
ECHO Error: [toolset] is invalid : "%~3"
ECHO.
CALL:PRINT_HELP
EXIT 1
))
set toolset=%~3

IF /I "%generator%" EQU "Visual Studio 2019" GOTO SETUP_VS_2019_ENV_VAR
IF /I "%generator%" EQU "Visual Studio 2022" GOTO SETUP_VS_2022_ENV_VAR
EXIT 1

:: ==========================
::  Setup Visual Studio 2019
:: ==========================
:SETUP_VS_2019_ENV_VAR
SET VSDEVENV="C:\Program Files (x86)\Microsoft Visual Studio\2019\Professional\Common7\IDE\devenv.exe"
IF EXIST %VSDEVENV% ( GOTO OPEN_VISUAL_STUDIO )
SET VSDEVENV="C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\IDE\devenv.exe"
IF EXIST %VSDEVENV% ( GOTO OPEN_VISUAL_STUDIO )
EXIT 1

:: ==========================
::  Setup Visual Studio 2022
:: ==========================
:SETUP_VS_2022_ENV_VAR
SET VSDEVENV="C:\Program Files\Microsoft Visual Studio\2022\Professional\Common7\IDE\devenv.exe"
IF EXIST %VSDEVENV% ( GOTO OPEN_VISUAL_STUDIO )
SET VSDEVENV="C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\IDE\devenv.exe"
IF EXIST %VSDEVENV% ( GOTO OPEN_VISUAL_STUDIO )
EXIT 1


:: ============================
:: Open Visual Studio solution
:: ============================
:OPEN_VISUAL_STUDIO
SET current_dir=%~dp0
CALL %current_dir%setup_build_env.bat "%generator%" "%arch%" "%toolset%"
IF ERRORLEVEL 1 EXIT /B %ERRORLEVEL%
START "" %VSDEVENV% "%build_dir%\HUDEngine.sln"
EXIT %ERRORLEVEL%

:: ================
::  Print the help
:: ================
:PRINT_HELP
ECHO.
ECHO Syntax: open.bat [generator] [arch] [toolset]
ECHO.
ECHO   [generator] The generator used to generate the project
ECHO     * Visual Studio 2019
ECHO     * Visual Studio 2022
ECHO.
ECHO   [arch] Set the architecture used to generate the project
ECHO     * Win32
ECHO     * Win64
ECHO     * ARM32
ECHO     * ARM64
ECHO.
ECHO   [toolset] Set the toolset used to generate the project
ECHO     * For Visual Studio 2019 and NMake Visual Studio 2019 generator
ECHO       * V142
ECHO       * Clang
ECHO.
EXIT 0
