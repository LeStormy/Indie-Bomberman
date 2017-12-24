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
RD /s /q build
MD build
RD /s /q "%homepath%\Indie"
MD "%homepath%\Indie"
call "C:\Windows\System32\xcopy.exe" /s /i .\Media "%homepath%\Indie\Media"
if %errorlevel% neq 0 goto :AdminError
call "C:\Windows\System32\xcopy.exe" /s /i .\Misc "%homepath%\Indie\Misc"
if %errorlevel% neq 0 goto :AdminError
call "C:\Windows\System32\xcopy.exe" /s .\bin\* "%homepath%\Indie\"
if %errorlevel% neq 0 goto :AdminError
CD build
call "C:\Program Files\CMake\bin\cmake.exe" ..
if %errorlevel% neq 0 goto :CompileError
call "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvarsall.bat" x86
set msBuildDir="C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\MSBuild\15.0\Bin"
SET VCTargetsPath=C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\Common7\IDE\VC\VCTargets
call %msBuildDir%\MSBuild.exe .\indie.sln /target:indie /p:Configuration=Release /p:Platform=Win32
if %errorlevel% neq 0 goto :CompileError
CD ..
call "C:\Windows\System32\xcopy.exe" /s .\Release\* "%homepath%\Indie\"
if %errorlevel% neq 0 goto :AdminError
RD /s /q Release
echo "Indie Bomberman was correctly installed in %homepath%\Indie\"
if %isAdmin% == 1 (
	MKLINK "%homepath%\Desktop\Indie.exe" "..\Indie\indie.exe"
	timeout 1
)
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
	echo "Could not copy files to ~\Indie\. Try running Batch as Administrator"
	timeout 10
	exit /b %errorlevel%
)
:CompileError (
	echo "Fatal! Compile Error."
	timeout 10
	exit /b %errorlevel%
)
