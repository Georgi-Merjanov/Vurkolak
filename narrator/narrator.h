#ifndef NARRATOR_H
#define NARRATOR_H

#include "../types.h"

void speak(const char text[]);
void speak_and_print(const char text[]);
void typewriter_print(const char text[]);

void show_roles_to_players(Player *players, int players_count, int kmet_index);
void start_the_night();

void narrate_role_suggestion(Role *middle_cards);

#endif