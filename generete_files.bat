@echo off
chcp 65001 > nul
echo Създаване на празна структура за проекта "Върколак" в текущата директория...

:: 1. Създаване на папките за модулите
mkdir role_loader
mkdir game_logic
mkdir narrator

:: 2. Създаване на напълно празни файлове в текущата директория
type nul > types.h
type nul > main.c
type nul > test_suite.c
type nul > roles.csv
type nul > Makefile

:: 3. Създаване на напълно празни файлове в папките на модулите
type nul > role_loader\role_loader.h
type nul > role_loader\role_loader.c

type nul > game_logic\game_logic.h
type nul > game_logic\game_logic.c

type nul > narrator\narrator.h
type nul > narrator\narrator.c

echo.
echo Готово! Всички файлове и папки бяха създадени напълно празни.
pause