/*
 * @author     YJSoft(a.k.a. @yumeka_kameyu)
 * @License    GPL V3
 * @Disclaimer You should have received a copy of the GNU General Public License
 *             along with this program.  If not, see <http://www.gnu.org/licenses/>
 */

#include "simulator.h"
#include "list.h"

// 캐릭터 리스트를 담는 함수(동적할당) 
List *list;

char list_file[] = "list.txt";
char stat_file[] = "stat.txt";
char san_file[] = "san.txt";

// 스탯 계산에 사용하는 변수 
double stat[11] = {0.1, 0.2, 0.3, 0.45, 0.4, 0.5, 0.55, 0.6, 0.7, 0.8, 0.9};
double san[11] = {0.5, 0.4, 0.4, 0.4, 0.3, 0.2, 0.15, 0.15, 0.1, 0.1, 0};

int main(void) {
	int i, cnt;
	Charactor first = {"FIRST", -1, -1, -1, -1};
	Charactor second = {"SECOND", -1, -1, -1, -1};
	char tmp[51], yn = '\0';
	FILE *f;
	ListElmt *element;
	
	list = (List *)malloc(sizeof(List));
	list_init(list, free);
	
	// 출력 핸들을 가져와 저장한다
	// 콘솔 글자 색변경 등에 필요하다
	hC = GetStdHandle(STD_OUTPUT_HANDLE);
	
	// 특별 버전/일반 버전 분리 
	if(__EXCLUSIVE__==0) {
		//normal release
		sprintf(tmp,"TITLE Text Fight Simulator V %s",VER_STRING);
		system(tmp);
	} else {
		//if exclusive release,set special title
		sprintf(tmp,"TITLE Text Fight Simulator V %s for %s",VER_STRING,__COMMUNAME__);
		system(tmp);
	}
	
	// 캐릭터 데이터베이스를 불러온다
	if((f=fopen(list_file,"r")) == NULL) {
		// 파일이 없으면 생성시도
		if((f=fopen(list_file,"w")) == NULL) {
			// 생성조차 불가능하다면 리턴
			error("list.txt 파일을 열 수 없습니다!");
        
	        fclose(f);
	        system("pause");
	        
	        return 1;
		} else {
			// 철수, 영희 두 캐릭터를 기본으로 추가한다
			printf("캐릭터 데이터베이스가 생성되었습니다.\n");
			fprintf(f,"철수 20 8 7 7 1\n영희 20 7 9 6 1");
			fclose(f);
			f = fopen(list_file,"r");
		}
    }
    
    //캐릭터 데이터베이스를 불러온다
    cnt = load_list(f);
    fclose(f);
    
    load_stat(stat_file, stat);
    load_stat(san_file, san);
    
    printf("캐릭터 데이터베이스를 불러왔습니다.\n(총 캐릭터 %d명)\n\n", cnt);
	
	// 메인 루프 시작
	while(1) {
		print_header();
		
		first.hp = -1;
		second.hp = -1;
        
        // 캐릭터 이름 입력 시작
        while(1) {
        	while(1) {
	        	printf("첫번째 캐릭터의 이름을 입력하세요>");
	        	
	        	fflush(stdin);
		        gets(tmp);
		        replace_whitespace(tmp, 0);
				
				element = list_head(list);
				while(element != NULL) {
					if(strcmp(tmp, element->data->name) == 0) {
		        		first = *(element->data);
					}
					
					element = list_next(element);
				}
				
				if(first.hp != -1) {
					break;
				} else {
					printf("캐릭터를 등록할까요? (Y/N)>");
					
					fflush(stdin);
					scanf("%c", &yn);
					if(yn == 'N' || yn == 'n') continue;
					input_name(tmp, &first);
					
					break;
				}
			}
			
        	while(1) {
	        	printf("두번째 캐릭터의 이름을 입력하세요>");
	        	
	        	fflush(stdin);
		        gets(tmp);
		        replace_whitespace(tmp, 0);
		        
		        element = list_head(list);
				while(element != NULL) {
					if(strcmp(tmp, element->data->name) == 0) {
		        		second = *(element->data);
					}
					
					element = list_next(element);
				}
				
				if(second.hp != -1 && strcmp(first.name, second.name) != 0) {
					break;
				} else if(strcmp(first.name, second.name) == 0) {
					error("첫번째 캐릭터와 같을 수 없습니다!");
				} else {
					printf("캐릭터를 등록할까요? (Y/N)>");
					
					fflush(stdin);
					scanf("%c", &yn);
					if(yn == 'N' || yn == 'n') continue;
					input_name(tmp, &second);
					
					break;
				}
			}
			
			replace_whitespace(first.name, 1);
			replace_whitespace(second.name, 1);
			
			printf("\n");
			
			printf("첫번째 캐릭터 : %s\n(체력 %2d, 공격 %2d, 방어 %2d, 정신 %2d, 힘 %2d)\n\n", first.name, first.hp, first.atk, first.def, first.san, first.power);
			printf("두번째 캐릭터 : %s\n(체력 %2d, 공격 %2d, 방어 %2d, 정신 %2d, 힘 %2d)\n\n", second.name, second.hp, second.atk, second.def, second.san, second.power);
			
			printf("이 캐릭터들이 맞습니까? (Y/N)>");
			
			fflush(stdin);
			scanf("%c", &yn);
			
			if(yn == 'N' || yn == 'n') continue;
			break;
		}
		// 캐릭터 이름 입력 끝
		
		// 50% 확률로 캐릭터 1과 2 서로 교환
		if(X_prob(0.5)) {
			Charactor temp;
			temp = first;
			first = second;
			second = temp;
		} 
		
		while(1) {
			first.confused = 0;
			second.confused = 0;
			
			// 선공 차례
			fight(&first, &second);
			printf("%s HP:%d / %s HP:%d\n\n", first.name, first.hp, second.name, second.hp);
			
			// 방어 쓰러짐
			if(second.hp <= 0) {
				printf("%s(이)가 쓰러졌다!\n",second.name);
				printf("%s의 승리!\n",first.name);
				
				break;
			}
			
			// 방어 차례
			fight(&second, &first);
			printf("%s HP:%d / %s HP:%d\n\n", first.name, first.hp, second.name, second.hp);
			
			//선공 쓰러짐
			if(first.hp <= 0) {
				printf("%s(이)가 쓰러졌다!\n",first.name);
				printf("%s의 승리!\n",second.name);
				
				break;
			}
		}
		
		
		printf("계속할까요? (Y/N)>");
		
		fflush(stdin);
		scanf("%c", &yn);
		
		if(yn == 'Y' || yn == 'y') continue;
		break;
	}
	// 메인 루프 끝
	
	system("pause");
	
	return 0;
}

