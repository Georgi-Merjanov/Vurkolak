#ifndef NIGHT_CALCULATIONS_H
#define NIGHT_CALCULATIONS_H

#include "../../types.h"

typedef struct {
    int victim_index;       // индекс на убития
    int sleepless_index;    // индекс на познатата Безсънница (ако не е позната -1)
} Wolves_choice;

typedef struct {
    int first;     // индекс на първия умрял (ако няма -1)
    int second;    // индекс на втория умрял (ако няма -1)
} Night_deaths;

void move_thief_to_end(Role *middle_cards);
Bool is_role_not_in_the_middle(Role *middle_cards, Role_type role_type);
int change_with_chosen_middle_card(Player *players, int players_count, Role *middle_cards, Role_type role_type, int choosen_index);
int suggest_role(Role *middle_cards);

Night_deaths resolve_night_actions(Player *players, Wolves_choice wolves_choice, int saved_by_doctors_index, int attacked_by_killer_index);

#endif