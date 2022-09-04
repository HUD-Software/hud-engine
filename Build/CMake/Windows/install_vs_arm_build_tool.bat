@ECHO OFF
:: Print the help if requested
IF /I "%~1" EQU "-help" GOTO PRINT_HELP

:: =======================
::  Check input parameter
:: =======================
IF /I "%~1" NEQ "Visual Studio 2019" (
IF /I "%~1" NEQ "Visual Studio 2022" (
IF /I "%~1%" NEQ "NMake Visual Studio 2019" (
IF /I "%~1%" NEQ "NMake Visual Studio 2022" (
ECHO. 
ECHO Error: [visual_studio] is invalid : "%~1"
ECHO.
CALL:PRINT_HELP
EXIT /B 1
)))) 
SET visual_studio=%~1


:SETUP_VS_2019_ENV_VAR
SET VS_SETUP_EXE="C:\Program Files (x86)\Microsoft Visual Studio\Installer\setup.exe"
SET VS_INSTALL_DIR="C:\Program Files (x86)\Microsoft Visual Studio\2019\Professional"
IF EXIST %VS_SETUP_EXE% ( GOTO INSTALL )
ECHO No Visual Studio 2019 installation found
EXIT /B 1

:INSTALL
CALL %VS_SETUP_EXE% modify --add Microsoft.VisualStudio.Component.VC.Tools.ARM --installPath %VS_INSTALL_DIR% --passive --norestart
EXIT /B %ERRORLEVEL%

:: ================
::  Print the help
:: ================
:PRINT_HELP
ECHO.
ECHO Syntax: install_vs_arm_build_tool.bat [visual_studio] [arch] [toolset]
ECHO.
ECHO   [visual_studio] Setup the Visual Studio environment of a specific version
ECHO     * Visual Studio 2019
ECHO     * Visual Studio 2022
ECHO     * NMake Visual Studio 2019
ECHO     * NMake Visual Studio 2022
ECHO.
ECHO   [arch] Architecture for compiled binaries/libraries
ECHO     * Win32
ECHO     * Win64
ECHO     * ARM32
ECHO     * ARM64
ECHO.
ECHO   [toolset] Set the toolset used to generate the project
ECHO     * For Visual Studio 2019 generator
ECHO       * V142
ECHO       * Clang
ECHO.
EXIT /B 0