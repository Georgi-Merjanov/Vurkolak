#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "role_loader.h"
#include "../types.h"
#define MAX_LINE MAX_ROLE_NAME*2+MAX_DESCRIPTION+7

int string_to_role_type(char string[])
{if(strcmp(string,"KRADEC")==0) return KRADEC;
if(strcmp(string,"DVOEN_AGENT")==0) return DVOEN_AGENT;
if(strcmp(string,"GLAVATAR")==0) return GLAVATAR;
if(strcmp(string,"VULK")==0) return VULK;
if(strcmp(string,"BEZSUNNICA")==0) return BEZSUNNICA;
if(strcmp(string,"GADATEL")==0) return GADATEL;
if(strcmp(string,"LEKAR")==0) return LEKAR;
if(strcmp(string,"UBIEC")==0) return UBIEC;
if(strcmp(string,"MAZOHIST")==0) return MAZOHIST;
if(strcmp(string,"SELQNIN")==0) return SELQNIN;
return 0;}


int string_to_team(char string[])
{if(strcmp(string,"GOOD")==0) return GOOD;
if(strcmp(string,"BAD")==0) return BAD;
if(strcmp(string,"SOLO")==0) return SOLO;
if(strcmp(string,"UNKNOWN")==0) return UNKNOWN;
return 0;}


Role* load_roles(const char *filename, int roles_count)
{int i;
char line[MAX_LINE], *token;
Role *roles=(Role *)malloc(roles_count*sizeof(Role));
if(roles==NULL)
    {printf("Error allocating memory\n");
    exit(1);}

FILE *file=fopen(filename, "r");
if(file==NULL)
    {printf("Error opening the file!\n");
    exit(1);}

for(i=0; fgets(line,MAX_LINE,file)!=NULL && i<roles_count; i++)
    {token=strtok(line, "; ");
    if(token!=NULL)
        roles[i].type=string_to_role_type(token);

    token=strtok(NULL, "; ");
    if(token!=NULL)
        strcpy(roles[i].name, token);

    token=strtok(NULL, ";");
    if(token!=NULL)
        strcpy(roles[i].description, token);

    token=strtok(NULL, ";");
    if(token!=NULL)
        {strcat(roles[i].description, "\n\n");
        strcat(roles[i].description, token);}

    token=strtok(NULL, "\n");
    if(token!=NULL)
        roles[i].team=string_to_team(token);}

fclose(file);
return roles;}