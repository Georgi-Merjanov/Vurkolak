#ifndef START_GAME_H
#define START_GAME_H

#include "../types.h"

static int string_to_role_type(char string[]);
static int string_to_team(char string[]);
Role* load_roles(const char *filename, int cards_to_load);
static void shuffle_roles(Role *roles, int total_cards);
static void assign_roles_to_players(Player *players, int players_count, Role *shuffled_roles, Role *middle_cards);
void fill_roles(Player *players, int players_count, Role *middle_cards, const char *filename);

#endif