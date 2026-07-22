#ifndef SETUP_GAME_H
#define SETUP_GAME_H

#include "../types.h"

void shuffle_roles(Role *roles, int total_cards);
void reduce_thief_in_the_middle_chance(Player *players, int players_count, Role *middle_cards);
int assign_roles_to_players(Player *players, int players_count, Role *shuffled_roles, Role *middle_cards);
int fill_roles(Player *players, int players_count, Role *middle_cards, const char *filename);
void show_roles_to_players(Player *players, int players_count, int kmet_index);

#endif