int load_list(FILE *f) {
	int       i = 0,
	          hp,
	          atk,
	          def,
	          san,
	          power;
	char      tmp[50];
	Charactor *data;
	ListElmt  *element;
	
	while(1) {
		// 캐릭터 데이터 저장용 메모리 할당
		if((data = (Charactor *)malloc(sizeof(Charactor))) == NULL) {
			return -1;
		}
		
		element = list_tail(list);
		
		// 파일에서 캐릭터 데이터베이스를 읽어온다
		// 파일은 반드시 지정된 형식이여야 한다 
		if(fscanf(f,"%s %d %d %d %d %d",&tmp,&hp,&atk,&def,&san,&power) == EOF) break;
		
		// 입력값 범위 검증 
		cap_range(&hp, 1, INT_MAX);
		cap_range(&atk, 0, 10);
		cap_range(&def, 0, 10);
		cap_range(&san, 0, 10);
		cap_range(&power, 0, INT_MAX);
		
		strcpy(data->name,tmp);
		data->hp = hp;
		data->atk = atk;
		data->def = def;
		data->san = san;
		data->power = power;
		data->confused = 0;
		
		list_ins_next(list, element, data);
		
		i++;
	}
	
	return i;
}

int init_prob(double x) {
	return RAND_MAX * x >= rand();
}

int X_prob(double x) {
	int count;
	int array[100];
	srand(time(NULL));
	
	for(count = 0; count != 100; ++count) {
		array[count] = init_prob(x);
	}
	
	return(array[rand()%100]);
}

void error(char *str) {	
	SetConsoleTextAttribute(hC,12);
	printf("%s\n",str);
	SetConsoleTextAttribute(hC,15);
}

void print_header(void) {
	SetConsoleTextAttribute(hC,12);
	printf("Text ");
	SetConsoleTextAttribute(hC,11);
	printf("Fight ");
	SetConsoleTextAttribute(hC,14);
	printf("Simulator");
	SetConsoleTextAttribute(hC,15);
	printf(" V %s ",VER_STRING);
	
	//if exclusive release,show for ~~
	if(__EXCLUSIVE__==1) {
		printf("For ");
		SetConsoleTextAttribute(hC,10);
		printf("%s",__COMMUNAME__);
		SetConsoleTextAttribute(hC,15);
	}
	
	printf("\n\n");
}

