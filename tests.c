#include "everything.h"

#define ASSERT_TEST(MESSAGE, CONDITION) \
  if(CONDITION) \
    {printf(MESSAGE ": PASSED\n"); \
    passed_tests++;} \
  else \
    printf(MESSAGE ": FAILED\n"); \
  all_tests++;

int passed_tests=0, all_tests=0;


void Test_load_roles_first_card_should_be_thief()
{int cards_to_load=1;
Role *loaded_cards=load_roles(filename, cards_to_load);
ASSERT_TEST("Loaded cards buffer should not be NULL", loaded_cards!=NULL);
if(loaded_cards!=NULL)
  {ASSERT_TEST("First role type should be KRADEC", loaded_cards[0].type==KRADEC);
  ASSERT_TEST("First role text name should be Kradec", strcmp(loaded_cards[0].name, "Kradec (Thief)")==0);
  ASSERT_TEST("First role team should be UNKNOWN", loaded_cards[0].team==UNKNOWN);
  free(loaded_cards);}
printf("\n");}


void Test_load_roles_third_card_should_be_sleepless()
{int cards_to_load=3;
Role *loaded_cards=load_roles(filename, cards_to_load);
ASSERT_TEST("Loaded cards buffer should not be NULL", loaded_cards!=NULL);
if(loaded_cards!=NULL)
  {ASSERT_TEST("Third role type should be BEZSUNNICA", loaded_cards[2].type==BEZSUNNICA);
  ASSERT_TEST("Third role text name should be Bezsunnica", strcmp(loaded_cards[2].name, "Bezsunnica (Sleepless)")==0);
  ASSERT_TEST("Third role team should be GOOD", loaded_cards[2].team==GOOD);
  free(loaded_cards);}
printf("\n");}


void Test_load_roles_ninth_card_should_be_masochist()
{int cards_to_load=9;
Role *loaded_cards=load_roles(filename, cards_to_load);
ASSERT_TEST("Loaded cards buffer should not be NULL", loaded_cards!=NULL);
if(loaded_cards!=NULL)
  {ASSERT_TEST("Ninth role type should be MAZOHIST", loaded_cards[8].type==MAZOHIST);
  ASSERT_TEST("Ninth role text name should be Mazohist", strcmp(loaded_cards[8].name, "Mazohist (Masochist)")==0);
  ASSERT_TEST("Ninth role team should be SOLO", loaded_cards[8].team==SOLO);
  free(loaded_cards);}
printf("\n");}


void Test_load_roles_fourteenth_card_should_be_villager()
{int cards_to_load=14;
Role *loaded_cards=load_roles(filename, cards_to_load);
ASSERT_TEST("Loaded cards buffer should not be NULL", loaded_cards!=NULL);
if(loaded_cards!=NULL)
  {ASSERT_TEST("Fourteenth role type should be SELQNIN", loaded_cards[13].type==SELQNIN);
  ASSERT_TEST("Fourteenth role text name should be Selqnin", strcmp(loaded_cards[13].name, "Selqnin (Peasant)")==0);
  ASSERT_TEST("Fourteenth role team should be GOOD", loaded_cards[13].team==GOOD);
  free(loaded_cards);}
printf("\n");}


void Test_role_loader()
{printf("======================================== TEST_ROLE_LOADER ========================================\n\n");
Test_load_roles_first_card_should_be_thief();
Test_load_roles_third_card_should_be_sleepless();
Test_load_roles_ninth_card_should_be_masochist();
Test_load_roles_fourteenth_card_should_be_villager();
printf("\n");}


