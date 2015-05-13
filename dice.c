/*
 * @author YJSoft(Yumeka)
 * @License GPL V3
 * @Disclaimer You should not remove any "Made by" string.
 *             �ҽ��ڵ� ���� "Made by" ���ڿ��� ���� �����Ͻ� �� �����ϴ�.
 *             You should have received a copy of the GNU General Public License
 *             along with this program.  If not, see <http://www.gnu.org/licenses/>
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include "Header.h"
//you can translate this program with language.h file.(not yet ready)
#include "language.h"

#define __EXCLUSIVE__ 0
#define __COMMUNAME__ "(Community Name Here)"
#define __PROGRAM_VERSION__ "0.2.1"
#define LV1 3
#define LV2 4
#define LV3 5
int isDebug,isRandom;

int main(int argc, char* argv[])
{
    stat player={0,0,0,0};
    stat computer={0,0,0,0};
    char title[100];
    char stat_tmp1[10];
    char stat_tmp2[10];
    char stat_tmp3[10];
    char stat_tmp4[10];
    int temp,success,compare_val,type; //1-���� 2-��� 3-���ŷ� 
    int continue_val=1,i=0;
    FILE *f;
    
    unsigned count;
    
    HANDLE hC = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hC,&csbi);
    COLORREF a;
    
    isDebug=0;
    isRandom=2;
    for(i = 1; i < argc; i++)
    {
        if(strcmp(argv[i],"/h")==0){
            printHelp();
            exit(1);
        }
        if(strcmp(argv[i],"/d")==0) isDebug=1;
        if(strcmp(argv[i],"/r")==0){
            if(isRandom!=2)
            {
                SetConsoleTextAttribute(hC,12);
                printf("ERROR : /r�� /n�� ����� �� �����ϴ�.\n\n"); 
                SetConsoleTextAttribute(hC,15);
                printHelp();
                exit(1);
            }
            else
            {
                isRandom=1;
            }
        }
        if(strcmp(argv[i],"/n")==0){
            if(isRandom!=2)
            {
                SetConsoleTextAttribute(hC,12);
                printf("ERROR : /r�� /n�� ����� �� �����ϴ�.\n\n"); 
                SetConsoleTextAttribute(hC,15);
                printHelp();
                exit(1);
            }
            else
            {
                isRandom=0;
            }
        }
    }
    
    if(__EXCLUSIVE__==0){
         sprintf(title,"TITLE ATK/DEF/SAN Calculator V %s",__PROGRAM_VERSION__);
         system(title);
    }
    //if exclusive release,set special title
    else{
         sprintf(title,"TITLE ATK/DEF/SAN Calculator V %s for %s",__PROGRAM_VERSION__,__COMMUNAME__);
         system(title);
    }
    while(continue_val==1){
        //�Ʒ� ������ �����Ǿ�� �ȵ˴ϴ�. 
        SetConsoleTextAttribute(hC,12+160);
        printf("Program by ����ī(@commu_yumeka or @sanekata_)\n");
        
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
        printf(" Calculator V %s\n",__PROGRAM_VERSION__);
        
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
            printf("stat.txt ������ �� �� �����ϴ�!\n");
            SetConsoleTextAttribute(hC,15);
            fclose(f);
            system("pause");
            exit(1);
        }
        fclose(f);
        
        if((f=fopen("san.txt","r")) == NULL)
        {
            SetConsoleTextAttribute(hC,12);
            printf("san.txt ������ �� �� �����ϴ�!\n");
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
        if(isRandom==2){
            do{
            printf("���� ����/��� ���� 0,\n����/��� ���� ���� 1�� �Է����ּ���.\n>");
            fgets(stat_tmp1, 2, stdin);
            sscanf(stat_tmp1, "%d",&temp);
            getchar();
            }while(temp<0||temp>1);
            isRandom=temp;
            temp=0;
        }
        do{
        printf("�÷��̾��� ");
        SetConsoleTextAttribute(hC,12);
        printf("���ݷ�");
        SetConsoleTextAttribute(hC,15);
        printf(" �Է�>");
        fgets(stat_tmp1, 2, stdin);
        sscanf(stat_tmp1, "%d",&temp);
        getchar();
        if(isDebug==1) printf("stat : %d ( %s )\n",temp,stat_tmp1);
        }while(temp<1||temp>11);
        player.atk=temp;
        temp=0;
        do{
        printf("�÷��̾��� ");
        SetConsoleTextAttribute(hC,11);
        printf("����");
        SetConsoleTextAttribute(hC,15);
        printf(" �Է�>");
        fgets(stat_tmp2, 2, stdin);
        sscanf(stat_tmp2, "%d",&temp);
        getchar();
        if(isDebug==1) printf("stat : %d ( %s )\n",temp,stat_tmp2);
        }while(temp<1||temp>11);
        player.def=temp;
        temp=0;
        do{
        printf("�÷��̾��� ");
        SetConsoleTextAttribute(hC,14);
        printf("���ŷ�");
        SetConsoleTextAttribute(hC,15);
        printf(" �Է�>");
        fgets(stat_tmp3, 2, stdin);
        sscanf(stat_tmp3, "%d",&temp);
        getchar();
        if(isDebug==1) printf("stat : %d ( %s )\n",temp,stat_tmp3);
        }while(temp<1||temp>11);
        player.san=temp;
        temp=0;
        
        if(isRandom==0){
            do{
            printf("����/��� ����(1-����,2-���)>");
            fgets(stat_tmp4, 2, stdin);
            sscanf(stat_tmp4, "%d",&temp);
            getchar();
            }while(temp<1||temp>3);
        }
        if(isRandom==1){
            player.dice=random_val(1,6);
            do{
            printf("��ǻ�� ���� �Է�(1,2,3)\n���� 1-�ִ밪 3\n���� 2-�ִ밪 4\n���� 3-�ִ밪 5\n>");
            fgets(stat_tmp4, 2, stdin);
            sscanf(stat_tmp4, "%d",&temp);
            getchar();
            }while(temp<1||temp>3);
            
            switch(temp){
            //��ǻ���� ����/���/���ŷ� ���� ����ϰ� ������ ������� �ʰ� �ֽ��ϴ�. 
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
        
        //���� 
        if(temp==1)
        {
             compare_val = player.atk;
             type=1;
        }
        //��� 
        else
        {
             compare_val = player.def;
             type=2;
        }
        //debug
        if(isDebug==1) printf("now comparing stat\n");
        success = compare_stat(compare_val);
        if(isDebug==1) printf("now comparing san\n");
        if(compare_san(player.san)==1)
        {
            success=0;
            type=3;
        }
        //if(isDebug==1) system("pause");
        //if(isDebug==0) system("cls");
        //printf("ATK/DEF/SAN Calculator\nFor %s\n",__COMMUNAME__);
        
        switch(type)
        {
            case 1:
                 //����
                 if(success==1) printf("�÷��̾��� ����! ������ �ſ� ȿ�����̿���.\n");
                 else printf("�÷��̾��� ����! ������ ������ �����ߴ�!\n");
                 break;
            case 2:
                 //��� 
                 if(success==1) printf("��ǻ���� ����! ���������� ����ߴ�\n");
                 else printf("��ǻ���� ����! �� ������ ���ݹް� ���Ҵ�...\n");
                 break;
            case 3:
                 //�̾ҳ�? 
                 printf("��ǻ���� ����� �׸� ��� �پ� ���ȴ�...\n��ǻ�Ϳ��� ������ �޾Ҵ�!\n");
                 break;
        }
        
        
        //printf("��� �Ϸ��� �ƹ� Ű�� �����ּ���>");
        system("pause");
        system("cls"); 
        //scanf("%d",&continue_val);
    }
}
// ���ݷ�/���� �񱳿� �Լ� 
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
          printf("stat.txt ������ �� �� �����ϴ�!\n");
          SetConsoleTextAttribute(hC,15);
          fclose(f);
          system("pause");
          exit(1);
     }
     if(isDebug==1) printf("stat.txt:");
     for(i=0;i<11;i++)
     {
          fscanf(f,"%lf",&statdata[i]);
          if(isDebug==1) printf("%.2lf, ",statdata[i]);
     }
     if(isDebug==1) printf("\n");
     
     fclose(f);
     
     return X_prob(statdata[stat]);
}
// ���ŷ� �񱳿� �Լ� 
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
          printf("san.txt ������ �� �� �����ϴ�!");
          SetConsoleTextAttribute(hC,15);
          fclose(f);
          system("pause");
          exit(1);
     }
     if(isDebug==1) printf("san.txt:");
     for(i=0;i<11;i++)
     {
          fscanf(f,"%lf",&sandata[i]);
          if(isDebug==1) printf("%.2lf, ",sandata[i]);
     }
     if(isDebug==1) printf("\n");
     
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
    if(isDebug==1) printf("array:");
    for (count = 0; count != 100; ++count) {
        array[count] = init_prob(x);
        //debug
        if(isDebug==1) printf("%d",array[count]);
    }
    if(isDebug==1) printf("\n");
    
    return(array[rand()%100]);
}

void printHelp()
{
    HANDLE hC = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hC,&csbi);
    SetConsoleTextAttribute(hC,12+160);
    printf("Program by ����ī(@commu_yumeka or @sanekata_)\n");
    
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
    printf(" Calculator V %s\n",__PROGRAM_VERSION__);
    
    //if exclusive release,show for ~~
    if(__EXCLUSIVE__==1){
        printf("For ");
        SetConsoleTextAttribute(hC,10);
        printf("%s\n\n",__COMMUNAME__);
        SetConsoleTextAttribute(hC,15);
    }
    
    printf("\n��� ������ ���α׷� �μ�\n========================\n\n");
    printf("/r - ���� ����/��� ��带 Ȱ��ȭ�մϴ�.(/n�� ���� ����� �� ����)\n");
    printf("/n - ����/��� ���� ��带 Ȱ��ȭ�մϴ�.(/r�� ���� ����� �� ����)\n");
    printf("/d - ����� ��带 Ȱ��ȭ�մϴ�.\n\n");
    system("PAUSE");
}
