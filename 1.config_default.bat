@echo off
REM The location of the main CMakeLists.txt (actually, this is the folder where this file is located)
set SOURCE_DIR=  REM e.g. C:\SyntheticSchmup
REM The build destination of the project
set BUILD_DIR=  REM e.g. C:\SyntheticSchmup-build
REM The external libraries destination (headers and libs)
set EXTERNALS_DIR=  REM e.g. C:\SyntheticSchmup-externals


REM =======================================================

if not exist "%BUILD_DIR%" (
    mkdir "%BUILD_DIR%"
)
if not exist "%BUILD_DIR%\Superbuild" (
    mkdir "%BUILD_DIR%\Superbuild"
)
if not exist "%BUILD_DIR%\Release" (
    mkdir "%BUILD_DIR%\Release"
)
if not exist "%BUILD_DIR%\Debug" (
    mkdir "%BUILD_DIR%\Debug"
)

if "%SyntheticSchmup_CONFIGURATION%"=="Release" (
    goto :other
) else (
    if "%SyntheticSchmup_CONFIGURATION%"=="Debug" (
        goto :other
    )
)
goto :end

:other
    set SFML_ROOT=%EXTERNALS_DIR%\sfml\%SyntheticSchmup_CONFIGURATION%
    set PATH=%SFML_ROOT%\bin;%PATH%
    goto :end

:end
REM echo "%PATH%"