void Test_reduce_thief_in_the_middle_chance()
{printf("\n======================================== TEST: REDUCE THIEF IN THE MIDDLE CHANCE ========================================\n\n");
int i, players_count = 6;
Player players[6];
Role middle_cards[3];

for(i=0; i<players_count; i++)
    {sprintf(players[i].name, "Player_%d", i+1);
    players[i].role.type = SELQNIN;
    strcpy(players[i].role.name, "Selqnin (Peasant)");}

middle_cards[0].type = GLAVATAR; strcpy(middle_cards[0].name, "Glavatar (Leader)");
middle_cards[1].type = LEKAR;    strcpy(middle_cards[1].name, "Lekar (Doctor)");
middle_cards[2].type = VULK;     strcpy(middle_cards[2].name, "Vulk (Wolf)");

reduce_thief_in_the_middle_chance(players, players_count, middle_cards);

ASSERT_TEST("When Thief is not in middle, middle cards stay unchanged",
            middle_cards[0].type == GLAVATAR && middle_cards[1].type == LEKAR && middle_cards[2].type == VULK);

middle_cards[1].type = KRADEC; strcpy(middle_cards[1].name, "Kradec (Thief)");

srand(1);
reduce_thief_in_the_middle_chance(players, players_count, middle_cards);

Bool thief_found_in_players = NO;
for(i=0; i<players_count; i++)
    {if(players[i].role.type == KRADEC)
        thief_found_in_players = YES;}

ASSERT_TEST("When Thief is in middle and swap triggers, one player gets KRADEC", thief_found_in_players == YES);
ASSERT_TEST("When swap triggers, middle card is no longer KRADEC", middle_cards[1].type != KRADEC);
printf("\n");}


void Test_thief_in_middle_simulation()
{printf("\n======================================== TEST: THIEF IN MIDDLE SIMULATION ========================================\n\n");
int i, total_runs = 1000;
int thief_not_in_middle_count = 0;
Player players[6];
Role middle_cards[3];

srand(time(NULL));

for(i=0; i<total_runs; i++)
    {fill_roles(players, 6, middle_cards, filename);

    if(is_role_not_in_the_middle(middle_cards, KRADEC) == YES)
        thief_not_in_middle_count++;}

printf("The thief in not in the middle kards: %d/%d times!\n\n", thief_not_in_middle_count, total_runs);}


void Test_fill_roles_integration()
{int i, alive_count=0, kmet_count=0, players_count=6;
Player players[6];
Role middle_cards[3];
srand(1);

for(i=0; i<players_count; i++)
    sprintf(players[i].name, "Player_%d", i+1);

fill_roles(players, players_count, middle_cards, filename);

printf("======================================== TEST: FILL ROLES INTEGRATION ========================================\n\n");
ASSERT_TEST("Players array should not be NULL", players!=NULL);

for(i=0; i<players_count; i++)
    {if(players[i].is_alive==1)
        alive_count++;
    
    if(players[i].is_kmet==1)
        kmet_count++;

    Role_type role_type=players[i].role.type;

    switch(role_type)
        {case GLAVATAR: case VULK: ASSERT_TEST("Bad roles must have BAD team", players[i].role.team==BAD); break;
        case MAZOHIST: ASSERT_TEST("Masochist must have SOLO team", players[i].role.team==SOLO); break;
        case KRADEC: case DVOEN_AGENT: ASSERT_TEST("Thief/Double Agent must have UNKNOWN team", players[i].role.team==UNKNOWN); break;
        default: ASSERT_TEST("Good roles must have GOOD team", players[i].role.team==GOOD); break;}}
    
printf("\n");
    
ASSERT_TEST("All players must be alive at start", alive_count==6);
ASSERT_TEST("Exactly 1 player must be chosen as Kmet", kmet_count==1);
ASSERT_TEST("Middle card 1 should have a valid type", middle_cards[0].type>=1 && middle_cards[0].type<=10);
ASSERT_TEST("Middle card 2 should have a valid type", middle_cards[1].type>=1 && middle_cards[1].type<=10);
ASSERT_TEST("Middle card 3 should have a valid type", middle_cards[2].type>=1 && middle_cards[2].type<=10);
printf("\n");}


