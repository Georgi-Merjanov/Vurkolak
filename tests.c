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


void main()
{system("cls");

Test_role_loader();
Test_fill_roles_integration();
Test_suggest_role_logic();
// Test_narrate_role_suggestion();
 Test_menu();

printf("\nTests: %d/%d passed!\n\n", passed_tests, all_tests);}