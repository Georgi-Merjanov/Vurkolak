#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

#include "types.h"
#include "start_game/start_game.h"
#include "calculations/calculations.h"
#include "narrator/narrator.h"

void main()
{printf("========================================================Vurkolak========================================================\n\n");

int i, players_count;
char *p;

do
    {printf("How many are the players (6<=players<=11): ");
    scanf("%d", &players_count);
    getchar();}
while(players_count<6 || players_count>11);


Player *players = (Player *)malloc(players_count * sizeof(Player));
if(players == NULL)
    {printf("Error allocating memory\n");
    exit(1);}

Role middle_cards[3];

for(i=0; i<players_count; i++)
    {printf("Type the name of the %d-th player: ",i+1);
    fgets(players[i].name, MAX_NAME, stdin);

    if(p=strchr(players[i].name,'\n'))
        *p='\0';
    else
        while(getchar()!='\n');}

srand(time(NULL));
fill_roles(players, players_count, middle_cards, filename);



free(players);}