void Test_suggest_role_logic()
{int recommended_index;
Role test_cards[3];

printf("\n======================================== TEST: SUGGEST ROLE ========================================\n\n");

test_cards[0].type = SELQNIN;
test_cards[1].type = GLAVATAR;
test_cards[2].type = LEKAR;

recommended_index = suggest_role(test_cards);
ASSERT_TEST("Recommended index must be between 0 and 2", recommended_index >= 0 && recommended_index <= 2);
ASSERT_TEST("Should recommend Glavatar (index 1) over Doctor and Peasant", recommended_index == 1);
printf("\n");

test_cards[0].type = SELQNIN;
test_cards[1].type = MAZOHIST;
test_cards[2].type = KRADEC;

recommended_index = suggest_role(test_cards);
ASSERT_TEST("Recommended index must be between 0 and 1", recommended_index >= 0 && recommended_index <= 1);
ASSERT_TEST("Double agent should ignore Mazohist and choose Peasant (index 0)", recommended_index == 0);
ASSERT_TEST("Double agent chosen card type must not be MAZOHIST", test_cards[recommended_index].type != MAZOHIST);
ASSERT_TEST("Double agent chosen card type must not be KRADEC", test_cards[recommended_index].type != KRADEC);
printf("\n");}


void Test_narrate_role_suggestion()
{Role test_cards[3];
char *suggestion;

test_cards[0].type = SELQNIN;
test_cards[1].type = GLAVATAR;
test_cards[2].type = LEKAR;

strcpy(test_cards[0].name, "Selqnin (Peasant)");
strcpy(test_cards[1].name, "Glavatar (Leader)");
strcpy(test_cards[2].name, "Lekar (Doctor)");

suggestion = narrate_role_suggestion(test_cards);
typewriter_print(suggestion);

printf("--------------------------------------------------------------------\n");

test_cards[0].type = SELQNIN;
test_cards[1].type = MAZOHIST;
test_cards[2].type = KRADEC;

strcpy(test_cards[0].name, "Selqnin (Peasant)");
strcpy(test_cards[1].name, "Mazohist (Masochist)");
strcpy(test_cards[2].name, "Kradec (Thief)");

suggestion = narrate_role_suggestion(test_cards);
typewriter_print(suggestion);
printf("\n");}


void Test_menu()
{int count = 6;
char *names[] = {"Gogo", "Emi", "Vasko", "Uli", "Toni", "Lara"};
int index = menu(names, count, "Choose Gogo!");
ASSERT_TEST("Choosen index should be between 0 and 5.", index >= 0 && index <= 5)
printf("Choosen index: %d\n", index);
printf("Choosen name: %s\n\n", names[index]);}


void Test_move_thief_to_end()
{printf("\n======================================== TEST: MOVE THIEF TO THE END ========================================\n\n");
Role middle_cards[3];

middle_cards[0].type = KRADEC;     strcpy(middle_cards[0].name, "Kradec (Thief)");
middle_cards[1].type = GLAVATAR;   strcpy(middle_cards[1].name, "Glavatar (Leader)");
middle_cards[2].type = LEKAR;      strcpy(middle_cards[2].name, "Lekar (Doctor)");

move_thief_to_end(middle_cards);

ASSERT_TEST("move_thief_to_end puts KRADEC at index 2", middle_cards[2].type == KRADEC);
ASSERT_TEST("move_thief_to_end moves former index 2 card to index 0", middle_cards[0].type == LEKAR);
printf("\n");}


void Test_is_role_not_in_the_middle()
{printf("\n======================================== TEST: IS ROLE NOT IN THE MIDDLE ========================================\n\n");
Role middle_cards[3];

middle_cards[0].type = GLAVATAR;
middle_cards[1].type = LEKAR;
middle_cards[2].type = KRADEC;

ASSERT_TEST("is_role_not_in_the_middle for KRADEC when present", is_role_not_in_the_middle(middle_cards, KRADEC) == NO);
ASSERT_TEST("is_role_not_in_the_middle for DVOEN_AGENT when missing", is_role_not_in_the_middle(middle_cards, DVOEN_AGENT) == YES);

middle_cards[0].type = DVOEN_AGENT;
middle_cards[1].type = SELQNIN;
middle_cards[2].type = KRADEC;

ASSERT_TEST("is_role_not_in_the_middle for DVOEN_AGENT when present in first two cards", is_role_not_in_the_middle(middle_cards, DVOEN_AGENT) == NO);
ASSERT_TEST("is_role_not_in_the_middle for KRADEC when present at index 2", is_role_not_in_the_middle(middle_cards, KRADEC) == NO);
printf("\n");}


