@echo off
setlocal EnableDelayedExpansion

for %%f in (horiz-*.mp4) do (
	set "filename=%%~nxf"

	call :process "%%f"
)

pause
goto :eof

:process
set "filename=%~1"
set "filename=%~nx1"

echo %nameonly% | findstr /R "^[0-9][0-9]*x[0-9][0-9]*-horiz-.*\.mp4" >nul
	if %errorlevel% EQU 0 (
		echo %nameonly% is not OK
	) else (
		echo Converting %nameonly%
		ffmpeg -i "%~1" -vf "scale=512:256" -y "512x256-%~nx1"
	)