#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define max_br 20
#define max_br2 500
#define GOOD 1
#define SOLO 2
#define BAD 3
#define UNKNOWN 4

typedef struct{
    char name[max_br];
    char role[max_br];
    char description[max_br2];
    char role2[max_br]; // ����� ���� (�� ������� �����)
    char role3[max_br]; // ����� ���� (�� �����)
    char description3[max_br2]; // ����� �������� (�� �����)
    int is_alive; // 1-alive, 0-dead
    int is_good;
}Player;

typedef struct {
    char name[max_br];
    char description[max_br2];
    int is_good;
}Role;

void clear_last_lines(int n);
int recommend_role(Role *cards, int count, int is_double_agent);


void main()
{int n,i,j,t=0,sleep=0,k,c=0,b,skip=-1,wolf_victim_index=-1,good,bad;
int pobeda; // 1-GOOD, 3-BAD
int mazohist_index_pobeda=0; // 1-������� �, 2-�� � �������
char *p;
unsigned char a;
srand(time(NULL));

printf("========================================================Vurkolak========================================================\n\n");
do
    {printf("How many are the players (6<=players<=11): ");
    scanf("%d",&n);
    getchar();}
while(n<6||n>11);

int night_victims[n]; // ������� �� ������� ���� ���
int night_count=0; // ���� ����� ���� ���
int wolf_victim_saved=0;

Player players[n];

Role all_roles[]=
    {{"Kradec", "Flips the three cards in the middle. Chooses one and swaps it with his own. Then places the seen cards face down, but his new one face up.\n\nObrushta trite karti po sredata. Izbira si edna i q zamenq za svoqta. Sled tova ostavq kartite, koito e vidql s litse nadolu, no svoqta s litse nagore.", UNKNOWN},
    {"Dvoen_agent", "Wakes up after the thief. Chooses one of the two remaining middle cards, without looking first. After choosing, he checks what it is and becomes that role. When killed, he is revealed as a double agent and does not die until killed a second time.\n\nSubujda se sled kradeca. Izbira si edna ot dvete ostanali karti po sredata, no bez da gi gleda. Sled kato si q e izbral, q vijda kakva e i se prevrushta v neq. Kogato go ubiqt, se razkriva che e bil dvoen agent i oshte ne e umrql, dokato ne go ubiqt vtori put.", UNKNOWN},
    {"Bezsunnica", "She is on the good team. She wakes up every night when the wolves wake up, but secretly, to see who they are. Her goal is not to be noticed. If the wolves figure her out, she dies immediately.\n\nTq e ot dobrite. Subujda se vsqka nosht kogato se subudqt vulcite, no taino, za da gi vidi koi sa. Tselta i e da ne q vidqt koq e. Ako q razgadaqt, tq umira vednaga.", GOOD},
    {"Vulk", "He is on the bad team. Wakes up with the other wolf and the Leader. They decide who to kill, but the Leader has the final word. At the end, they also point to who they think is the Sleepless. If they guess correctly, she dies automatically.\n\nToi e ot loshiq otbor. Subujda se s drugiq vulk i glavataq. Reshavat kogo da ubiqt, no glavataq ima krainata duma. Nakrq posochvat koi mislqt che e bezsunnicata i ako q uluchat, tq umira avtomatichno.", BAD},
    {"Vulk", "He is on the bad team. Wakes up with the other wolf and the Leader. They decide who to kill, but the Leader has the final word. At the end, they also point to who they think is the Sleepless. If they guess correctly, she dies automatically.\n\nToi e ot loshiq otbor. Subujda se s drugiq vulk i glavataq. Reshavat kogo da ubiqt, no glavataq ima krainata duma. Nakrq posochvat koi mislqt che e bezsunnicata i ako q uluchat, tq umira avtomatichno.", BAD},
    {"Gadatel", "He is on the good team. Each night he can check if a player is good, bad, or the Masochist.\n\nToi e ot dobrite. Toi moje da razbere prez vsqka nosht dali edin igraqch e ot dobrite, dali e ot loshite, ili e mazohist.", 1},
    {"Lekar", "He is on the good team. Each night he chooses someone to save. He can save himself, but cannot save the same person two nights in a row. His goal is to save the wolves� victim if he guesses correctly.\n\nToi e ot dobrite. Vsqka nosht toi se subujda s drugiq lekar, izbirat kogo da spqsqt. Mogat da spasqt i sebe si, no ne moje dve poredni noshti da spqsvat edin i sushti chovek. Tselta im e da spasqt jertvata na vulcite, ako q uluchat.", GOOD},
    {"Ubiec", "He is on the good team. Wakes up every night after the doctors and kills someone. If the doctors saved the wolves� victim, then his chosen person really dies. Otherwise, the person survives.\n\nToi e ot dobrite. Subujda se vsqka nosht sled lekarite i ubiva nqkoi. Ako lekarite sa spqsili jertvata na vulcite, tozi chovek umira naistina. Inache, ocelqva.", 1},
    {"Mazohist", "He plays only for himself. His goal is to be voted out before the game ends. If this happens, he wins, but he does not reveal he is the Masochist, and the game continues for the other two teams.\n\nToi igrae sam za sebe si. Tselta mu e da bude ubit ot glasuvane predi igrata da svrshi. Ako tova stane, toi pecheli igrata, no ne se izdava che e mazohist i igrata produljava za drugite dva otbora.", SOLO},
    {"Selqnin", "He is on the good team. Sleeps through the whole night and never wakes up.\n\nToi e ot dobrite. Spi prez cqla nosht i ne se subujda.", GOOD},
    {"Lekar", "He is on the good team. Each night he chooses someone to save. He can save himself, but cannot save the same person two nights in a row. His goal is to save the wolves� victim if he guesses correctly.\n\nToi e ot dobrite. Vsqka nosht toi se subujda s drugiq lekar, izbirat kogo da spqsqt. Mogat da spasqt i sebe si, no ne moje dve poredni noshti da spqsvat edin i sushti chovek. Tselta im e da spasqt jertvata na vulcite, ako q uluchat.", GOOD},
    {"Selqnin", "He is on the good team. Sleeps through the whole night and never wakes up.\n\nToi e ot dobrite. Spi prez cqla nosht i ne se subujda.", GOOD},
    {"Glavatar", "He is on the bad team. Wakes up with the wolves. Together they choose who to kill, but he has the final word. At the end, they also point to who they think is the Sleepless. If they guess correctly, she dies automatically.\n\nToi e ot loshiq otbor. Subujda se s vulcite. Zaedno izbirat kogo da ubiqt, no toi ima krainata duma. Nakrq posochvat koi mislqt che e bezsunnicata i ako q uluchat, tq umira avtomatichno.", BAD},
    {"Selqnin", "He is on the good team. Sleeps through the whole night and never wakes up.\n\nToi e ot dobrite. Spi prez cqla nosht i ne se subujda.", GOOD}};

Role roles[n+3];

for(i=0;i<n+3;i++)
    roles[i]=all_roles[i];

int indices[n+3];
for(i=0;i<n+3;i++)
    indices[i]=i;

// ����������� �� ��������� (Fisher�Yates shuffle)
for(i=n+2;i>0;i--)
    {int j=rand()%(i+1);
    int tmp=indices[i];
    indices[i]=indices[j];
    indices[j]=tmp;}

printf("\n");

for(i=0;i<n;i++)
    {printf("Type the name of the %d-th player: ",i+1);
    fgets(players[i].name,max_br,stdin); //name
    if(p=strchr(players[i].name,'\n'))
        *p='\0';
    strcpy(players[i].role,roles[indices[i]].name); // role
    strcpy(players[i].description,roles[indices[i]].description); // description
    strcpy(players[i].role2,"no_role2"); // role2 (��� ��� ����)
    strcpy(players[i].role3,"no_role3"); // role3 (��� ��� ���� ����)
    strcpy(players[i].description3,"no_description3"); // description3 (��� ��� ���� ����)
    players[i].is_alive=1; // is_alive (������������ ������ �� ����)
    players[i].is_good=roles[indices[i]].is_good;} // is_good

int kmet_index=rand()%n;
strcpy(players[kmet_index].role3,"Kmet");
strcpy(players[kmet_index].description3,"He has the special right to decide in case of a tied vote.\nReshava koj da umre pri ravni glasove.");

// ������� �� ������
while(1)
    {system("cls");
    printf("The roles are shuffled! You can see it separately!\nRolite sa razburkani! Mozete da si gi vidite pootdelno!\n\n");
    printf("The Kmet is %s.\n\n%s\n\n\n",players[kmet_index].name,players[kmet_index].description3);
    for(i=0;i<n;i++)
        {if(t==i)
            printf("%s<\n",players[i].name);
        else
            printf("%s\n",players[i].name);}
    if(t==n)
        printf("Start the game<\n");
    else
        printf("Start the game\n");

    a=getch();
    if(a==224)
        {a=getch();
        if(a==72&&t>0)
            t--;
        if(a==80&&t<n)
            t++;}
    if(a==13)
        {system("cls");
        if(t==n)
            break;
        printf("========================================================%s========================================================",players[t].name);
        printf("\n\nYou are %s.\nTi si %s.\n\n%s",players[t].role,players[t].role,players[t].description);
        printf("\n\nType a random button to if you are ready!\nNatisni sluchaen buton ako si gotov!");
        getch();}}

// ��������� �� �������
Beep(750, 600);
for(j=0;j<n;j++)
    {sleep=0;
    if(strcmp(players[j].role,"Kradec")==0)
        {printf("Kradec, wake up!\nKradec, susbudi se!\n\n");

        int recommended = recommend_role(&roles[indices[n]], 3, 0);
        printf("Choose one of the three cards in the middle!\nI suggest you to choose the card %s!\nIzberi si edna ot trite karti po sredata!\nPreporuchvam ti da izberesh kartata %s!",roles[indices[n+recommended]].name,roles[indices[n+recommended]].name);
        t=n;
        while(1)
            {for(i=n;i<n+3;i++)
                {if(t==i)
                    printf("%s<\n",roles[indices[i]].name);
                else
                    printf("%s\n",roles[indices[i]].name);}

            a=getch();

            if(a==13)
                break;

            if(a==224)
                {a=getch();
                if(a==72&&t>n)
                    t--;
                if(a==80&&t<n+2)
                    t++;}
            clear_last_lines(3);} // ������� ���������� 3 ����

        players[j].is_good=roles[indices[t]].is_good;
        strcpy(players[j].role, roles[indices[t]].name);
        strcpy(players[j].description, roles[indices[t]].description);
        strcpy(roles[indices[t]].name, "Kradec");

        printf("\n\n%s, you are now %s.\n%s, ti veche si %s.\n\n%s",players[j].name,players[j].role,players[j].name,players[j].role,players[j].description);
        printf("\n\nIf you are ready, type a random button to continue the game!\nAko si gotov natisni sluchaen buton za da produlzi igrata!");
        getch();
        break;}

    else
        sleep=1;}
if(sleep)
    {Sleep(20000);
    sleep=0;
    c=1;} // �� ���������� �� ������� ����� ��-����� ���� � ����� ������
system("cls");

// ��������� �� ������� �����
Role available[2];
k=0;
for(i=n;i<n+3;i++)
    {if(strcmp(roles[indices[i]].name,"Kradec")!=0) // ���������� ������� �� �������
        available[k++]=roles[indices[i]];}

Beep(750, 600);
for(j=0;j<n;j++)
    {sleep=0;
    if(strcmp(players[j].role,"Dvoen_agent")==0)
        {printf("Dvoen agent, wake up!\nDvoen agent, susbudi se!\n\n");

        int recommended = recommend_role(available,k,1);
        if(recommended==0)
            printf("Choose one of the two cards in the middle!\nI suggest you to choose Karta 1!\nIzberi si edna ot dvete karti po sredata!\nPreporuchvam ti da izberesh Karta 1!\n");
        else
            printf("Choose one of the two cards in the middle!\nI suggest you to choose Karta 2!\nIzberi si edna ot dvete karti po sredata!\nPreporuchvam ti da izberesh Karta 2!\n");
        t=0;
        while(1)
            {if(t==0)
                printf("Karta 1<\n");
            else
                printf("Karta 1\n");
            if(t==1)
                printf("Karta 2<\n");
            else
                printf("Karta 2\n");

            a=getch();

            if(a==13)
                break;

            if(a==224)
                {a=getch();
                if(a==72&&t>0)
                    t--;
                if(a==80&&t<1)
                    t++;}
            clear_last_lines(2);} // ������� ���������� 3 ����

        strcpy(players[j].role,available[t].name);
        strcpy(players[j].description,available[t].description);
        strcpy(players[j].role2,"Dvoen_agent");
        players[j].is_good=available[t].is_good;

        printf("\n\n%s, you are now %s.\n%s, ti veche si %s.\n\n%s",players[j].name,players[j].role,players[j].name,players[j].role,players[j].description);
        printf("The first time when you die I will reveal that you are Dvoen agent and you will survive!\nPurviq put kogato umresh, az shte razkriq, che ti si Dvoen agent i ti shte oceleesh!\n\n");
        if(c==0)
            printf("And you have the information that there was a Kradec!\nI ti imash informaciqta, che imashe Kradec!");
        else
            printf("And you have the information that there wasn't a Kradec!\nI ti imash informaciqta, che nqmashe Kradec!");
        printf("\n\nIf you are ready, type a random button to continue the game!\nAko si gotov natisni sluchaen buton za da produlzi igrata!");
        getch();
        break;}

    else
        sleep=1;}
if(sleep)
    {Sleep(20000);
    sleep=0;}

// ����� � ��� � ���, ����� ���������, ������ ������� ��� ������ �������!
while(1)
    {//���
    night_count=0; // ���� ���� �������� ������ �� ���������� ���
    wolf_victim_index=-1;
    wolf_victim_saved=0;

    //��������� �� ��������� � �������
    system("cls");
    Beep(750, 600);
    for(j=0;j<n;j++)
        {sleep=0;
        if((strcmp(players[j].role,"Glavatar")==0||strcmp(players[j].role,"Vulk")==0)&&players[j].is_alive==1)
            {printf("Vulci, wake up!\nVulci, subudete se!\n\n");
            printf("Choose one player that you want to kill.\nIzberete edin igrach, kojto iskate da ubiete");

            char remaining_players[n][max_br];
            b=0;
            for(k=0;k<n;k++)
                {if((strcmp(players[k].role,"Glavatar")!=0&&strcmp(players[k].role,"Vulk")!=0)&&players[k].is_alive==1)
                    strcpy(remaining_players[b++],players[k].name);}
            t=0;
            while(1)
                {for(i=0;i<b;i++)
                    {if(t==i)
                        printf("%s<\n",remaining_players[i]);
                    else
                        printf("%s\n",remaining_players[i]);}

                a=getch();

                if(a==13)
                    break;

                if(a==224)
                    {a=getch();
                    if(a==72&&t>0)
                        t--;
                    if(a==80&&t<b-1)
                        t++;}
                clear_last_lines(b);} // ������� ���������� 3 ����

            int chosen_index=-1;
            for(k=0;k<n;k++)
            {if(strcmp(players[k].name,remaining_players[t])==0)
                    chosen_index=k;}

            if(chosen_index!=-1)
                {night_victims[night_count++]=chosen_index;
                wolf_victim_index=chosen_index;}

            printf("\n\nYou made your choice!\nVie napravihte svoq izbor!\n\n");

            b=0;
            for(k=0;k<n;k++)
                {if((strcmp(players[k].role,"Glavatar")!=0 && strcmp(players[k].role,"Vulk")!=0) && (strcmp(players[k].name,players[t].name)!=0 && players[k].is_alive==1))
                    strcpy(remaining_players[b++],players[k].name);}
            if(b>0)
                {printf("Who do you think is the Bezsunnica?\nKoj mislite, che e Bezsunnicata?");
                t=0;
                while(1)
                    {for(i=0;i<b;i++)
                        {if(t==i)
                            printf("%s<\n",remaining_players[i]);
                        else
                            printf("%s\n",remaining_players[i]);}

                    a=getch();

                    if(a==13)
                        break;

                    if(a==224)
                        {a=getch();
                        if(a==72&&t>0)
                            t--;
                        if(a==80&&t<b-1)
                            t++;}
                    clear_last_lines(b);} // ������� ���������� 3 ����

                chosen_index=-1;
                for(k=0;k<n;k++)
                    {if(strcmp(players[k].name,remaining_players[t])==0)
                        chosen_index=k;}

                if(chosen_index!=-1 && strcmp(players[chosen_index].role,"Bezsunnica")==0)
                    night_victims[night_count++]=chosen_index;

                printf("\n\nYou made your choice!\nVie napravihte svoq izbor!\n\n");}

            printf("\n\nIf you are ready, type a random button to continue the game!\nAko ste gotovi natisnete sluchaen buton za da produlzi igrata!");
            getch();
            break;}

        else
            sleep=1;}
    if(sleep)
        {Sleep(20000);
        sleep=0;}

    // ��������� �� ��������
    system("cls");
    Beep(750, 600);
    for(j=0;j<n;j++)
        {sleep=0;
        if(strcmp(players[j].role,"Gadatel")==0 && players[j].is_alive==1)
            {printf("Gadatel, wake up!\nGadatel, subudi se!\n\n");
            printf("Choose one player to check if they are good, bad or Mazohist.\n");
            char remaining_players[n][max_br];
            b=0;
            for(k=0;k<n;k++)
                {if(players[k].is_alive==1 && k!=j) // ���� �� ����� ���� ����, ��� ���� ��
                    strcpy(remaining_players[b++],players[k].name);}

            t=0;
            while(1)
                {for(i=0;i<b;i++)
                    {if(t==i)
                        printf("%s<\n",remaining_players[i]);
                    else
                        printf("%s\n",remaining_players[i]);}

                a=getch();

                if(a==13)
                    break;

                if(a==224)
                    {a=getch();
                    if(a==72&&t>0)
                        t--;
                    if(a==80&&t<b-1)
                        t++;}

                clear_last_lines(b);}

            int chosen_index=-1;
            for(k=0;k<n;k++)
                {if(strcmp(players[k].name,remaining_players[t])==0)
                    chosen_index=k;}

            if(chosen_index!=-1)
                {if(players[chosen_index].is_good==SOLO)
                    printf("\n%s is the Mazohist!\n%s e Mazohist!\n",players[chosen_index].name,players[chosen_index].name);
                else
                    if(players[chosen_index].is_good==GOOD)
                        printf("\n%s is GOOD!\n%s e ot dobrite!\n",players[chosen_index].name,players[chosen_index].name);
                else
                    printf("\n%s is BAD!\n%s e ot loshite!\n",players[chosen_index].name,players[chosen_index].name);}

            printf("\n\nIf you are ready, type a random button to continue the game!\nAko si gotov natisni sluchaen buton za da produlzi igrata!");
            getch();
            break;}

        else
            sleep=1;}

    if(sleep)
        {Sleep(20000);
        sleep=0;}

    // ��������� �� ��������
    // �������� ����� ������ ��� � ������� ���������
    Beep(750,600);
    int lekar_count=0;
    int lekar_indices[2]={-1,-1};
    for(j=0;j<n;j++)
        {if(strcmp(players[j].role,"Lekar")==0 && players[j].is_alive==1)
            lekar_indices[lekar_count++]=j;}

    if(lekar_count>0)
        {system("cls");
        printf("Lekari, wake up!\nLekari, susbudete se!\n\n");
        printf("Choose one player who you want to save.\nIzberete edin igrach, kojto iskate da spasite.\n\n");

        char remaining_players[n][max_br];
        int b=0;
        for(k=0;k<n;k++)
            if(players[k].is_alive==1 && k!=skip)
                strcpy(remaining_players[b++],players[k].name);

        t=0;
        while(1)
            {for(i=0;i<b;i++)
                if(t==i)
                    printf("%s<\n",remaining_players[i]);
                else
                    printf("%s\n",remaining_players[i]);

            a=getch();

            if(a==13)
                break;

            if(a==224)
               {a=getch();
                if(a==72&&t>0)
                    t--;
                if(a==80&&t<b-1)
                    t++;}

            clear_last_lines(b);}

        int chosen_index=-1;
        for(k=0;k<n;k++)
            {if(strcmp(players[k].name,remaining_players[t])==0)
                chosen_index=k;}

        if(chosen_index!=-1)
            {int is_in_victims=0;
            for(i=0;i<night_count;i++)
                {if(night_victims[i]==chosen_index)
                    {is_in_victims=1;
                    break;}}

            if(is_in_victims)
                {night_victims[i]=night_victims[night_count-1]; // ������ �� night_victims
                night_count--;
                if(chosen_index==wolf_victim_index)
                    wolf_victim_saved=1;}

            skip=chosen_index;} // ���������� ��� �� ���� �� ����� �����

        printf("\n\nYou have chosen who to save!\nIzbrakhte kogo da spasite!\n");
        printf("\n\nIf you are ready, type a random button to continue the game!\nAko ste gotovi natisnete sluchaen buton za da produlzi igrata!");
        getch();}

    else
        Sleep(20000);

    // ��������� �� ������
    system("cls");
    Beep(750, 600);
    for(j=0;j<n;j++)
        {sleep=0;
        if(strcmp(players[j].role,"Ubiec")==0 && players[j].is_alive==1)
            {printf("Ubiec, wake up!\nUbiec, subudi se!\n\n");
            printf("Choose one player to try to kill.\nIzberi edin igrach, kojto iskash da ubiete.\n\n");

            char remaining_players[n][max_br];
            b=0;
            for(k=0;k<n;k++)
                {if(players[k].is_alive==1 && k!=j) // ������ ���� ��� ������
                    strcpy(remaining_players[b++],players[k].name);}

            t=0;
            while(1)
                {for(i=0;i<b;i++)
                    {if(t==i)
                        printf("%s<\n",remaining_players[i]);
                    else
                        printf("%s\n",remaining_players[i]);}

                a=getch();

                if(a==13)
                    break;

                if(a==224)
                    {a=getch();
                    if(a==72&&t>0)
                        t--;
                    if(a==80&&t<b-1)
                        t++;}

                clear_last_lines(b);}

            int chosen_index=-1;
            for(k=0;k<n;k++)
                {if(strcmp(players[k].name,remaining_players[t])==0)
                    chosen_index=k;}

            if(chosen_index!=-1 && wolf_victim_index!=-1)
                {if(wolf_victim_saved) // ������� � ������ �������� �� �������
                    {night_victims[night_count++]=chosen_index;
                        night_count--;}}

            printf("\n\nYou made your choice!\nVie napravihte svoq izbor!\n\n");

            printf("\n\nIf you are ready, type a random button to continue the game!\nAko si gotov natisni sluchaen buton za da produlzi igrata!");
            getch();
            break;}

        else
            sleep=1;}

    if(sleep)
        {Sleep(20000);
        sleep=0;}

    // ���
    Beep(750, 600);
    // ������� �� �������� �� ����
    for(i=0;i<night_count;i++)
        players[night_victims[i]].is_alive=0;

    players[skip].is_alive=1; //�������� �� ������, ����� ������� � ����� �� �����

    //���������� ��� �� ��������
    system("cls");

    if(night_count==0)
        printf("No one died during the night.\nNikoj ne umrq prez tazi nosht.\n\n");
    else
        {printf("The players, which died during the night are (umrelite igrachi sa):\n");
        for(i=0;i<night_count;i++)
            printf("- %s\n", players[night_victims[i]].name);}

    //�������� ���� ������ � ��������
    good=0; bad=0;
    for(i=0;i<n;i++)
        {if(players[i].is_alive==1 && players[i].is_good==GOOD)
            good++;
        else
            {if(players[i].is_alive==1 && players[i].is_good==BAD)
                bad++;}}
    if(good==0)
        {pobeda=BAD;
        break;}
    if(bad==0)
        {pobeda=GOOD;
        break;}}


    // �������� ���� � ����
    for(k=0;k<night_count;k++)
        {if(strcmp(players[night_victims[k]].role3,"Kmet")==0)
            {printf("%s was the Kmet and now he/she has to choose a new Kmet!\n%s beshe Kmet i sega toi/tq trqbva da izbere nov Kmet!\n\n",players[night_victims[k]].name,players[night_victims[k]].name);

            // ������ � ���� ������
            char kmet_targets[n][max_br];
            int kmet_targets_count=0;
            for(i=0;i<n;i++)
                if(players[i].is_alive==1)
                    strcpy(kmet_targets[kmet_targets_count++],players[i].name);
            t=0;
            while(1)
                {for(j=0;j<kmet_targets_count;j++)
                    {if(players[j].is_alive==1 && j!=night_victims[k])
                        {if(t==j)
                            printf("%s<\n",kmet_targets[j]);
                        else
                            printf("%s\n",kmet_targets[j]);}}

                a=getch();

                if(a==224)
                    {a=getch();
                    if(a==72&&t>0)
                        t--;
                    if(a==80&&t<kmet_targets_count-1)
                        t++;}

                if(a==13)
                    break;

                clear_last_lines(kmet_targets_count-1);}

                // �������� ������� �� ����� ����
                int new_kmet_index=-1;
                for(i=0;i<n;i++)
                    if(strcmp(players[i].name,kmet_targets[t])==0)
                        new_kmet_index=i;
                if(new_kmet_index!=-1)
                    {strcpy(players[new_kmet_index].role3,"Kmet");
                    printf("%s is now the new Kmet!\n%s e noviq Kmet!\n\n",players[new_kmet_index].name,players[new_kmet_index].name);}}

    //���������
    // ������ �� ���� � ��������� ������ � �����
    printf("Voting begins!\nDenqt zapochva: Glasuvaneto zapochva!\n\n");
    printf("\nThe Kmet is %s.\n\n%s\n\n", players[kmet_index].name, players[kmet_index].description3);

    // ������ � ���� ������
    char vote_targets[n][max_br];
    int alive_count=0;
    for(i=0;i<n;i++)
        if(players[i].is_alive==1)
            strcpy(vote_targets[alive_count++],players[i].name);

    // ����� �� ������ ���� ����
    t=0; // ����� �����
    while(1)
        {printf("Choose the player who was killed by voting.\nIzberete igracha, kojto ste ubili s glasuvane:\n");
        for(i=0;i<alive_count;i++)
            {if(t==i)
                printf("%s<\n",vote_targets[i]);
            else
            printf("%s\n",vote_targets[i]);}

        a=getch();

        if(a==224)
            {a=getch();
            if(a==72&&t>0)
                t--;
            if(a==80&&t<alive_count-1)
                t++;}

            if(a==13) // Enter
                break;

        clear_last_lines(alive_count);}

    // ���� ����� � ��������� �� ��������
    int chosen_index=-1;
    for(i=0;i<n;i++)
        if(strcmp(players[i].name,vote_targets[t])==0)
            chosen_index=i;

    if(chosen_index!=-1)
        {if(strcmp(players[chosen_index].role2,"Dvoen_agent")==0) // �������� �� ����� �����
            {printf("%s survives, because he/she was Dvoen agent!\n%s ocelqva, zashtoto toi/tq beshe Dvoen Agent!\n\n",players[chosen_index].name,players[chosen_index].name);
            strcpy(players[chosen_index].role2,"no_role2");}
        else
            {if(players[chosen_index].is_good==SOLO) // �������� �� ���������
                mazohist_index_pobeda=chosen_index;}

        // �������� ���� � ����
        if(strcmp(players[chosen_index].role3,"Kmet")==0)
            {printf("%s was the Kmet and now he/she has to choose a new Kmet!\n%s beshe Kmet i sega toi/tq trqbva da izbere nov Kmet!\n\n",players[chosen_index].name,players[chosen_index].name);
            // ������ � ���� ������
            char kmet_targets[n][max_br];
            int kmet_targets_count=0;
            for(i=0;i<n;i++)
                if(players[i].is_alive==1)
                    strcpy(kmet_targets[kmet_targets_count++],players[i].name);

            t=0;
            while(1)
                {for(j=0;j<kmet_targets_count;j++)

                    {if(players[j].is_alive==1 && j!=chosen_index)
                        {if(t==j)
                            printf("%s<\n",kmet_targets[j]);
                        else
                            printf("%s\n",kmet_targets[j]);}}

                a=getch();

                if(a==224)
                    {a=getch();
                    if(a==72&&t>0)
                        t--;
                    if(a==80&&t<kmet_targets_count-1)
                        t++;}

                if(a==13)
                    break;

                clear_last_lines(kmet_targets_count-1);}

                // �������� ������� �� ����� ����
                int new_kmet_index=-1;
                for(i=0;i<n;i++)
                    if(strcmp(players[i].name,kmet_targets[t])==0)
                        new_kmet_index=i;
                if(new_kmet_index!=-1)
                    {strcpy(players[new_kmet_index].role3,"Kmet");
                    printf("%s is now the new Kmet!\n%s e noviq Kmet!\n\n",players[new_kmet_index].name,players[new_kmet_index].name);}

            // ���������� �������
            players[chosen_index].is_alive=0;
            printf("%s died.\n%s umrq.\n\n",players[chosen_index].name,players[chosen_index].name);}}

    //�������� ���� ������ � ��������
    good=0; bad=0;
    for(i=0;i<n;i++)
        {if(players[i].is_alive==1 && players[i].is_good==GOOD)
            good++;
        else
            {if(players[i].is_alive==1 && players[i].is_good==BAD)
                bad++;}}
    if(good==0)
        {pobeda=BAD;
        break;}
    if(bad==0)
        {pobeda=GOOD;
        break;}

    printf("If you are ready type a random button and fell asleep!\nAko ste gotovi  natisnete sluchaen buton i zaspete!");
    getch();}

// ���� �� ������
printf("The game finished!\nIgrata prikluchi!\n\n");
switch(pobeda)
    {case GOOD: printf("The Village's team (the good team) won!\nOtborut na Seloto (dobriqt otbor) pobedi!\n\n"); break;
    case BAD: printf("The Vulcite's team (the bad team) won!\nOtborut na Vulcite (loshiqt otbor) pobedi!\n\n"); break;}

if(mazohist_index_pobeda)
    printf("And %s also won, because he was Mazohist and he died from voting!\nI %s sushto pobedi, zashtoto toi beshe Mazohist i umrq ot glasuvane!\n\n",players[mazohist_index_pobeda].name,players[mazohist_index_pobeda].name);

printf("I hope you enjoy the game!\nNadqvam se, che se se zabavlqvali po vreme na igrata!");}


void clear_last_lines(int n)
{int i;
for(i=0;i<n;i++)
    {printf("\033[A");  // ������� 1 ��� ������
    printf("\033[K");}}  // ������� ���� �� ������� �� ����



int recommend_role(Role *cards, int count, int is_double_agent)
{int p,i;
const char *priority_list[]= // ����������� ������
    {"Dvoen_agent", "Glavatar", "Vulk", "Gadatel", "Lekar",
        "Ubiec", "Mazohist", "Bezsunnica", "Selqnin"};

int priority_count = sizeof(priority_list)/sizeof(priority_list[0]);

// ������ �� ���� �� ����������
for(p=0;p<priority_count;p++)
    {if(is_double_agent && strcmp(priority_list[p], "Mazohist") == 0) // ��� � ����� �����, ���������� "Mazohist"
        continue;

    for(i=0;i<count;i++)
        {if (strcmp(cards[i].name, priority_list[p]) == 0)
            return i;}} // ����� ������� �� ������������� �����
return 0;}