void Test_change_with_chosen_middle_card()
{printf("\n======================================== TEST: EXECUTE ROLE SWAP ========================================\n\n");
int i, swapped_index, players_count = 6;
Player players[6];
Role middle_cards[3];

for(i=0; i<players_count; i++)
    {sprintf(players[i].name, "Player_%d", i+1);
    players[i].role.type = SELQNIN;
    strcpy(players[i].role.name, "Selqnin (Peasant)");}

players[2].role.type = KRADEC;       strcpy(players[2].role.name, "Kradec (Thief)");
players[4].role.type = DVOEN_AGENT;  strcpy(players[4].role.name, "Dvoen Agent (Double Agent)");

middle_cards[0].type = GLAVATAR; strcpy(middle_cards[0].name, "Glavatar (Leader)");
middle_cards[1].type = LEKAR;    strcpy(middle_cards[1].name, "Lekar (Doctor)");
middle_cards[2].type = VULK;     strcpy(middle_cards[2].name, "Vulk (Wolf)");

swapped_index = change_with_chosen_middle_card(players, players_count, middle_cards, KRADEC, 1);
ASSERT_TEST("change_with_chosen_middle_card returns correct player index for KRADEC", swapped_index == 2);
ASSERT_TEST("Former KRADEC player gets new role", players[2].role.type == LEKAR);
ASSERT_TEST("Middle card gets KRADEC role", middle_cards[1].type == KRADEC);

swapped_index = change_with_chosen_middle_card(players, players_count, middle_cards, DVOEN_AGENT, 0);
ASSERT_TEST("change_with_chosen_middle_card returns correct player index for DVOEN_AGENT", swapped_index == 4);
ASSERT_TEST("Former DVOEN_AGENT player gets new role", players[4].role.type == GLAVATAR);
ASSERT_TEST("Former DVOEN_AGENT player sets is_double_agent flag", players[4].is_double_agent == YES);
ASSERT_TEST("Middle card gets DVOEN_AGENT role", middle_cards[0].type == DVOEN_AGENT);
printf("\n");}


void Test_wake_thief()
{int i, players_count = 6;
Player players[6];
Role middle_cards[3];

for(i=0; i<players_count; i++)
    {sprintf(players[i].name, "Player_%d", i+1);
    players[i].role.type = SELQNIN;
    strcpy(players[i].role.name, "Selqnin (Peasant)");}

players[2].role.type = KRADEC;
strcpy(players[2].role.name, "Kradec (Thief)");
strcpy(players[2].role.description, "You are the Thief. Choose a new role from the middle.");

middle_cards[0].type = GLAVATAR; strcpy(middle_cards[0].name, "Glavatar (Leader)"); strcpy(middle_cards[0].description, "You are the Leader.");
middle_cards[1].type = LEKAR;    strcpy(middle_cards[1].name, "Lekar (Doctor)");    strcpy(middle_cards[1].description, "You are the Doctor.");
middle_cards[2].type = VULK;     strcpy(middle_cards[2].name, "Vulk (Wolf)");       strcpy(middle_cards[2].description, "You are the Wolf.");

wake_thief(players, players_count, middle_cards);

printf("--------------------------------------------------------------------\n");

middle_cards[0].type = KRADEC;   strcpy(middle_cards[0].name, "Kradec (Thief)");
middle_cards[1].type = GLAVATAR; strcpy(middle_cards[1].name, "Glavatar (Leader)");
middle_cards[2].type = LEKAR;    strcpy(middle_cards[2].name, "Lekar (Doctor)");

players[2].role.type = SELQNIN;

wake_thief(players, players_count, middle_cards);
printf("\n");}


