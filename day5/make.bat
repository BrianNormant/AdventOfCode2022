@echo off
ECHO BUILDING
nim c -o:a.exe aoc_05.nim
ECHO RUNNING
call TIMEIT a
DEL a.exe
ECHO DONE