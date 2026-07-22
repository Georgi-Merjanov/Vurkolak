#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include "narrator_tools.h"

#define MILISECONDS 60
#define TIMES_DOTS 5
#define MAX_COMMAND 500


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
    Sleep(MILISECONDS);}
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