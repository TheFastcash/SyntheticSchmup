@echo off
set current_dir=%cd%

set SyntheticSchmup_CONFIGURATION=Release

call 1.config.bat

cd %BUILD_DIR%\%SyntheticSchmup_CONFIGURATION%

cmake %SOURCE_DIR% -G"Visual Studio 14 2015 Win64" -DCMAKE_BUILD_TYPE=%SyntheticSchmup_CONFIGURATION%

cd %current_dir%