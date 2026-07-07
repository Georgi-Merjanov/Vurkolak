#ifndef ROLE_LOADER_H
#define ROLE_LOADER_H
#include "../types.h"

int string_to_role_type(char string[]);
int string_to_team(char string[]);
Role* load_roles(const char *filename, int cards_to_load);

#endif