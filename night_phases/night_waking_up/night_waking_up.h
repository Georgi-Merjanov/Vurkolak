#ifndef NIGHT_WAKING_UP_H
#define NIGHT_WAKING_UP_H

#include "../../types.h"
#include "../night_calculations/night_calculations.h"

void start_the_night();
char * say_role_suggestion(Role *middle_cards);
void wake_thief(Player *players, int players_count, Role *middle_cards);
void wake_double_agent(Player *players, int players_count, Role *middle_cards);
Wolves_choice wake_wolves(Player *players, int players_count);
void wake_seer(Player *players, int players_count);                                  // само му показва какъв е отборът на играч
int wake_doctors(Player *players, int players_count, int last_night_saved_index);    // връща индекс на спасения (ако ги няма -1)
int wake_killer(Player *players, int players_count);                                 // връща индекса на атакувания (ако го няма -1)
void say_killed_players(Player *players, Wolves_choice wolves_choice, int saved_by_doctors_index, int attacked_by_killer_index);
#endif