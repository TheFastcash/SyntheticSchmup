@echo off
set current_dir=%cd%

set SyntheticSchmup_CONFIGURATION=Superbuild

call config.bat

cd %BUILD_DIR%\Superbuild

cmake %SOURCE_DIR% -G"Visual Studio 14 2015 Win64" -DCMAKE_BUILD_TYPE=Superbuild

REM cmake $SOURCE_DIR -G"CodeBlocks - Unix Makefiles" -DCMAKE_BUILD_TYPE=Superbuild

call SyntheticSchmup.sln

cd %current_dir%