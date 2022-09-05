@ECHO OFF

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
IF /I "%~2" NEQ "Win32" (
IF /I "%~2" NEQ "Win64" (
IF /I "%~2" NEQ "ARM32" (
IF /I "%~2" NEQ "ARM64" (
    ECHO.
    ECHO Error: [arch] is invalid : "%~2"
    ECHO.
    CALL:PRINT_HELP
    EXIT 1
))))
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
EXIT 1
)))
SET config=%~4

:: ============================
:: Check [target] parameter
:: ============================
IF /I "%~5" NEQ "" (
SET target=/target:%~5
)

:: ============================
:: Set build environnement
:: ============================
SET current_dir=%~dp0
CALL %current_dir%setup_build_env.bat "%generator%" "%arch%" "%toolset%" "%config%"
IF ERRORLEVEL 1 EXIT /B 1

:: ======================================
::  Build the HUDEngine.sln using MSBuild
:: ======================================
PUSHD "%build_dir%"
where /q msbuild
IF ERRORLEVEL 1 CALL %current_dir%setup_vs.bat "%generator%" "%arch%" "%toolset%"

CALL :PRINT_HEADER "msbuild HUDEngine.sln /p:Configuration=%config% %target% -maxcpucount"
ECHO Build ^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>
ECHO.
CALL msbuild HUDEngine.sln /p:Configuration=%config% %target% -maxcpucount
EXIT /B %ERRORLEVEL%

:: =====================
:: Print command header
:: =====================
:PRINT_HEADER
ECHO  ________
ECHO ^|       ^|
ECHO ^| Build ^|
ECHO ^|_______^|
ECHO.
ECHO BUILD_DIR = %build_dir%
ECHO GENERATOR = %generator%
ECHO CONFIGURATION = %config%
ECHO ARCHITECTURE = %arch%
ECHO TOOLSET = %toolset%
ECHO CMD = %~1
ECHO.
EXIT /B 0


:: ================
::  Print the help
:: ================
:PRINT_HELP
ECHO.
ECHO Syntax: build_msvc.bat [generator] [arch] [toolset]
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
ECHO     * V142
ECHO     * Clang
ECHO.
ECHO   [config] Configuration used to generate the project
ECHO     * Debug
ECHO     * Release
ECHO     * DebugOptimized
ECHO.
ECHO   [target] (Optional) Select the target to build. This correspond to the generator target.
ECHO.
EXIT /B 0
