@echo off
:check_Permissions (
    net session >nul 2>&1
    if %errorLevel% == 0 (
        set /a isAdmin = 1
    ) else (
        set /a isAdmin = 0
    )
)
CD "%~dp0"
RD /s /q "%homepath%\Indie"
MD "%homepath%\Indie"
call "C:\Windows\System32\xcopy.exe" /s /i ..\Media "%homepath%\Indie\Media"
if %errorlevel% neq 0 goto :AdminError
call "C:\Windows\System32\xcopy.exe" /s /i ..\Misc "%homepath%\Indie\Misc"
if %errorlevel% neq 0 goto :AdminError
call "C:\Windows\System32\xcopy.exe" /s .\bin\* "%homepath%\Indie\"
if %errorlevel% neq 0 goto :AdminError
echo "Indie Bomberman was correctly installed in %homepath%\Indie\"
if %isAdmin% == 1 (
	MKLINK "%homepath%\Desktop\Indie.exe" "..\Indie\indie.exe"
	timeout 1
)
MD "%homepath%\Indie\Misc\Maps"
set /p answer="Run Indie Bomberman? Y/N"
if "%answer%" == "Y" goto :launch
if "%answer%" == "y" goto :launch
goto :exit
:launch (
	echo "Launching..."
	timeout 2
	start "Indie" "%homepath%\Indie\indie.exe"
	exit /b 0
)
:exit (
	echo "Exiting..."
	timeout 2
	exit /b 0
)
:AdminError (
	echo "Could not copy files to ~\Indie\. Try running as Administrator"
	timeout 10
	exit /b %errorlevel%
)
