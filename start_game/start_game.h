#ifndef START_GAME_H
#define START_GAME_H

#include "../types.h"

static int string_to_role_type(char string[]);
static int string_to_team(char string[]);
Role* load_roles(const char *filename, int cards_to_load);
void shuffle_roles(Role *roles, int total_cards);
void assign_roles_to_players(Player *players, int players_count, Role *shuffled_roles);
void choose_kmet(Player *players, int players_count);
void setup_game(Player *players, int players_count, Role *middle_cards, const char *filename);

#endif