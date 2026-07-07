all: tests.exe main.exe

main.exe: main.c role_loader/role_loader.o game_logic/game_logic.o narrator/narrator.o
	gcc main.c role_loader/role_loader.o game_logic/game_logic.o narrator/narrator.o -o main.exe

tests.exe: tests.c role_loader/role_loader.o game_logic/game_logic.o narrator/narrator.o
	gcc tests.c role_loader/role_loader.o game_logic/game_logic.o narrator/narrator.o -o tests.exe


role_loader/role_loader.o: role_loader/role_loader.c role_loader/role_loader.h types.h
	gcc -c role_loader/role_loader.c -o role_loader/role_loader.o

game_logic/game_logic.o: game_logic/game_logic.c game_logic/game_logic.h types.h
	gcc -c game_logic/game_logic.c -o game_logic/game_logic.o

narrator/narrator.o: narrator/narrator.c narrator/narrator.h types.h
	gcc -c narrator/narrator.c -o narrator/narrator.o


clean:
	del /s *.o *.exe