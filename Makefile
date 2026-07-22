main: main.exe tests.exe
	./main.exe

tests: tests.exe
	./tests.exe

object_files = narrator_tools/narrator_tools.o \
       role_loader/role_loader.o \
       setup_game/setup_game.o \
       night_phases/night_calculations/night_calculations.o \
       night_phases/night_waking_up/night_waking_up.o \
       day_phases/day_calculations/day_calculations.o \
       day_phases/day_events/day_events.o

main.exe: main.c $(object_files)
	gcc main.c $(object_files) -o main.exe

tests.exe: tests.c $(object_files)
	gcc tests.c $(object_files) -o tests.exe

narrator_tools/narrator_tools.o: narrator_tools/narrator_tools.c narrator_tools/narrator_tools.h types.h
	gcc -c narrator_tools/narrator_tools.c -o narrator_tools/narrator_tools.o

role_loader/role_loader.o: role_loader/role_loader.c role_loader/role_loader.h types.h roles.csv
	gcc -c role_loader/role_loader.c -o role_loader/role_loader.o

setup_game/setup_game.o: setup_game/setup_game.c setup_game/setup_game.h types.h role_loader/role_loader.h narrator_tools/narrator_tools.h
	gcc -c setup_game/setup_game.c -o setup_game/setup_game.o

night_phases/night_calculations/night_calculations.o: night_phases/night_calculations/night_calculations.c night_phases/night_calculations/night_calculations.h types.h narrator_tools/narrator_tools.h
	gcc -c night_phases/night_calculations/night_calculations.c -o night_phases/night_calculations/night_calculations.o

night_phases/night_waking_up/night_waking_up.o: night_phases/night_waking_up/night_waking_up.c night_phases/night_waking_up/night_waking_up.h types.h narrator_tools/narrator_tools.h night_phases/night_calculations/night_calculations.h
	gcc -c night_phases/night_waking_up/night_waking_up.c -o night_phases/night_waking_up/night_waking_up.o

day_phases/day_calculations/day_calculations.o: day_phases/day_calculations/day_calculations.c day_phases/day_calculations/day_calculations.h types.h
	gcc -c day_phases/day_calculations/day_calculations.c -o day_phases/day_calculations/day_calculations.o

day_phases/day_events/day_events.o: day_phases/day_events/day_events.c day_phases/day_events/day_events.h types.h narrator_tools/narrator_tools.h day_phases/day_calculations/day_calculations.h
	gcc -c day_phases/day_events/day_events.c -o day_phases/day_events/day_events.o

clean:
	del /s *.o *.exe