void Test_wake_double_agent()
{int i, players_count = 6;
Player players[6];
Role middle_cards[3];

for(i=0; i<players_count; i++)
    {sprintf(players[i].name, "Player_%d", i+1);
    players[i].role.type = SELQNIN;
    strcpy(players[i].role.name, "Selqnin (Peasant)");}

players[4].role.type = DVOEN_AGENT;
strcpy(players[4].role.name, "Dvoen Agent (Double Agent)");
strcpy(players[4].role.description, "You are the Double Agent.");

middle_cards[0].type = GLAVATAR; strcpy(middle_cards[0].name, "Glavatar (Leader)"); strcpy(middle_cards[0].description, "You are the Leader.");
middle_cards[1].type = LEKAR;    strcpy(middle_cards[1].name, "Lekar (Doctor)");    strcpy(middle_cards[1].description, "You are the Doctor.");
middle_cards[2].type = KRADEC;   strcpy(middle_cards[2].name, "Kradec (Thief)");    strcpy(middle_cards[2].description, "You are the Thief.");

wake_double_agent(players, players_count, middle_cards);

printf("--------------------------------------------------------------------\n");

middle_cards[0].type = DVOEN_AGENT; strcpy(middle_cards[0].name, "Dvoen Agent (Double Agent)");
middle_cards[1].type = GLAVATAR;    strcpy(middle_cards[1].name, "Glavatar (Leader)");
middle_cards[2].type = LEKAR;       strcpy(middle_cards[2].name, "Lekar (Doctor)");

players[4].role.type = SELQNIN;

wake_double_agent(players, players_count, middle_cards);
printf("\n");}


