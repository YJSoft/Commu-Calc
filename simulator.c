/*
 * @author     YJSoft(a.k.a. @yumeka_kameyu)
 * @License    GPL V3
 * @Disclaimer You should have received a copy of the GNU General Public License
 *             along with this program.  If not, see <http://www.gnu.org/licenses/>
 */

#include "simulator.h"
#include "list.h"

// ĳ���� ����Ʈ�� ��� �Լ�(�����Ҵ�) 
List *list;

char list_file[] = "list.txt";
char stat_file[] = "stat.txt";
char san_file[] = "san.txt";

// ���� ��꿡 ����ϴ� ���� 
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
	
	// ��� �ڵ��� ������ �����Ѵ�
	// �ܼ� ���� ������ � �ʿ��ϴ�
	hC = GetStdHandle(STD_OUTPUT_HANDLE);
	
	// Ư�� ����/�Ϲ� ���� �и� 
	if(__EXCLUSIVE__==0) {
		//normal release
		sprintf(tmp,"TITLE Text Fight Simulator V %s",VER_STRING);
		system(tmp);
	} else {
		//if exclusive release,set special title
		sprintf(tmp,"TITLE Text Fight Simulator V %s for %s",VER_STRING,__COMMUNAME__);
		system(tmp);
	}
	
	// ĳ���� �����ͺ��̽��� �ҷ��´�
	if((f=fopen(list_file,"r")) == NULL) {
		// ������ ������ �����õ�
		if((f=fopen(list_file,"w")) == NULL) {
			// �������� �Ұ����ϴٸ� ����
			error("list.txt ������ �� �� �����ϴ�!");
        
	        fclose(f);
	        system("pause");
	        
	        return 1;
		} else {
			// ö��, ���� �� ĳ���͸� �⺻���� �߰��Ѵ�
			printf("ĳ���� �����ͺ��̽��� �����Ǿ����ϴ�.\n");
			fprintf(f,"ö�� 20 8 7 7 1\n���� 20 7 9 6 1");
			fclose(f);
			f = fopen(list_file,"r");
		}
    }
    
    //ĳ���� �����ͺ��̽��� �ҷ��´�
    cnt = load_list(f);
    fclose(f);
    
    load_stat(stat_file, stat);
    load_stat(san_file, san);
    
    printf("ĳ���� �����ͺ��̽��� �ҷ��Խ��ϴ�.\n(�� ĳ���� %d��)\n\n", cnt);
	
	// ���� ���� ����
	while(1) {
		print_header();
		
		first.hp = -1;
		second.hp = -1;
        
        // ĳ���� �̸� �Է� ����
        while(1) {
        	while(1) {
	        	printf("ù��° ĳ������ �̸��� �Է��ϼ���>");
	        	
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
					printf("ĳ���͸� ����ұ��? (Y/N)>");
					
					fflush(stdin);
					scanf("%c", &yn);
					if(yn == 'N' || yn == 'n') continue;
					input_name(tmp, &first);
					
					break;
				}
			}
			
        	while(1) {
	        	printf("�ι�° ĳ������ �̸��� �Է��ϼ���>");
	        	
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
					error("ù��° ĳ���Ϳ� ���� �� �����ϴ�!");
				} else {
					printf("ĳ���͸� ����ұ��? (Y/N)>");
					
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
			
			printf("ù��° ĳ���� : %s\n(ü�� %2d, ���� %2d, ��� %2d, ���� %2d, �� %2d)\n\n", first.name, first.hp, first.atk, first.def, first.san, first.power);
			printf("�ι�° ĳ���� : %s\n(ü�� %2d, ���� %2d, ��� %2d, ���� %2d, �� %2d)\n\n", second.name, second.hp, second.atk, second.def, second.san, second.power);
			
			printf("�� ĳ���͵��� �½��ϱ�? (Y/N)>");
			
			fflush(stdin);
			scanf("%c", &yn);
			
			if(yn == 'N' || yn == 'n') continue;
			break;
		}
		// ĳ���� �̸� �Է� ��
		
		// 50% Ȯ���� ĳ���� 1�� 2 ���� ��ȯ
		if(X_prob(0.5)) {
			Charactor temp;
			temp = first;
			first = second;
			second = temp;
		} 
		
		while(1) {
			first.confused = 0;
			second.confused = 0;
			
			// ���� ����
			fight(&first, &second);
			printf("%s HP:%d / %s HP:%d\n\n", first.name, first.hp, second.name, second.hp);
			
			// ��� ������
			if(second.hp <= 0) {
				printf("%s(��)�� ��������!\n",second.name);
				printf("%s�� �¸�!\n",first.name);
				
				break;
			}
			
			// ��� ����
			fight(&second, &first);
			printf("%s HP:%d / %s HP:%d\n\n", first.name, first.hp, second.name, second.hp);
			
			//���� ������
			if(first.hp <= 0) {
				printf("%s(��)�� ��������!\n",first.name);
				printf("%s�� �¸�!\n",second.name);
				
				break;
			}
		}
		
		
		printf("����ұ��? (Y/N)>");
		
		fflush(stdin);
		scanf("%c", &yn);
		
		if(yn == 'Y' || yn == 'y') continue;
		break;
	}
	// ���� ���� ��
	
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
		// ĳ���� ������ ����� �޸� �Ҵ�
		if((data = (Charactor *)malloc(sizeof(Charactor))) == NULL) {
			return -1;
		}
		
		element = list_tail(list);
		
		// ���Ͽ��� ĳ���� �����ͺ��̽��� �о�´�
		// ������ �ݵ�� ������ �����̿��� �Ѵ� 
		if(fscanf(f,"%s %d %d %d %d %d",&tmp,&hp,&atk,&def,&san,&power) == EOF) break;
		
		// �Է°� ���� ���� 
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
        error("list.txt ������ �� �� �����ϴ�!");
        
        fclose(f);
        system("pause");
        
        return 1;
    }
    
    input_stat(&hp, "ü��", 1, INT_MAX);
    input_stat(&atk, "���ݷ�", 0, 10);
    input_stat(&def, "����", 0, 10);
    input_stat(&san, "���ŷ�", 0, 10);
    input_stat(&power, "���� ���ݷ�", 0, INT_MAX);
    
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
	 
	// ���� ���� 
	if(X_prob(san[first->san])) {
		printf("%s(��)�� ȥ���� ������!\n",first->name);
		first->confused = 1;
	} 
	if(X_prob(stat[first->atk])) {
		// ���� ���� ����
		if(X_prob(stat[second->def])) {
			// ���� ���� ���������� ��� ��� ����
			damage = first->atk - (second->def / 2) + first->power;
			if(first->confused) damage /= 2;
			if(damage > 0) printf("%s�� ����! �������� %s���� %d�� �������� ������!\n", first->name, second->name, damage);
			else printf("%s�� ����! ������ %s���� ȿ���� ������!\n", first->name, second->name);
		} else {
			damage = first->atk + first->power;
			if(first->confused) damage /= 2;
			printf("%s�� ����! %s���� %d�� �������� ������!\n", first->name, second->name, damage);
		}
	} else {
		// ���� ���� ���� 
		if(X_prob(stat[second->def])) {
			// ���� ���� �����̸鼭 ��� ���� ���� 
			damage = first->power - second->def;
			if(first->confused) damage /= 3;
			else damage /= 2;
			if(damage > 0) printf("%s�� ����! ���������� %s���� %d�� �������� ������!\n", first->name, second->name, damage);
			else printf("%s�� ����! ������ ������ %s���� ȿ���� ������!\n", first->name, second->name);
		} else {
			// ���� ���ݵ� ��� �� ��� ���� 
			damage = first->power;
			if(first->confused) damage /= 3;
			else damage /= 2;
			printf("%s�� ����! ���������� %s���� %d�� �������� ������!\n", first->name, second->name, damage);
		}
	}
	if(damage < 0) damage = 0;
	second->hp -= damage;
}

void input_stat(int *stat, char *name, int min, int max) {
	char err[50];
	char yn;
	
	while(1) {
    	printf("%s �Է�>", name);
	    fflush(stdin); 
	    scanf("%d",stat);
	    if(check_range(*stat, min, max)) {
	    	sprintf(err, "%s(��)�� 0���� Ŀ�� �մϴ�!", name);
	    	error(err);
	    	continue;
		}
		/*
	    printf("%d, �½��ϱ�? (Y/N)>",*stat);
		
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
		// ������ ������ �����õ�
		if((f=fopen(filename,"w")) == NULL) {
			// �������� �Ұ����ϴٸ� ����
			sprintf(err, "%s ������ ������ �� �����ϴ�!\n", filename);
	    	error(err);
	    	
	        fclose(f);
	        system("pause");
	        exit(1);
		} else {
			printf("���� �����ͺ��̽� ���� %s�� �����Ǿ����ϴ�.\n", filename);
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
