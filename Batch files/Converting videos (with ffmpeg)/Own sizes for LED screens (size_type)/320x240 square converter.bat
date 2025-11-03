@echo off
setlocal EnableDelayedExpansion

for %%f in (square-*.mp4) do (
	set "filename=%%~nxf"

	call :process "%%f"
)

pause
goto :eof

:process
set "filename=%~1"
set "filename=%~nx1"

echo %nameonly% | findstr /R "^[0-9][0-9]*x[0-9][0-9]*-square-.*\.mp4" >nul
	if %errorlevel% EQU 0 (
		echo %nameonly% is not OK
	) else (
		echo Converting %nameonly%
		ffmpeg -i "%~1" -vf "scale=320:240" -y "320x240-%~nx1"
	)