void Test_resolve_night_actions()
{printf("======================================== TEST: RESOLVE NIGHT ACTIONS ========================================\n\n");
int i;
Player players[6];
Wolves_choice wolves_choice;
Night_deaths deaths;

for(i=0; i<6; i++)
    players[i].is_alive = YES;

wolves_choice.victim_index = 0;
wolves_choice.sleepless_index = -1;

deaths = resolve_night_actions(players, wolves_choice, 0, -1);

ASSERT_TEST("Scenario 1.1: First dead should be -1", deaths.first == -1);
ASSERT_TEST("Scenario 1.1: Second dead should be -1", deaths.second == -1);
ASSERT_TEST("Scenario 1.1: Victim player 0 remains alive", players[0].is_alive == YES);
printf("\n");


for(i=0; i<6; i++)
    players[i].is_alive = YES;

wolves_choice.victim_index = 0;
wolves_choice.sleepless_index = -1;

deaths = resolve_night_actions(players, wolves_choice, 0, 2);

ASSERT_TEST("Scenario 2.1: First dead is Killer target (2)", deaths.first == 2);
ASSERT_TEST("Scenario 2.1: Second dead is -1", deaths.second == -1);
ASSERT_TEST("Scenario 2.1: Player 2 is dead", players[2].is_alive == NO);
ASSERT_TEST("Scenario 2.1: Victim player 0 remains alive", players[0].is_alive == YES);
printf("\n");


for(i=0; i<6; i++)
    players[i].is_alive = YES;

wolves_choice.victim_index = 0;
wolves_choice.sleepless_index = -1;

deaths = resolve_night_actions(players, wolves_choice, 1, 3);

ASSERT_TEST("Scenario 2.2: First dead is Wolf victim (0)", deaths.first == 0);
ASSERT_TEST("Scenario 2.2: Second dead is -1", deaths.second == -1);
ASSERT_TEST("Scenario 2.2: Player 0 is dead", players[0].is_alive == NO);
ASSERT_TEST("Scenario 2.2: Killer target 3 remains alive", players[3].is_alive == YES);
printf("\n");


for(i=0; i<6; i++)
    players[i].is_alive = YES;

wolves_choice.victim_index = 0;
wolves_choice.sleepless_index = 1;

deaths = resolve_night_actions(players, wolves_choice, 0, 1);

ASSERT_TEST("Scenario 2.3: First dead is Sleepless (1)", deaths.first == 1);
ASSERT_TEST("Scenario 2.3: Second dead is -1", deaths.second == -1);
ASSERT_TEST("Scenario 2.3: Sleepless player 1 is dead", players[1].is_alive == NO);
ASSERT_TEST("Scenario 2.3: Victim player 0 remains alive", players[0].is_alive == YES);
printf("\n");


for(i=0; i<6; i++)
    players[i].is_alive = YES;

wolves_choice.victim_index = 0;
wolves_choice.sleepless_index = 1;

deaths = resolve_night_actions(players, wolves_choice, 0, -1);

ASSERT_TEST("Scenario 2.4: First dead is Sleepless (1)", deaths.first == 1);
ASSERT_TEST("Scenario 2.4: Second dead is -1", deaths.second == -1);
ASSERT_TEST("Scenario 2.4: Sleepless player 1 is dead", players[1].is_alive == NO);
printf("\n");


for(i=0; i<6; i++)
    players[i].is_alive = YES;

wolves_choice.victim_index = 0;
wolves_choice.sleepless_index = 1;

deaths = resolve_night_actions(players, wolves_choice, 1, 2);

ASSERT_TEST("Scenario 2.5: First dead is Wolf victim (0)", deaths.first == 0);
ASSERT_TEST("Scenario 2.5: Second dead is -1", deaths.second == -1);
ASSERT_TEST("Scenario 2.5: Victim player 0 is dead", players[0].is_alive == NO);
ASSERT_TEST("Scenario 2.5: Saved Sleepless player 1 remains alive", players[1].is_alive == YES);
printf("\n");


for(i=0; i<6; i++)
    players[i].is_alive = YES;

wolves_choice.victim_index = 0;
wolves_choice.sleepless_index = 1;

deaths = resolve_night_actions(players, wolves_choice, 0, 2);

ASSERT_TEST("Scenario 3.1 (Z != X): First dead is Killer target (2)", deaths.first == 2);
ASSERT_TEST("Scenario 3.1 (Z != X): Second dead is Sleepless (1)", deaths.second == 1);
ASSERT_TEST("Scenario 3.1 (Z != X): Player 2 is dead", players[2].is_alive == NO);
ASSERT_TEST("Scenario 3.1 (Z != X): Sleepless player 1 is dead", players[1].is_alive == NO);
printf("\n");


for(i=0; i<6; i++)
    players[i].is_alive = YES;

wolves_choice.victim_index = 0;
wolves_choice.sleepless_index = 1;

deaths = resolve_night_actions(players, wolves_choice, 0, 0);

ASSERT_TEST("Scenario 3.1 (Z == X): First dead is Killer target X (0)", deaths.first == 0);
ASSERT_TEST("Scenario 3.1 (Z == X): Second dead is Sleepless (1)", deaths.second == 1);
ASSERT_TEST("Scenario 3.1 (Z == X): Player 0 is dead", players[0].is_alive == NO);
ASSERT_TEST("Scenario 3.1 (Z == X): Sleepless player 1 is dead", players[1].is_alive == NO);
printf("\n");


for(i=0; i<6; i++)
    players[i].is_alive = YES;

wolves_choice.victim_index = 0;
wolves_choice.sleepless_index = 1;

deaths = resolve_night_actions(players, wolves_choice, 3, 2);

ASSERT_TEST("Scenario 3.2: First dead is Wolf victim (0)", deaths.first == 0);
ASSERT_TEST("Scenario 3.2: Second dead is Sleepless (1)", deaths.second == 1);
ASSERT_TEST("Scenario 3.2: Victim player 0 is dead", players[0].is_alive == NO);
ASSERT_TEST("Scenario 3.2: Sleepless player 1 is dead", players[1].is_alive == NO);
printf("\n");}


void main()
{system("cls");

Test_role_loader();
Test_reduce_thief_in_the_middle_chance();
Test_thief_in_middle_simulation();
Test_fill_roles_integration();
Test_suggest_role_logic();
// Test_narrate_role_suggestion();
// Test_menu();
Test_is_role_not_in_the_middle();
Test_move_thief_to_end();
Test_change_with_chosen_middle_card();
// Test_wake_thief();
// Test_wake_double_agent();

Test_resolve_night_actions();

printf("\nTests: %d/%d passed!\n\n", passed_tests, all_tests);}