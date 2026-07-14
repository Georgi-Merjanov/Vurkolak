#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "start_game/start_game.h"
#include "calculations/calculations.h"
#include "start_game/start_game.h"
#include "types.h"

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
  ASSERT_TEST("First role text name should be Kradec", strcmp(loaded_cards[0].name,"Kradec")==0);
  ASSERT_TEST("First role team should be UNKNOWN", loaded_cards[0].team==UNKNOWN);
  free(loaded_cards);}
printf("\n");}


void Test_load_roles_third_card_should_be_sleepless()
{int cards_to_load=3;
Role *loaded_cards=load_roles(filename, cards_to_load);
ASSERT_TEST("Loaded cards buffer should not be NULL", loaded_cards!=NULL);
if(loaded_cards!=NULL)
  {ASSERT_TEST("Third role type should be BEZSUNNICA", loaded_cards[2].type==BEZSUNNICA);
  ASSERT_TEST("Third role text name should be Bezsunnica", strcmp(loaded_cards[2].name,"Bezsunnica")==0);
  ASSERT_TEST("Third role team should be GOOD", loaded_cards[2].team==GOOD);
  free(loaded_cards);}
printf("\n");}


void Test_load_roles_ninth_card_should_be_masochist()
{int cards_to_load=9;
Role *loaded_cards=load_roles(filename, cards_to_load);
ASSERT_TEST("Loaded cards buffer should not be NULL", loaded_cards!=NULL);
if(loaded_cards!=NULL)
  {ASSERT_TEST("Ninth role type should be MAZOHIST", loaded_cards[8].type==MAZOHIST);
  ASSERT_TEST("Ninth role text name should be Mazohist", strcmp(loaded_cards[8].name,"Mazohist")==0);
  ASSERT_TEST("Ninth role team should be SOLO", loaded_cards[8].team==SOLO);
  free(loaded_cards);}
printf("\n");}


void Test_load_roles_fourteenth_card_should_be_villager()
{int cards_to_load=14;
Role *loaded_cards=load_roles(filename, cards_to_load);
ASSERT_TEST("Loaded cards buffer should not be NULL", loaded_cards!=NULL);
if(loaded_cards!=NULL)
  {ASSERT_TEST("Fourteenth role type should be SELQNIN", loaded_cards[13].type==SELQNIN);
  ASSERT_TEST("Fourteenth role text name should be Selqnin", strcmp(loaded_cards[13].name,"Selqnin")==0);
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
        default: ASSERT_TEST("Good roles must have GOOD team", players[i].role.team==GOOD); break;}
     
    printf("\n");

    switch(role_type)
        {case DVOEN_AGENT: ASSERT_TEST("Dvoen agent flag should be 1", players[i].is_dvoen_agent==1); break;
        default: ASSERT_TEST("Non-dvoen agent flag should be 0", players[i].is_dvoen_agent==0); break;}}
    
printf("\n");
    
ASSERT_TEST("All players must be alive at start", alive_count==6);
ASSERT_TEST("Exactly 1 player must be chosen as Kmet", kmet_count==1);
ASSERT_TEST("Middle card 1 should have a valid type", middle_cards[0].type>=1 && middle_cards[0].type<=10);
ASSERT_TEST("Middle card 2 should have a valid type", middle_cards[1].type>=1 && middle_cards[1].type<=10);
ASSERT_TEST("Middle card 3 should have a valid type", middle_cards[2].type>=1 && middle_cards[2].type<=10);
printf("\n");}


void main()
{printf("\n");

Test_role_loader();
Test_fill_roles_integration();

printf("Tests: %d/%d passed!\n\n", passed_tests, all_tests);}