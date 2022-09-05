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
EXIT 1
)))) 
SET visual_studio=%~1

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

:: ========================================================
::  Retrieves correct variable name corresponding to CMake
:: ========================================================
IF /I "%arch%" EQU "Win32" SET architecture=x86
IF /I "%arch%" EQU "Win64" SET architecture=amd64
IF /I "%arch%" EQU "ARM32" SET architecture=arm
IF /I "%arch%" EQU "ARM64" SET architecture=arm64

:: =====================================
:: Retriseves correct Toolset argument
:: =====================================
IF /I "%toolset%" EQU "V142" SET toolset_arg=-vcvars_ver=14.2


:: ========================================================================================
:: We use the x64 build tools except when compiling an Win32 NMake Makefile with Clang
:: ========================================================================================
SET host_arch=amd64
IF /I "%arch%" EQU "Win32" (
IF /I "%toolset%" EQU "Clang" (
IF /I "%visual_studio%" EQU "NMake Visual Studio 2019" SET host_arch=x86
IF /I "%visual_studio%" EQU "NMake Visual Studio 2022" SET host_arch=x86
))

:: =======================
::  Setup the environment
:: =======================
IF /I "%visual_studio%" EQU "Visual Studio 2019"  GOTO SETUP_VS_2019_ENV_VAR
IF /I "%visual_studio%" EQU "Visual Studio 2022"  GOTO SETUP_VS_2022_ENV_VAR
IF /I "%visual_studio%" EQU "NMake Visual Studio 2019" GOTO SETUP_VS_2019_ENV_VAR
IF /I "%visual_studio%" EQU "NMake Visual Studio 2022" GOTO SETUP_VS_2022_ENV_VAR
EXIT 1

:: ==========================
::  Setup Visual Studio 2019
:: ==========================
:SETUP_VS_2019_ENV_VAR
SET VSDEVCMD="C:\Program Files (x86)\Microsoft Visual Studio\2019\Professional\Common7\Tools\VsDevCmd.bat"
IF EXIST %VSDEVCMD% ( GOTO VSDEVCMD_SCRIPT )
SET VSDEVCMD="C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\Tools\VsDevCmd.bat"
IF EXIST %VSDEVCMD% ( GOTO VSDEVCMD_SCRIPT ) 
ECHO No Visual Studio 2019 installation found
EXIT 1

:: ==========================
::  Setup Visual Studio 2022
:: ==========================
:SETUP_VS_2022_ENV_VAR
SET VSDEVCMD="C:\Program Files\Microsoft Visual Studio\2022\Professional\Common7\Tools\VsDevCmd.bat"
IF EXIST %VSDEVCMD% ( GOTO VSDEVCMD_SCRIPT )
SET VSDEVCMD="C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\Tools\VsDevCmd.bat"
IF EXIST %VSDEVCMD% ( GOTO VSDEVCMD_SCRIPT )
SET VSDEVCMD="C:\Program Files\Microsoft Visual Studio\2022\Enterprise\Common7\Tools\VsDevCmd.bat"
IF EXIST %VSDEVCMD% ( GOTO VSDEVCMD_SCRIPT )
ECHO No Visual Studio 2022 installation found
EXIT 1

:: ============================================
:: Call VsDevCmd.bat set in %$VSDEVCMD%
:: Use the x64 compiler binaries to avoid out of memory during compilation (-host_arch=amd64)
:: ============================================
:VSDEVCMD_SCRIPT
ECHO  ___________________________________________
ECHO ^|                                           ^|
ECHO ^| Setup Visual Studio Developer Environment ^|
ECHO ^|___________________________________________^|
ECHO.
ECHO ARCHITECTURE="%arch%"
ECHO TOOLSET="%toolset%"
ECHO HOST_ARCH="%host_arch%"
ECHO CMD = %VSDEVCMD% -no_logo -arch=%architecture% %toolset_arg% -host_arch=%host_arch%
ECHO. 
CALL %VSDEVCMD% -no_logo -arch=%architecture% %toolset_arg% -host_arch=%host_arch%
EXIT /B %ERRORLEVEL%

:: ================
::  Print the help
:: ================
:PRINT_HELP
ECHO.
ECHO Syntax: setup_vs.bat [visual_studio] [arch] [toolset]
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
