@echo off

title Create web-project
echo ==========================================================
echo           Script for initializing files
echo ==========================================================
echo.

for /F %%A in ('echo prompt $E^| cmd') do set "ESC=%%A"
setlocal enabledelayedexpansion

:is_project-name
echo %ESC%[1A%ESC%[s
set /p project_name=Write your project's name: 
if not defined project_name (
	echo The name cannot be empty
	pause
	echo %ESC%[u%ESC%[J
	timeout /t 1 /nobreak >nul
	goto is_project-name
)

echo.

:is_existing-project
echo %ESC%[1A%ESC%[s
if exist "%project_name%" (
	echo The project with this name already exists.
	echo %ESC%[u%ESC%[0J
	echo What do you want to do with it?
	echo 1 === Delete existed project and create another with the same name (CAUTION: files inside the existed project will be deleted)
	echo 2 === Rename existed project and create new with this name
	echo 3 === Leave existed project and change another name for the new one
	set /p user_choice=Write 1, 2 or 3: 
	if "%user_choice%"=="1" (
		rmdir /s /q "%project_name%"
		mkdir "%project_name%"
		cd "%project_name%"
		echo Existed project was recreated succesfully
	) else (
		if "%user_choice%"=="2" (
			set /p new_name_ex=Write new name for existed project: 
			ren "%project_name%" "%new_name_ex%"
			echo Existed project was succesfully renamed
			mkdir "%project_name%"
			cd "%project_name%"
			echo New project was created succesfully
		) else (
			if "%user_choice%"=="3" (
				:is_changed_project-name
				echo %ESC%[1A%ESC%[s
				set /p project_name=Change the name for the new project: 
				if defined project_name (
					if not exist "%project_name%" (
						mkdir "%project_name%"
						cd "%project_name%"
						echo New project was created succesfully
					) else (
						echo The name was already taken
						echo.
						pause
						echo %ESC%[u%ESC%[0J
						timeout /t 1 /nobreak >nul
						goto is_existing-project
					)
				) else (
					echo The name cannot be empty
					pause
					echo %ESC%[u%ESC%[0J
					timeout /t 1 /nobreak >nul
					goto is_changed_project-name
				)
			) else (
				echo Incorrect input
				pause
				echo %ESC%[u%ESC%[J
				timeout /t 1 /nobreak >nul
				goto is_existing-project
			)
		)
	)
)

if not exist "%project_name%" mkdir "%project_name%"
cd "%project_name%"

set /p html_name=Write your HTML's name (default index): 
if "%html_name%"=="" set html_name=index

set /p css_name=Write your CSS's name (default style): 
if "%css_name%"=="" set css_name=style

set /p js_name=Write your JavaScript's name (default script): 
if "%js_name%"=="" set js_name=script

type nul > "%html_name%".html
type nul > "%css_name%".css
type nul > "%js_name%".js

echo.
echo Files "%html_name%".html, "%css_name%".css and "%js_name%".js were created
echo.

:is_existing-git
echo %ESC%[1A%ESC%[s
if exist ".git" (
	echo Git repository was found in the project.
	echo What do  you want to do?
	echo 1 === Delete repository
	echo 2 === Replace repository to the new one
	echo 3 === Leave it
	set /p user_choice=Enter 1, 2 or 3: 
	
	if "%user_choice%"=="1" (
		echo Deleting repository...
		rmdir /s /q ".git"
		echo Repository was succesfully deleted
	) else (
		if "%user_choice%"=="2" (
			echo Do you want to create empty or clone from Git Hub?
			echo 1 === Create empty one
			echo 2 === Clone from GitHub
			set /p replace_repo=Enter 1 or 2: 
			if "%replace_repo%"=="1" (
				echo Replacing old repository with empty one...
				rmdir /s /q ".git"
				git init
				git add .
				git commit -m "init: recreated repository"
				echo New empty repository was succesfully created
			) else (
				if "%replace_repo%"=="2" (
					echo Replacing old repository with cloned one...
					rmdir /s /q ".git"
					set /p link=Enter GitHub repository link: 
					git init
					git remote add origin %link%
					git branch -M main
					git add .
					git commit -m "init: added template of web-files with remote git repository"
					git push origin main
					echo New cloned repository was succesfully added and pushed
				) else (
					echo Incorrect input
					pause
					echo %ESC%[u%ESC%[J
					timeout /t 1 /nobreak >nul
					goto is_existing-git
				)
			)
		) else (
			if "%user_choice%"=="3" (
				echo Git wasn't added to your project
			) else (
				echo Incorrect input
				pause
				echo %ESC%[u%ESC%[J
				timeout /t 1 /nobreak >nul
				goto is_existing-git
			)
		) 
	)
)

:is_create-git
echo %ESC%[1A%ESC%[s
echo Choose the action with Git
echo 1 === Create a local Git repository
echo 2 === Clone GitHub repository
echo 3 === Not create Git repository
set /p user_choice=Enter 1, 2 or 3: 

if "%user_choice%"=="1" (
	git init
	git add .
	git commit -m "init: created repository"
	echo Git repository was succesfully created
) else (
	if "%user_choice%"=="2" (
		set /p link=Enter GitHub repository link: 
		git init
		git remote add origin %link%
		git branch -M main
		git add .
		git commit -m "init: added template of web-files with remote git repository"
		git push origin main
		echo Cloned repository was succesfully added and pushed
	) else (
		if "%user_choice%"=="3" (
			echo Git wasn't added to your project
		) else (
			echo Incorrect input
			pause
			echo %ESC%[u%ESC%[J
			timeout /t 1 /nobreak >nul
			goto is_create-git
		)
	)
)

echo.
pause