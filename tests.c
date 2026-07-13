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
    i++;} \
  else \
    printf(MESSAGE ": FAILED\n"); \
  b++;

int b=0,i=0;


void Test_load_roles_first_card_should_be_thief()
{int cards_to_load=1;
Role *loaded_cards=load_roles("roles.csv", cards_to_load);
printf("======================================== TEST: FIRST CARD THIEF ========================================\n");
ASSERT_TEST("Loaded cards buffer should not be NULL", loaded_cards!=NULL);
if(loaded_cards!=NULL)
  {ASSERT_TEST("First role type should be KRADEC", loaded_cards[0].type==KRADEC);
  ASSERT_TEST("First role text name should be Kradec", strcmp(loaded_cards[0].name,"Kradec")==0);
  ASSERT_TEST("First role team should be UNKNOWN", loaded_cards[0].team==UNKNOWN);
  free(loaded_cards);}
printf("\n");}


void Test_load_roles_third_card_should_be_sleepless()
{int cards_to_load=3;
Role *loaded_cards=load_roles("roles.csv", cards_to_load);
ASSERT_TEST("Loaded cards buffer should not be NULL", loaded_cards!=NULL);
if(loaded_cards!=NULL)
  {ASSERT_TEST("Third role type should be BEZSUNNICA", loaded_cards[2].type==BEZSUNNICA);
  ASSERT_TEST("Third role text name should be Bezsunnica", strcmp(loaded_cards[2].name,"Bezsunnica")==0);
  ASSERT_TEST("Third role team should be GOOD", loaded_cards[2].team==GOOD);
  free(loaded_cards);}
printf("\n");}


void Test_load_roles_ninth_card_should_be_masochist()
{int cards_to_load=9;
Role *loaded_cards=load_roles("roles.csv", cards_to_load);
ASSERT_TEST("Loaded cards buffer should not be NULL", loaded_cards!=NULL);
if(loaded_cards!=NULL)
  {ASSERT_TEST("Ninth role type should be MAZOHIST", loaded_cards[8].type==MAZOHIST);
  ASSERT_TEST("Ninth role text name should be Mazohist", strcmp(loaded_cards[8].name,"Mazohist")==0);
  ASSERT_TEST("Ninth role team should be SOLO", loaded_cards[8].team==SOLO);
  free(loaded_cards);}
printf("\n");}


void Test_load_roles_fourteenth_card_should_be_villager()
{int cards_to_load=14;
Role *loaded_cards=load_roles("roles.csv", cards_to_load);
ASSERT_TEST("Loaded cards buffer should not be NULL", loaded_cards!=NULL);
if(loaded_cards!=NULL)
  {ASSERT_TEST("Fourteenth role type should be SELQNIN", loaded_cards[13].type==SELQNIN);
  ASSERT_TEST("Fourteenth role text name should be Selqnin", strcmp(loaded_cards[13].name,"Selqnin")==0);
  ASSERT_TEST("Fourteenth role team should be GOOD", loaded_cards[13].team==GOOD);
  free(loaded_cards);}
printf("\n");}


void Test_role_loader()
{printf("======================================== TEST_ROLE_LOADER ========================================\n");
Test_load_roles_first_card_should_be_thief();
Test_load_roles_third_card_should_be_sleepless();
Test_load_roles_ninth_card_should_be_masochist();
Test_load_roles_fourteenth_card_should_be_villager();}


void main()
{printf("\n");

Test_role_loader();

printf("Tests: %d/%d passed!\n\n",i,b);}