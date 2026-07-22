#ifndef NARRATOR_TOOLS_H
#define NARRATOR_TOOLS_H

#include "../types.h"

void speak(const char text[]);
void speak_and_print(const char text[]);
void typewriter_print(const char text[]);
void three_dots();

static void clear_last_lines(int lines);
int menu(char *texts[], int count, char message[]);

#endif