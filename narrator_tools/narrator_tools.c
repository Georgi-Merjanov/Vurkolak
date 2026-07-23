#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include "narrator_tools.h"

#define MILISECONDS 60
#define TIMES_DOTS 5
#define MAX_COMMAND 500


void speak(const char text[])
{char command[MAX_COMMAND];
sprintf(command, "powershell -Command \"Add-Type -AssemblyName System.Speech; (New-Object System.Speech.Synthesis.SpeechSynthesizer).Speak('%s')\"", text);
system(command);}


void speak_and_print(const char text[])
{printf("%s", text);
speak(text);}


void typewriter_print(const char text[])
{int i;
for(i=0; text[i] != '\0'; i++)
    {printf("%c", text[i]);
    fflush(stdout);
    Sleep(MILISECONDS);}
printf("\n");}


void three_dots()
{int i;

for(i=0; i<TIMES_DOTS; i++)
    {printf("."); fflush(stdout); Sleep(200);
    printf("."); fflush(stdout); Sleep(200);
    printf("."); fflush(stdout); Sleep(200);

    Sleep(200);
    printf("\b \b\b \b\b \b");
    fflush(stdout);
    Sleep(200);}}


void clear_last_lines(int lines)
{int i;
for(i=0; i<lines; i++)
    {printf("\033[A");
    printf("\033[K");}}


int menu(char *texts[], int count, char message[])
{int i, lines, option = 0;
unsigned char symbol;

while(1)
    {for(i=0; i<count; i++)
        printf("%s%s\n", texts[i], (option == i) ? "<" : "");
    if(message)
        {printf("\n%s\n", message);
        lines = count + 2;}

    symbol = getch();
    if(symbol == 13) break;

    if(symbol == 224)
        {symbol = getch();
        if(symbol == 72 && option > 0) option--;
        if(symbol == 80 && option < count-1) option++;}

    clear_last_lines(lines);}
printf("\n");
return option;}


int menu_alive_players(Player *players, int players_count, Role_type role_type_exeption)
{int i, alive_players_without_exeption_count=0, option = 0;
unsigned char symbol;
Role_type role_type_exeption2 = INVALID;

if(role_type_exeption == VULK && players_count >= 10)
    role_type_exeption2 = GLAVATAR;

for(i=0; i<players_count; i++)
    {if(players[i].is_alive == YES && players[i].role.type != role_type_exeption && players[i].role.type != role_type_exeption2)
        alive_players_without_exeption_count++;}

Player *alive_players_without_exeption=(Player *)malloc(alive_players_without_exeption_count*sizeof(Player));
if(alive_players_without_exeption==NULL)
    {printf("Error allocating memory\n");
    exit(1);}

alive_players_without_exeption_count = 0;
for(i=0; i<players_count; i++)
    {if(players[i].is_alive == YES && players[i].role.type != role_type_exeption && players[i].role.type != role_type_exeption2)
        alive_players_without_exeption[alive_players_without_exeption_count++] = players[i];}

while(1)
    {for(i=0; i<alive_players_without_exeption_count; i++)
        printf("%s%s\n", alive_players_without_exeption[i].name, (option == i) ? "<" : "");

    symbol = getch();
    if(symbol == 13) break;

    if(symbol == 224)
        {symbol = getch();
        if(symbol == 72 && option > 0) option--;
        if(symbol == 80 && option < alive_players_without_exeption_count-1) option++;}

    clear_last_lines(alive_players_without_exeption_count);}
printf("\n");

for(i=0; i<players_count; i++)
    {if(strcmp(players[i].name, alive_players_without_exeption[option].name) == 0)
        {free(alive_players_without_exeption);
        return i;}}}