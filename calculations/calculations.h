#ifndef CALCULATIONS_H
#define CALCULATIONS_H

#include "../types.h"

void move_thief_to_end(Role *middle_cards);
Bool is_role_not_in_the_middle(Role *middle_cards, Role_type role_type);
int change_with_chosen_middle_card(Player *players, int players_count, Role *middle_cards, Role_type role_type, int choosen_index);
int suggest_role(Role *middle_cards);

#endif