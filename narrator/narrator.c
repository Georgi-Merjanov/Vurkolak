#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include "narrator.h"
#include "../calculations/calculations.h"
#include "../start_game/start_game.h"

#define MILISECOUNDS 60
#define TIMES_DOTS 5
#define MAX_COMMAND 500
#define MAX_SUGGESTION 50
#define MAX_MESSAGE (20 + MAX_NAME + MAX_ROLE_NAME + MAX_DESCRIPTION)

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
    Sleep(MILISECOUNDS);}
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


static void clear_last_lines(int lines)
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


void show_roles_to_players(Player *players, int players_count, int kmet_index)
{int i, option = 0;
unsigned char symbol;
char message[MAX_ROLE_NAME + 50];
char description[MAX_DESCRIPTION];

while(1)
    {system("cls");
    printf("============================================== The roles are shuffled! You can see it separately! ==============================================\n\n");
    printf("The Kmet is %s.\nHe has the special right to decide in case of a tied vote.\n\n", players[kmet_index].name);
    
    for(i=0; i<players_count; i++)
        {if(option == i)
            printf("%s<\n", players[i].name);
        else
            printf("%s\n", players[i].name);}
    if(option == players_count)
        printf("Start the game<\n");
    else
        printf("Start the game\n");

    symbol = getch();
    if(symbol == 224)
        {symbol = getch();
        if(symbol == 72 && option > 0) option--;
        if(symbol == 80 && option < players_count) option++;}

    if(symbol == 13)
        {system("cls");
        if(option == players_count) break;

        printf("===================================================================== %s =====================================================================\n\n", players[option].name);
        sprintf(message, "You are %s.", players[option].role.name);
        typewriter_print(message);
        printf("\n");
        Sleep(1000);

        sprintf(description, "%s", players[option].role.description);
        typewriter_print(description);
        printf("\n");
        Sleep(500);

        typewriter_print("When you are ready, type a random button to return to the menu!");
        symbol = getch();}}}


void start_the_night()
{system("cls");
speak_and_print("Everyone, close your eyes. The night begins!");
printf("\n\nType a random button when you are already asleep!\n");
getch();}


char * narrate_role_suggestion(Role *middle_cards)
{int i, suggested_index = suggest_role(middle_cards);
Bool is_double_agent = NO;

char *suggestion=(char *)malloc(MAX_SUGGESTION*sizeof(char));
if(suggestion==NULL)
    {printf("Error allocating memory\n");
    exit(1);}

for(i=0; i<3; i++)
    {if(middle_cards[i].type == KRADEC)
        is_double_agent = YES;}

if(is_double_agent == NO)
    sprintf(suggestion, "I suggest you to choose: %s.", middle_cards[suggested_index].name);

if(is_double_agent == YES)
    sprintf(suggestion, "I suggest you to choose: Card %d.", suggested_index + 1);

return suggestion;}


void wake_thief(Player *players, int players_count, Role *middle_cards)
{int i, thief_index;
char message[MAX_MESSAGE];
Bool there_is_thief = YES;

Sleep(1000);
system("cls");
printf("======================================================================== KRADEC (THIEF) ================================================================\n\n");
speak_and_print("Thief, wake up. Open your eyes.");
printf("\n\n");
Sleep(3000);
speak_and_print("Choose one of the three cards in the middle:");
printf("\n\n");

there_is_thief = is_role_not_in_the_middle(middle_cards, KRADEC);

if(there_is_thief)
    {char *names[] = {middle_cards[0].name, middle_cards[1].name, middle_cards[2].name};
    char *suggestion_text = narrate_role_suggestion(middle_cards);
    int choosen_index = menu(names, 3, suggestion_text);

    thief_index = execute_role_swap(players, players_count, middle_cards, KRADEC, choosen_index);

    printf("--------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    sprintf(message, "%s, from this moment, you are %s.", players[thief_index].name, players[thief_index].role.name);
    typewriter_print(message);

    printf("\n");
    typewriter_print(players[thief_index].role.description);

    printf("\n");
    typewriter_print("When you are ready, type a random button to continue the game!");
    getch();}

else
    {printf("There is no Thief!\n");
    Sleep(30000);}

printf("\n");
speak_and_print("Close your eyes and go to sleep.");}


void wake_double_agent(Player *players, int players_count, Role *middle_cards)
{int i, double_agent_index;
char message[MAX_MESSAGE];
Bool there_is_double_agent = YES;

move_thief_to_end(middle_cards);

Sleep(1000);
system("cls");
printf("================================================================== DVOEN AGENT (DOUBLE AGENT) ==========================================================\n\n");
speak_and_print("Double agent, wake up. Open your eyes.");
printf("\n\n");
Sleep(3000);
speak_and_print("Choose one of the two cards in the middle:");
printf("\n\n");

there_is_double_agent = is_role_not_in_the_middle(middle_cards, DVOEN_AGENT);

if(there_is_double_agent)
    {char *names[] = {"Card 1", "Card 2"};
    char *suggestion_text = narrate_role_suggestion(middle_cards);
    int choosen_index = menu(names, 2, suggestion_text);

    double_agent_index = execute_role_swap(players, players_count, middle_cards, DVOEN_AGENT, choosen_index);

    printf("--------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    sprintf(message, "%s, from this moment, you are %s.", players[double_agent_index].name, players[double_agent_index].role.name);
    typewriter_print(message);

    printf("\n");
    typewriter_print("When you are killed, it will be revealed that you were a Double agent and you won't die until you are killed a second time.");

    printf("\n");
    typewriter_print(players[double_agent_index].role.description);

    printf("\n");
    typewriter_print("When you are ready, type a random button to continue the game!");
    getch();}

else
    {printf("There is no Double agent!\n");
    Sleep(30000);}

printf("\n");
speak_and_print("Close your eyes and go to sleep.");}