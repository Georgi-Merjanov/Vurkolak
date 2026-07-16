#ifndef NARRATOR_H
#define NARRATOR_H

#include "../types.h"

void speak(const char text[]);
void speak_and_print(const char text[]);
void typewriter_print(const char text[]);
void three_dots();

static void clear_last_lines(int lines);
int menu(char *texts[], int count, char message[]);

void show_roles_to_players(Player *players, int players_count, int kmet_index);
void start_the_night();

void wake_thief(Player *players, int players_count, Role *middle_cards);
void wake_double_agent(Player *players, int players_count, Role *middle_cards);
char * narrate_role_suggestion(Role *middle_cards);

#endif