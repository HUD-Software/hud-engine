@ECHO OFF

:: ======================
::  Build HUDEngine
:: ======================
IF /I "%~1" EQU "Visual Studio 2019" (
    CALL %~dp0build_msvc.bat "%~1" "%~2" "%~3" "%~4" "%~5"
    ECHO. build return %ERRORLEVEL%
    EXIT /B %ERRORLEVEL%
)

IF /I "%~1" EQU "Visual Studio 2022" (
    CALL %~dp0build_msvc.bat "%~1" "%~2" "%~3" "%~4" "%~5"
    ECHO. build return %ERRORLEVEL%
    EXIT /B %ERRORLEVEL%
)

IF /I "%~1" EQU "NMake Visual Studio 2019" (
    CALL %~dp0build_nmake_makefile.bat "%~1" "%~2" "%~3" "%~4" "%~5"
    ECHO. build return %ERRORLEVEL%
    EXIT /B %ERRORLEVEL%
)

IF /I "%~1" EQU "NMake Visual Studio 2022" (
    CALL %~dp0build_nmake_makefile.bat "%~1" "%~2" "%~3" "%~4" "%~5"
    ECHO. build return %ERRORLEVEL%
    EXIT /B %ERRORLEVEL%
)

:: ===================================
:: Error if not genertor are selected
:: ===================================
ECHO.
ECHO Not generator specified. Generator should be :
ECHO     * Visual Studio 2019
ECHO     * Visual Studio 2022
ECHO     * NMake Visual Studio 2019
ECHO     * NMake Visual Studio 2022
ECHO.
EXIT 1
