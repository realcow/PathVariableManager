@ECHO OFF

:: has .bat extension for making it runnable
SET PVM_TEMPFILE=%TEMP%\PVM-TEMP-%DATE%-%RANDOM%.bat
PUSHD %~dp0
PathVariableManager.exe %1 %2 %3 %4
POPD

:: 
IF %ERRORLEVEL% == 9 (
	SET /P PATH= < %PVM_TEMPFILE%
) ELSE IF %ERRORLEVEL% == 8 (
	CALL %PVM_TEMPFILE%
)

IF EXIST %PVM_TEMPFILE% (
	DEL %PVM_TEMPFILE%
)
SET PVM_TEMPFILE=