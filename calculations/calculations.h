#ifndef CALCULATIONS_H
#define CALCULATIONS_H

#include "../types.h"

void wake_thief(Player *thief, Role *middle_cards);
void wake_double_agent(Player *thief, Role *middle_cards);

int suggest_role(Role *middle_cards);

#endif