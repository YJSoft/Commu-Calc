#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include "Header.h"

#define __DEBUG__ 0
#define __EXCLUSIVE__ 0
#define __COMMUNAME__ "Still Alive Community"
#define __RANDOM__ 1
#define LV1 3
#define LV2 4
#define LV3 5

int main()
{
    stat player={0,0,0,0};
    stat computer={0,0,0,0};
    char title[100];
    int temp;
    int success;
    int compare_val;
    int type; //1-선공 2-방어 3-정신력 
    int continue_val=1;
    int i=0;
    FILE *f;
    
    unsigned count;
    
    HANDLE hC = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hC,&csbi);
    COLORREF a;
    
    if(__EXCLUSIVE__==0){
         system("TITLE ATK/DEF/SAN Calculator");
    }
    //if exclusive release,set special title
    else{
         sprintf(title,"TITLE ATK/DEF/SAN Calculator for %s",__COMMUNAME__);
         system(title);
    }
    while(continue_val==1){
        SetConsoleTextAttribute(hC,12+160);
        printf("Program by 유메카(@commu_yumeka or @sanekata_)\n");
        SetConsoleTextAttribute(hC,12);
        printf("ATK");
        SetConsoleTextAttribute(hC,15);
        printf("/");
        SetConsoleTextAttribute(hC,11);
        printf("DEF");
        SetConsoleTextAttribute(hC,15);
        printf("/");
        SetConsoleTextAttribute(hC,14);
        printf("SAN");
        SetConsoleTextAttribute(hC,15);
        printf(" Calculator\n");
        
        //if exclusive release,show for ~~
        if(__EXCLUSIVE__==1){
            printf("For ");
            SetConsoleTextAttribute(hC,10);
            printf("%s\n",__COMMUNAME__);
            SetConsoleTextAttribute(hC,15);
        }
        
        if((f=fopen("stat.txt","r")) == NULL)
        {
            SetConsoleTextAttribute(hC,12);
            printf("stat.txt 파일을 열 수 없습니다!\n");
            SetConsoleTextAttribute(hC,15);
            fclose(f);
            system("pause");
            exit(1);
        }
        fclose(f);
        
        if((f=fopen("san.txt","r")) == NULL)
        {
            SetConsoleTextAttribute(hC,12);
            printf("san.txt 파일을 열 수 없습니다!\n");
            SetConsoleTextAttribute(hC,15);
            fclose(f);
            system("pause");
            exit(1);
        }
        
        fclose(f);
        success=0;
        type=0;
        temp=0;
        compare_val=0; 
        
        printf("플레이어의 ");
        SetConsoleTextAttribute(hC,12);
        printf("공격력");
        SetConsoleTextAttribute(hC,15);
        printf(" 입력>");
        scanf("%d",&temp);
        player.atk=temp;
        printf("플레이어의 ");
        SetConsoleTextAttribute(hC,11);
        printf("방어력");
        SetConsoleTextAttribute(hC,15);
        printf(" 입력>");
        scanf("%d",&temp);
        player.def=temp;
        printf("플레이어의 ");
        SetConsoleTextAttribute(hC,14);
        printf("정신력");
        SetConsoleTextAttribute(hC,15);
        printf(" 입력>");
        scanf("%d",&temp);
        player.san=temp;
        
        if(__RANDOM__==0){
            printf("공격/방어 선택(1-공격,2-방어,이외 방어)>");
            scanf("%d",&temp); 
        }
        if(__RANDOM__==1){
            player.dice=random_val(1,6);
            printf("컴퓨터 레벨 입력(1,2,3)\n레벨 1-최대값 3\n레벨 2-최대값 4\n레벨 3-최대값 5\n>");
            scanf("%d",&temp);
            
            switch(temp){
            case 1:
                 computer.atk = random_val(1,LV1);
                 computer.def = random_val(1,LV1);
                 computer.san = random_val(1,LV1);
                 computer.dice=random_val(1,LV1);
                 break;
            case 2:
                 computer.atk = random_val(1,LV2);
                 computer.def = random_val(1,LV2);
                 computer.san = random_val(1,LV2);
                 computer.dice=random_val(1,LV2);
                 break;
            case 3:
                 computer.atk = random_val(1,LV3);
                 computer.def = random_val(1,LV3);
                 computer.san = random_val(1,LV3);
                 computer.dice=random_val(1,LV3);
                 break;
            }
            if(player.dice>=computer.dice) temp=1;
            else temp=2;
        }
        
        if(temp==1)
        {
             compare_val = player.atk;
             type=1;
        }
        else
        {
             compare_val = player.def;
             type=2;
        }
        //debug
        if(__DEBUG__==1) printf("now comparing stat\n");
        success = compare_stat(compare_val);
        if(__DEBUG__==1) printf("now comparing san\n");
        if(compare_san(player.san)==1)
        {
            success=0;
            type=3;
        }
        //if(__DEBUG__==1) system("pause");
        //if(__DEBUG__==0) system("cls");
        //printf("ATK/DEF/SAN Calculator\nFor %s\n",__COMMUNAME__);
        
        switch(type)
        {
            case 1:
                 //선공
                 if(success==1) printf("플레이어의 공격! 공격은 매우 효과적이였다.\n");
                 else printf("플레이어의 공격! 하지만 공격은 실패했다!\n");
                 break;
            case 2:
                 //방어 
                 if(success==1) printf("컴퓨터의 공격! 성공적으로 방어했다\n");
                 else printf("컴퓨터의 공격! 방어에 실패해 공격받고 말았다...\n");
                 break;
            case 3:
                 //쫄았냐? 
                 printf("컴퓨터의 모습에 그만 얼어 붙어 버렸다...\n컴퓨터에게 공격을 받았다!\n");
                 break;
        }
        
        
        //printf("계속 하려면 아무 키나 눌러주세요>");
        system("pause");
        system("cls"); 
        //scanf("%d",&continue_val);
    }
}
// 공격력/방어력 비교용 함수 
int compare_stat(int stat)
{
    HANDLE hC = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hC,&csbi);
     int i;
     FILE *f;
     double statdata[11];
     if((f=fopen("stat.txt","r")) == NULL)
     {
          SetConsoleTextAttribute(hC,12);
          printf("stat.txt 파일을 열 수 없습니다!\n");
          SetConsoleTextAttribute(hC,15);
          fclose(f);
          system("pause");
          exit(1);
     }
     if(__DEBUG__==1) printf("stat.txt:");
     for(i=0;i<11;i++)
     {
          fscanf(f,"%lf",&statdata[i]);
          if(__DEBUG__==1) printf("%.2lf, ",statdata[i]);
     }
     if(__DEBUG__==1) printf("\n");
     
     fclose(f);
     
     return X_prob(statdata[stat]);
}
// 정신력 비교용 함수 
int compare_san(int stat)
{
    HANDLE hC = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hC,&csbi);
     int i;
     FILE *f;
     double sandata[11];
     if((f=fopen("san.txt","r")) == NULL)
     {
          SetConsoleTextAttribute(hC,12);
          printf("san.txt 파일을 열 수 없습니다!");
          SetConsoleTextAttribute(hC,15);
          fclose(f);
          system("pause");
          exit(1);
     }
     if(__DEBUG__==1) printf("san.txt:");
     for(i=0;i<11;i++)
     {
          fscanf(f,"%lf",&sandata[i]);
          if(__DEBUG__==1) printf("%.2lf, ",sandata[i]);
     }
     if(__DEBUG__==1) printf("\n");
     
     fclose(f);
     
     return X_prob(sandata[stat]);
}

int random_val(int min,int max)
{
    srand(time(NULL));
    return (rand() % max) + min;
}

int init_prob(double x)
{
   return RAND_MAX * x >= rand();
}

int X_prob(double x)
{
    int count;
    int array[100];
    srand(time(NULL));
    
    //debug
    if(__DEBUG__==1) printf("array:");
    for (count = 0; count != 100; ++count) {
        array[count] = init_prob(x);
        //debug
        if(__DEBUG__==1) printf("%d",array[count]);
    }
    if(__DEBUG__==1) printf("\n");
    
    return(array[rand()%100]);
}
