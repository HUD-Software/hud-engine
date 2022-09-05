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
    EXIT /B 1
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
    EXIT /B 1
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
    EXIT /B 1
))
set toolset=%~3


:: ============================
:: Set build environnement
:: ============================
SET current_dir=%~dp0
CALL %current_dir%setup_build_env.bat "%generator%" "%arch%" "%toolset%"
IF ERRORLEVEL 1 EXIT /B %ERRORLEVEL%

:: ===================================
::  Generate a Visual Studio solution
:: ===================================
PUSHD "%build_dir%"

:: Delete the CMakeCache.txt file is present
IF EXIST CMakeCache.txt DEL CMakeCache.txt

:: Get the related CMake architecture, Visual Studio generator and toolset
IF /I "%arch%" EQU "Win32" SET cmake_arch=Win32
IF /I "%arch%" EQU "Win64" SET cmake_arch=x64
IF /I "%arch%" EQU "ARM32" SET cmake_arch=ARM
IF /I "%arch%" EQU "ARM64" SET cmake_arch=ARM64
IF /I "%generator%" EQU "Visual Studio 2019" SET cmake_generator=Visual Studio 16 2019
IF /I "%generator%" EQU "Visual Studio 2022" SET cmake_generator=Visual Studio 17 2022
IF /I "%toolset%" EQU "V142" SET cmake_toolset=v142
IF /I "%toolset%" EQU "Clang" SET cmake_toolset=ClangCL

CALL :PRINT_HEADER "CMake %current_dir%../../.. -G %cmake_generator% -A %cmake_arch% -T %cmake_toolset%"
ECHO CMake generation ^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>^>
ECHO.
CALL CMake "%current_dir%../../.." -G "%cmake_generator%" -A "%cmake_arch%" -T "%cmake_toolset%"
IF ERRORLEVEL 1 EXIT /B %ERRORLEVEL%
ECHO.
ECHO ^<^<^<^<^<^<^<^<^<^<^<^<^<^<^<^<^<^<^<^<^<^<^<^<^<^<^<^<^<^<^<^<^<^<^<^<^<^<^<^<^<^<^<^ CMake generation
POPD
EXIT /B %ERRORLEVEL%

:: =====================
:: Print command header
:: =====================
:PRINT_HEADER
ECHO  ____________________
ECHO ^|                    ^|
ECHO ^| Generate HUDEngine ^|
ECHO ^|____________________^|
ECHO.
ECHO BUILD_DIR = %build_dir%
ECHO GENERATOR = %generator%
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
ECHO Syntax: generate_msvc.bat [generator] [arch] [toolset]
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
EXIT /B 0
