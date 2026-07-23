#include <stdlib.h>
#include "night_calculations.h"

void move_thief_to_end(Role *middle_cards)
{int i;
for(i=0; i<3; i++)
    {if(middle_cards[i].type == KRADEC)
        {change_roles(middle_cards[i], middle_cards[2]);
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
    {change_roles(players[player_index].role, middle_cards[choosen_index]);
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


Night_deaths resolve_night_actions(Player *players, Wolves_choice wolves_choice, int saved_by_doctors_index, int attacked_by_killer_index)
{Night_deaths night_deaths = {-1, -1};

if(wolves_choice.sleepless_index == -1) // Ако Вълците НЕ са познали Безсънницата
    {if(saved_by_doctors_index == -1 || wolves_choice.victim_index != saved_by_doctors_index) // Ако Лекарите НЕ са в играта или НЕ са спасили правилния човек (жертвата на вълците) => изборът на Убиеца се анулира
        {night_deaths.first = wolves_choice.victim_index; // Умира само жертвата на Вълците
        players[night_deaths.first].is_alive = NO;}
    
    else // Ако Лекарите са в играта и са спасили правилния човек (жертвата на вълците)
        {if(attacked_by_killer_index == -1) // Ако Убиецът НЕ е в играта => не е атакувал никого
            ; // Никой не умира
        
        else // Ако Убиецът е в играта
            {night_deaths.first = attacked_by_killer_index; // Умира атакуваният от Убиеца
            players[night_deaths.first].is_alive = NO;}}}

else // Ако Вълците са познали Безсънницата
    {if(saved_by_doctors_index == -1 || (wolves_choice.victim_index != saved_by_doctors_index && saved_by_doctors_index != wolves_choice.sleepless_index)) // Ако Лекарите НЕ са в играта или НЕ са спасили правилния човек (жертвата на вълците) и не са спасили Безсънницата => изборът на Убиеца се анулира
        {night_deaths.first = wolves_choice.victim_index; // Умира жертвата на Вълците
        players[night_deaths.first].is_alive = NO;
        night_deaths.second = wolves_choice.sleepless_index; // Умира и Безсънницата
        players[night_deaths.second].is_alive = NO;}
    
    else // Ако Лекарите са в играта и са спасили правилния човек (жертвата на вълците)
        {if(wolves_choice.sleepless_index == saved_by_doctors_index) // Ако Лекарите са спасили Безсънницата => изборът на Убиеца се анулира
            {night_deaths.first = wolves_choice.victim_index; // Умира само жертвата на Вълците
            players[night_deaths.first].is_alive = NO;}
        
        else // Ако Лекарите НЕ са спасили Безсънницата
            {if(attacked_by_killer_index == -1) // Ако Убиецът НЕ е в играта => не е атакувал никого
                {night_deaths.first = wolves_choice.sleepless_index; // Умира само Безсънницата
                players[night_deaths.first].is_alive = NO;}
            
            else // Ако Убиецът е в играта
                {if(wolves_choice.sleepless_index == attacked_by_killer_index) // Ако Убиецът е атакувал Безсънницата
                    {night_deaths.first = wolves_choice.sleepless_index; // Умира само Безсънницата
                    players[night_deaths.first].is_alive = NO;}
                
                else // Ако Убиецът НЕ е атакувал Безсънницата
                    {night_deaths.first = attacked_by_killer_index; // Умира атакуваният от Убиеца
                    players[night_deaths.first].is_alive = NO;
                    night_deaths.second = wolves_choice.sleepless_index; // Умира и Безсънницата
                    players[night_deaths.second].is_alive = NO;}}}}}

return night_deaths;}