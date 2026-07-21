#include <stdlib.h>
#include "calculations.h"
#include "../start_game/start_game.h"


void move_thief_to_end(Role *middle_cards)
{int i;
for(i=0; i<3; i++)
    {if(middle_cards[i].type == KRADEC)
        {change_roles(&middle_cards[i], &middle_cards[2]);
        break;}}}


Bool is_role_not_in_the_middle(Role *middle_cards, Role_type role_type)
{int i, cards_to_check = (role_type == KRADEC) ? 3 : 2;

for(i=0; i<cards_to_check; i++)
    {if(middle_cards[i].type == role_type)
        return NO;}
return YES;}


int change_with_chosen_middle_card(Player *players, int players_count, Role *middle_cards, Role_type role_type, int choosen_index)
{int i, player_index = -1;

for(i=0; i<players_count; i++)
    {if(players[i].role.type == role_type)
        {player_index = i;
        break;}}

if(player_index != -1)
    {change_roles(&players[player_index].role, &middle_cards[choosen_index]);
    if(role_type == DVOEN_AGENT)
        players[player_index].is_double_agent = YES;}

return player_index;}


int suggest_role(Role *middle_cards)
{int i, j;
Bool is_double_agent = NO;
Role_type priority_list[] = {DVOEN_AGENT, GLAVATAR, VULK, BEZSUNNICA, LEKAR, GADATEL, MAZOHIST, UBIEC, SELQNIN, KRADEC};

for(i=0; i<3; i++)
    {if(middle_cards[i].type == KRADEC)
        is_double_agent = YES;}

for(i=0; i<10; i++)
    {for(j=0; j<3; j++)
        {if(priority_list[i] == middle_cards[j].type && (!is_double_agent || middle_cards[j].type != MAZOHIST))
            return j;}}}