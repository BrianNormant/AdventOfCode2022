@echo OFF
ECHO IN C:
ECHO BUILDING
gcc aoc.c
ECHO RUNNING
call TIMEIT a
DEL a.exe

ECHO IN NIM
ECHO BUIDLING
nim c -o:a.exe aoc.nim
ECHO RUNNING
call TIMEIT a
DEL a.exe 