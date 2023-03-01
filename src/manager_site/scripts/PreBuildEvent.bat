@echo off

set DISK=%~d0
set CURRENT=%cd%

set ROOT=%CURRENT%\..\..\..\..\..
set TOOLS_DIR=%ROOT%\tools\bin\

set RES_SKIN_DIR=%CURRENT%\..\res\skin

set RES_RELEASE_PATHNAME=%RES_SKIN_DIR%\..\skin.zip
set RES_RELEASE_FINAL_PATHNAME=%RES_SKIN_DIR%\..\skin.res
rem @echo %RES_SKIN_DIR%
rem @echo %TOOLS_DIR%

rem call %TOOLS_DIR%compress.exe %RES_SKIN_DIR% %RES_RELEASE_PATHNAME%
call %TOOLS_DIR%encryption.exe 9 %RES_RELEASE_PATHNAME% %RES_RELEASE_FINAL_PATHNAME%

rem del /F /S /Q %RES_RELEASE_FINAL_PATHNAME%
rem del /F /S /Q %RES_RELEASE_PATHNAME%