#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>

#include "setup_game.h"
#include "../role_loader/role_loader.h"
#include "../narrator_tools/narrator_tools.h"


void shuffle_roles(Role *roles, int total_cards)
{int i,j;

for(i=total_cards-1; i>0; i--)
    {j = rand() % (i+1);
    change_roles(roles[i], roles[j]);}}


void reduce_thief_in_the_middle_chance(Player *players, int players_count, Role *middle_cards)
{int i, thief_index;
Bool there_is_thief = YES;
for(i=0; i<3; i++)
    {if(middle_cards[i].type == KRADEC)
        {there_is_thief = NO;
        thief_index = i;
        break;}}

if(there_is_thief == NO)
        {Bool should_swap = rand() % 2;
        if(should_swap)
            {int random_player_index = rand() % players_count;
            change_roles(players[random_player_index].role, middle_cards[thief_index]);}}}


int assign_roles_to_players(Player *players, int players_count, Role *shuffled_roles, Role *middle_cards)
{int i, role_type;

for(i=0; i<players_count; i++)
    {players[i].role = shuffled_roles[i];
    
    role_type = players[i].role.type;
    
    players[i].is_alive = YES;
    players[i].is_double_agent = NO;
    players[i].is_kmet = NO;}

int kmet_index = rand() % players_count;
players[kmet_index].is_kmet = YES;

for(i=0; i<3; i++)
    middle_cards[i] = shuffled_roles[players_count+i];

reduce_thief_in_the_middle_chance(players, players_count, middle_cards);

return kmet_index;}


int fill_roles(Player *players, int players_count, Role *middle_cards, const char *filename)
{int total_cards = players_count+3;
Role *loaded_roles = load_roles(filename, total_cards);

shuffle_roles(loaded_roles, total_cards);
int kmet_index = assign_roles_to_players(players, players_count, loaded_roles, middle_cards);

free(loaded_roles);
return kmet_index;}


void show_roles_to_players(Player *players, int players_count, int kmet_index)
{int i, option = 0;
unsigned char symbol;
char message[MAX_ROLE_NAME + 50];
char description[MAX_DESCRIPTION];

while(1)
    {system("cls");
    printf("============================================== The roles are shuffled! You can see it separately! ==============================================\n\n");
    printf("The Kmet is %s.\nHe has the special right to decide in case of a tied vote.\n\n", players[kmet_index].name);
    
    for(i=0; i<players_count; i++)
        {if(option == i)
            printf("%s<\n", players[i].name);
        else
            printf("%s\n", players[i].name);}
    if(option == players_count)
        printf("Start the game<\n");
    else
        printf("Start the game\n");

    symbol = getch();
    if(symbol == 224)
        {symbol = getch();
        if(symbol == 72 && option > 0) option--;
        if(symbol == 80 && option < players_count) option++;}

    if(symbol == 13)
        {system("cls");
        if(option == players_count) break;

        printf("===================================================================== %s =====================================================================\n\n", players[option].name);
        sprintf(message, "You are %s.", players[option].role.name);
        typewriter_print(message);
        printf("\n");
        Sleep(1000);

        sprintf(description, "%s", players[option].role.description);
        typewriter_print(description);
        printf("\n");
        Sleep(500);

        typewriter_print("When you are ready, type a random button to return to the menu!");
        symbol = getch();}}}