int input_name(char *name, Charactor *data) {
	FILE *f;
	int hp, atk, def, san, power;
	
	if((f=fopen(list_file,"a")) == NULL) {
        error("list.txt 파일을 열 수 없습니다!");
        
        fclose(f);
        system("pause");
        
        return 1;
    }
    
    input_stat(&hp, "체력", 1, INT_MAX);
    input_stat(&atk, "공격력", 0, 10);
    input_stat(&def, "방어력", 0, 10);
    input_stat(&san, "정신력", 0, 10);
    input_stat(&power, "무기 공격력", 0, INT_MAX);
    
    strcpy(data->name,name);
    data->hp = hp;
    data->atk = atk;
    data->def = def;
    data->san = san;
    data->power = power;
    
    fprintf(f,"\n%s %d %d %d %d %d",name, hp, atk, def, san, power);
    fclose(f);
}

void fight(Charactor *first, Charactor *second) {
	int damage = 0;
	 
	// 선공 공격 
	if(X_prob(san[first->san])) {
		printf("%s(이)가 혼란에 빠졌다!\n",first->name);
		first->confused = 1;
	} 
	if(X_prob(stat[first->atk])) {
		// 선공 공격 성공
		if(X_prob(stat[second->def])) {
			// 선공 공격 성공이지만 방어 방어 성공
			damage = first->atk - (second->def / 2) + first->power;
			if(first->confused) damage /= 2;
			if(damage > 0) printf("%s의 공격! 막혔지만 %s에게 %d의 데미지를 입혔다!\n", first->name, second->name, damage);
			else printf("%s의 공격! 하지만 %s에겐 효과가 없었다!\n", first->name, second->name);
		} else {
			damage = first->atk + first->power;
			if(first->confused) damage /= 2;
			printf("%s의 공격! %s에게 %d의 데미지를 입혔다!\n", first->name, second->name, damage);
		}
	} else {
		// 선공 공격 실패 
		if(X_prob(stat[second->def])) {
			// 선공 공격 실패이면서 방어 방어는 성공 
			damage = first->power - second->def;
			if(first->confused) damage /= 3;
			else damage /= 2;
			if(damage > 0) printf("%s의 공격! 빗나갔지만 %s에게 %d의 데미지를 입혔다!\n", first->name, second->name, damage);
			else printf("%s의 공격! 완전히 빗나가 %s에겐 효과가 없었다!\n", first->name, second->name);
		} else {
			// 선공 공격도 방어 방어도 모두 실패 
			damage = first->power;
			if(first->confused) damage /= 3;
			else damage /= 2;
			printf("%s의 공격! 빗나갔지만 %s에게 %d의 데미지를 입혔다!\n", first->name, second->name, damage);
		}
	}
	if(damage < 0) damage = 0;
	second->hp -= damage;
}

void input_stat(int *stat, char *name, int min, int max) {
	char err[50];
	char yn;
	
	while(1) {
    	printf("%s 입력>", name);
	    fflush(stdin); 
	    scanf("%d",stat);
	    if(check_range(*stat, min, max)) {
	    	sprintf(err, "%s(은)는 0보다 커야 합니다!", name);
	    	error(err);
	    	continue;
		}
		/*
	    printf("%d, 맞습니까? (Y/N)>",*stat);
		
		fflush(stdin);
		scanf("%c", &yn);
		
		if(yn == 'Y' || yn == 'y') break;
		*/
	}
}

int check_range(int num, int min, int max) {
	if(num >= min && num <= max) return 0;
	else return 1;
}

int cap_range(int *num, int min, int max) {
	if(*num < min) *num = min;
	if(*num > max) *num = max;
}

void load_stat(char *filename, double *array) {
	int i;
	FILE *f;
	char err[50];
	
	if((f=fopen(filename,"r")) == NULL) {
		// 파일이 없으면 생성시도
		if((f=fopen(filename,"w")) == NULL) {
			// 생성조차 불가능하다면 리턴
			sprintf(err, "%s 파일을 생성할 수 없습니다!\n", filename);
	    	error(err);
	    	
	        fclose(f);
	        system("pause");
	        exit(1);
		} else {
			printf("스탯 데이터베이스 파일 %s가 생성되었습니다.\n", filename);
			for(i=0;i<11;i++) {
				fprintf(f,"%.2lf\r\n", san[i]);
			}
			fclose(f);
			f = fopen(filename,"r");
		}
	}
	
	for(i=0;i<11;i++) {
		fscanf(f,"%lf", array + i);
	}
	
	fclose(f);
}

void replace_whitespace(char *str, int reverse) {
	while(*str) {
		if(reverse == 0) {
			if(isspace((unsigned char) *str)) {
				*str='_';
			}
		} else {
			if(*str == '_') *str = ' ';
		}
		
		*str++;
	}
}
