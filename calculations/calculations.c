#include <stdlib.h>
#include "calculations.h"


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


void wake_thief(Player *thief, Role *middle_cards)
{

}


void wake_double_agent(Player *thief, Role *middle_cards)
{

}