@echo off

DEL "INF1301-TRAB1-FPFMMQPF\*.*" /F /S /Q

CALL "MoveFiles.bat"
CALL "TRAB1-1\MoveFiles.bat"
CALL "TRAB1-2\MoveFiles.bat"