@echo off
SET src=TRAB1-1\
SET dst=INF1301-TRAB1-FPFMMQPF\%src%
FOR /F "delims=" %%a IN (%src%.files) DO XCOPY "%src%%%a" "%dst%" /Y

REN "INF1301-TRAB1-FPFMMQPF\TRAB1-1\TRAB1-1.exe" "TRAB1-1.exe.txt"