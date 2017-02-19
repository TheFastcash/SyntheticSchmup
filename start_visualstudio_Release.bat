@echo off
set current_dir=%cd%

set SyntheticSchmup_CONFIGURATION=Release

call config.bat

cd %BUILD_DIR%\%SyntheticSchmup_CONFIGURATION%

call SyntheticSchmup.sln

cd %current_dir%
