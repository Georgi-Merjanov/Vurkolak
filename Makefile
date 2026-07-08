all: tests.exe main.exe

main.exe: main.c start_game/start_game.o calculations/calculations.o narrator/narrator.o
	gcc main.c start_game/start_game.o calculations/calculations.o narrator/narrator.o -o main.exe

tests.exe: tests.c start_game/start_game.o calculations/calculations.o narrator/narrator.o
	gcc tests.c start_game/start_game.o calculations/calculations.o narrator/narrator.o -o tests.exe
	./tests.exe


start_game/start_game.o: start_game/start_game.c start_game/start_game.h types.h
	gcc -c start_game/start_game.c -o start_game/start_game.o

calculations/calculations.o: calculations/calculations.c calculations/calculations.h types.h
	gcc -c calculations/calculations.c -o calculations/calculations.o

narrator/narrator.o: narrator/narrator.c narrator/narrator.h types.h
	gcc -c narrator/narrator.c -o narrator/narrator.o


clean:
	del /s *.o *.exe