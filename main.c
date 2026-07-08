#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#include "types.h"
#include "start_game/start_game.h"
#include "calculations/calculations.h"
#include "narrator/narrator.h"

void main()
{printf("========================================================Vurkolak========================================================\n\n");

int players_count;
do
    {printf("How many are the players (6<=players<=11): ");
    scanf("%d", &players_count);
    getchar();}
while(players_count<6 || players_count>11);


}