#ifndef NIGHT_WAKING_UP_H
#define NIGHT_WAKING_UP_H

#include "../../types.h"

void start_the_night();
char * narrate_role_suggestion(Role *middle_cards);
void wake_thief(Player *players, int players_count, Role *middle_cards);
void wake_double_agent(Player *players, int players_count, Role *middle_cards);

#endif