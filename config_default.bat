@echo off
REM The location of the main CMakeLists.txt (actually, this is the folder where this file is located)
set SOURCE_DIR=
REM The build destination of the project
set BUILD_DIR=
REM The external libraries destination (headers and libs)
set EXTERNALS_DIR=

if "%SyntheticSchmup_CONFIGURATION%"=="%Superbuild" (
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
REM ) else "%SyntheticSchmup_CONFIGURATION%"=="Debug" || "%SyntheticSchmup_CONFIGURATION%"=="Release" (
    REM set SFML_ROOT=%EXTERNALS_DIR%\%SyntheticSchmup_CONFIGURATION%\sfml
    REM set PATH=%PATH%;%EXTERNALS_DIR%
)