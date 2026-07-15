#include "everything.h"

void main()
{system("cls");
printf("========================================================= Welcome to the game Vurkolak =========================================================\n\n");
speak("Welcome to the game Vurkolak!");

int i, players_count;
char *p;

/*
do
    {typewriter_print("How many are the players (6<=players<=11): ");
    scanf("%d", &players_count);
    getchar();}
while(players_count<6 || players_count>11);
*/

players_count = 6;

Player *players = (Player *)malloc(players_count * sizeof(Player));
if(players == NULL)
    {printf("Error allocating memory\n");
    exit(1);}

Role middle_cards[3];

printf("\n");

/*
for(i=0; i<players_count; i++)
    {typewriter_print("Type the name of the %d-th player: ",i+1);
    fgets(players[i].name, MAX_NAME, stdin);

    if(p=strchr(players[i].name, '\n'))
        *p='\0';
    else
        while(getchar()!='\n');}
*/

char *players_names[] = {"Gogo", "Emi", "Vasko", "Uli", "Toni", "Lara"};

for(i=0; i<players_count; i++)
    strcpy(players[i].name, players_names[i]);

srand(time(NULL));
int kmet_index = fill_roles(players, players_count, middle_cards, filename);

show_roles_to_players(players, players_count, kmet_index);

start_the_night();
wake_thief(players, players_count, middle_cards);

free(players);}