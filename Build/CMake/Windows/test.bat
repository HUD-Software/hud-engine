@ECHO OFF

:: Print the help if requested
IF /I "%~1" EQU "-help" GOTO PRINT_HELP

:: ============================
::  Check [generator] parameter
:: ============================
IF /I "%~1" NEQ "Visual Studio 2019" (
IF /I "%~1" NEQ "Visual Studio 2022" (
IF /I "%~1" NEQ "NMake Visual Studio 2019" (
ECHO. 
ECHO Error: [generator] is invalid : "%~1"
ECHO.
CALL:PRINT_HELP
EXIT /B 1
)))
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
EXIT /B 1
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
EXIT /B 1
))
set toolset=%~3


:: ============================
::  Check [config] parameter
:: ============================
IF /I "%~4" NEQ "Debug" (
IF /I "%~4" NEQ "Release" (
IF /I "%~4" NEQ "DebugOptimized" (
ECHO. 
ECHO Error: [config] is invalid : "%~4"
ECHO.
CALL:PRINT_HELP
EXIT /B 1
)))
SET config=%~4

:: ============================
::  Save [test] parameter
:: ============================
SET test=%~5

:: ============================
:: Move to the build directory
:: ============================
SET current_dir=%~dp0
CALL %current_dir%setup_build_env.bat "%generator%" "%arch%" "%toolset%" "%config%"
IF /I "%build_dir%" EQU "" EXIT /B 1
PUSHD "%build_dir%"
IF /I "%test%" EQU "" (
    CALL CTest -C %config% --verbose
) ELSE (
    CALL CTest -C %config% -R %test% --verbose
)
POPD
EXIT /B %errorlevel%

:: ================
::  Print the help
:: ================
:PRINT_HELP
ECHO.
ECHO Syntax: build.bat [generator] [arch] [toolset] [config] [target]
ECHO.
ECHO   [generator] The generator used to generate the project
ECHO     * Visual Studio 2019
ECHO     * Visual Studio 2022
ECHO     * NMake Visual Studio 2019
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
ECHO   [config] Configuration used to generate the project.
ECHO     * Debug
ECHO     * Release
ECHO     * DebugOptimized
ECHO.
ECHO   [test] Run tests matching regular expression. Run all test if empty.
ECHO.
EXIT /B 0