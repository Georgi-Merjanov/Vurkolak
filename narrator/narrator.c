#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "narrator.h"


void narrator_show_initial_roles(Player *players, int players_count, int kmet_index)
{int i, t=0;
unsigned char a;

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
        
        printf("===================================================================== %s =====================================================================", players[t].name);
        printf("\n\nYou are %s.\n\n%s", players[t].role.name, players[t].role.description);
        printf("\n\nType a random button to if you are ready!");
        a=getch();}}}