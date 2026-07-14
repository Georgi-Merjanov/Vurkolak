#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include "narrator.h"

#define MILISECOUNDS 60
#define MAX_COMMAND 500

void speak(const char text[])
{char command[MAX_COMMAND];
sprintf(command, "powershell -Command \"Add-Type -AssemblyName System.Speech; (New-Object System.Speech.Synthesis.SpeechSynthesizer).Speak('%s')\"", text);
system(command);}


void speak_and_print(const char text[])
{char command[MAX_COMMAND];
printf("%s", text);
sprintf(command, "powershell -Command \"Add-Type -AssemblyName System.Speech; (New-Object System.Speech.Synthesis.SpeechSynthesizer).Speak('%s')\"", text);
system(command);}


void typewriter_print(const char *text)
{int i;
for(i=0; text[i] != '\0'; i++)
    {printf("%c", text[i]);
    fflush(stdout);
    Sleep(MILISECOUNDS);}
printf("\n");}


void show_roles_to_players(Player *players, int players_count, int kmet_index)
{int i, t=0;
unsigned char a;
char message[MAX_ROLE_NAME + 10];
char description[MAX_DESCRIPTION];

while(1)
    {system("cls");
    printf("============================================== The roles are shuffled! You can see it separately! ==============================================\n\n");
    printf("The Kmet is %s.\nHe has the special right to decide in case of a tied vote.\n\n", players[kmet_index].name);
    for(i=0; i<players_count; i++)
        {if(t==i)
            printf("%s<\n", players[i].name);
        else
            printf("%s\n", players[i].name);}
    if(t == players_count)
        printf("Start the game<\n");
    else
        printf("Start the game\n");

    a=getch();
    if(a==224)
        {a=getch();
        if(a==72 && t>0) t--;
        if(a==80 && t<players_count) t++;}

    if(a==13)
        {system("cls");
        if(t == players_count) break;

        printf("===================================================================== %s =====================================================================\n\n", players[t].name);
        sprintf(message, "You are %s.", players[t].role.name);
        typewriter_print(message);
        printf("\n");
        Sleep(1000);

        sprintf(description, "%s", players[t].role.description);
        typewriter_print(description);
        printf("\n");
        Sleep(500);

        typewriter_print("Type a random button to return to the menu when you are ready!");
        a=getch();}}}


void start_the_night()
{system("cls");
speak_and_print("Everyone, close your eyes. The night begins!");
printf("\n\nType a random button when you are ready!\n");
getch();}