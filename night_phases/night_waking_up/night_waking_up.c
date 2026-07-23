#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>

#include "night_waking_up.h"
#include "../../narrator_tools/narrator_tools.h"

#define MAX_SUGGESTION 50
#define MAX_MESSAGE (20 + MAX_NAME + MAX_ROLE_NAME + MAX_DESCRIPTION)
#define MESSAGE_KILLED_PLAYERS 100

void start_the_night()
{system("cls");
speak_and_print("Everyone, close your eyes. The night begins!");
printf("\n\nType a random button when you are already asleep!\n");
getch();}


char * say_role_suggestion(Role *middle_cards)
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
{int thief_index;
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
    char *suggestion_text = say_role_suggestion(middle_cards);
    int choosen_index = menu(names, 3, suggestion_text);
    free(suggestion_text);

    thief_index = change_with_chosen_middle_card(players, players_count, middle_cards, KRADEC, choosen_index);

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
{int double_agent_index;
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
    char *suggestion_text = say_role_suggestion(middle_cards);
    int choosen_index = menu(names, 2, suggestion_text);
    free(suggestion_text);

    double_agent_index = change_with_chosen_middle_card(players, players_count, middle_cards, DVOEN_AGENT, choosen_index);

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


Wolves_choice wake_wolves(Player *players, int players_count)
{

}


void wake_seer(Player *players, int players_count)
{

}


int wake_doctors(Player *players, int players_count, int last_night_saved_index)
{

}


int wake_killer(Player *players, int players_count)
{

}


void say_killed_players(Player *players, Wolves_choice wolves_choice, int saved_by_doctors_index, int attacked_by_killer_index)
{char message[MESSAGE_KILLED_PLAYERS];
Night_deaths night_deaths = resolve_night_actions(players, wolves_choice, saved_by_doctors_index, attacked_by_killer_index);

if(night_deaths.first == -1)
    speak_and_print("During this night no one died!");

else
    {if(night_deaths.second == -1)
        {sprintf(message, "During this night died %s.", players[night_deaths.first].name);
        speak_and_print(message);}
    else
        {sprintf(message, "During this night died %s and %s.", players[night_deaths.first].name, players[night_deaths.second].name);
        speak_and_print(message);}}}