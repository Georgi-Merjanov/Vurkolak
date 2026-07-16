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


void Test_wake_thief_logic_when_thief_is_present()
{int i, players_count = 6, theif_index = -1;
Player players[6];
Role middle_cards[3];

for(i=0; i<players_count; i++)
    {sprintf(players[i].name, "Player_%d", i+1);
    players[i].role.type = SELQNIN;
    strcpy(players[i].role.name, "Selqnin (Peasant)");}

players[2].role.type = KRADEC;
strcpy(players[2].role.name, "Kradec (Thief)");

middle_cards[0].type = GLAVATAR; strcpy(middle_cards[0].name, "Glavatar (Leader)");
middle_cards[1].type = LEKAR;    strcpy(middle_cards[1].name, "Lekar (Doctor)");
middle_cards[2].type = VULK;     strcpy(middle_cards[2].name, "Vulk (Wolf)");

Bool there_is_theif = YES;
for(i=0; i<3; i++)
    {if(middle_cards[i].type == KRADEC)
        there_is_theif = NO;}

ASSERT_TEST("Thief should be flagged as present when not in the middle", there_is_theif == YES);

int choosen_index = 1; 

if(there_is_theif)
    {for(i=0; i<players_count; i++)
        {if(players[i].role.type == KRADEC)
            theif_index = i;}

    Role temp = players[theif_index].role;
    players[theif_index].role = middle_cards[choosen_index];
    middle_cards[choosen_index] = temp;}

ASSERT_TEST("Thief index should be found correctly (index 2)", theif_index == 2);
ASSERT_TEST("The former Thief player should now be LEKAR", players[2].role.type == LEKAR);
ASSERT_TEST("The middle card at chosen index should now be KRADEC", middle_cards[1].type == KRADEC);
printf("\n");}


void Test_wake_thief_logic_when_thief_is_in_middle()
{int i, players_count = 6;
Player players[6];
Role middle_cards[3];

for(i=0; i<players_count; i++)
    {sprintf(players[i].name, "Player_%d", i+1);
    players[i].role.type = SELQNIN;
    strcpy(players[i].role.name, "Selqnin (Peasant)");}

middle_cards[0].type = GLAVATAR; strcpy(middle_cards[0].name, "Glavatar (Leader)");
middle_cards[1].type = KRADEC;    strcpy(middle_cards[1].name, "Kradec (Thief)");
middle_cards[2].type = VULK;     strcpy(middle_cards[2].name, "Vulk (Wolf)");

Bool there_is_theif = YES;
for(i=0; i<3; i++)
    {if(middle_cards[i].type == KRADEC)
        there_is_theif = NO;}

ASSERT_TEST("Thief should be flagged as ABSENT when in the middle", there_is_theif == NO);
printf("\n");

for(i=0; i<players_count; i++)
    {ASSERT_TEST("Player role should remain Peasant", players[i].role.type == SELQNIN);}
printf("\n");}


void Test_wake_thief()
{printf("======================================== TEST: WAKE THIEF LOGIC ========================================\n\n");
Test_wake_thief_logic_when_thief_is_present();
Test_wake_thief_logic_when_thief_is_in_middle();}


void Test_wake_double_agent_logic_and_thief_displacement()
{int i, players_count = 6, double_agent_index = -1;
Player players[6];
Role middle_cards[3];

for(i=0; i<players_count; i++)
    {sprintf(players[i].name, "Player_%d", i+1);
    players[i].role.type = SELQNIN;
    strcpy(players[i].role.name, "Selqnin (Peasant)");}

players[3].role.type = DVOEN_AGENT;
strcpy(players[3].role.name, "Dvoen Agent (Double Agent)");

middle_cards[0].type = KRADEC;     strcpy(middle_cards[0].name, "Kradec (Thief)");
middle_cards[1].type = GLAVATAR;   strcpy(middle_cards[1].name, "Glavatar (Leader)");
middle_cards[2].type = LEKAR;      strcpy(middle_cards[2].name, "Lekar (Doctor)");

for(i=0; i<3; i++)
    {if(middle_cards[i].type == KRADEC)
        {change_roles(&middle_cards[i], &middle_cards[2]);
        break;}}

ASSERT_TEST("Thief must be moved to index 2", middle_cards[2].type == KRADEC);
ASSERT_TEST("Lekar must be moved to index 0", middle_cards[0].type == LEKAR);
ASSERT_TEST("Glavatar must remain at index 1", middle_cards[1].type == GLAVATAR);

Bool there_is_double_agent = YES;
for(i=0; i<2; i++)
    {if(middle_cards[i].type == DVOEN_AGENT)
        there_is_double_agent = NO;}

ASSERT_TEST("Double agent should be present", there_is_double_agent == YES);

int choosen_index = 0;

if(there_is_double_agent)
    {for(i=0; i<players_count; i++)
        {if(players[i].role.type == DVOEN_AGENT)
            double_agent_index = i;}

    change_roles(&players[double_agent_index].role, &middle_cards[choosen_index]);
    players[double_agent_index].is_double_agent = YES;}

ASSERT_TEST("Double agent index should be 3", double_agent_index == 3);
ASSERT_TEST("The former Double agent player should now be LEKAR", players[3].role.type == LEKAR);
ASSERT_TEST("The middle card at chosen index 0 should now be DVOEN_AGENT", middle_cards[0].type == DVOEN_AGENT);
printf("\n");}


void Test_wake_double_agent_logic_when_agent_is_in_middle()
{int i, players_count = 6;
Player players[6];
Role middle_cards[3];

for(i=0; i<players_count; i++)
    {sprintf(players[i].name, "Player_%d", i+1);
    players[i].role.type = SELQNIN;
    strcpy(players[i].role.name, "Selqnin (Peasant)");}

middle_cards[0].type = GLAVATAR;   strcpy(middle_cards[0].name, "Glavatar (Leader)");
middle_cards[1].type = DVOEN_AGENT; strcpy(middle_cards[1].name, "Dvoen Agent (Double Agent)");
middle_cards[2].type = KRADEC;      strcpy(middle_cards[2].name, "Kradec (Thief)");

for(i=0; i<3; i++)
    {if(middle_cards[i].type == KRADEC)
        {change_roles(&middle_cards[i], &middle_cards[2]);
        break;}}

Bool there_is_double_agent = YES;
for(i=0; i<2; i++)
    {if(middle_cards[i].type == DVOEN_AGENT)
        there_is_double_agent = NO;}

ASSERT_TEST("Double agent should be flagged as ABSENT because he is in the middle", there_is_double_agent == NO);
printf("\n");}


void Test_wake_double_agent()
{printf("======================================== TEST: DOUBLE AGENT LOGIC ========================================\n\n");
Test_wake_double_agent_logic_and_thief_displacement();
Test_wake_double_agent_logic_when_agent_is_in_middle();}


void main()
{system("cls");

Test_role_loader();
Test_fill_roles_integration();
Test_suggest_role_logic();
// Test_narrate_role_suggestion();
// Test_menu();
Test_wake_thief();
Test_wake_double_agent();

printf("\nTests: %d/%d passed!\n\n", passed_tests, all_tests);}