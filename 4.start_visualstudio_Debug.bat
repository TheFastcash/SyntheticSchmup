@echo off
set current_dir=%cd%

set SyntheticSchmup_CONFIGURATION=Debug

call 1.config.bat

cd %BUILD_DIR%\%SyntheticSchmup_CONFIGURATION%

call SyntheticSchmup.sln

cd %current_dir%