#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include <string.h>
#include "TextFightSimulator_private.h"

#define __EXCLUSIVE__ 0
#define __COMMUNAME__ "Achromatic Closer Community"

typedef struct {
	char name[51];
	int hp; 
	int atk;
	int def;
	int san;
	int power;
	int confused;
} Charactor;

// 콘솔 색상 변경에 사용하는 핸들 
HANDLE hC;

// 플레이어 데이터베이스 로드 함수 
int load_list(FILE *);

// 확률 계산용 함수 
int init_prob(double);

// 입력한 확률대로 0 혹은 1 반환 
int X_prob(double);

// 오류를 붉은 글씨로 출력해주는 함수 
void error(char *);

// 헤더를 출력해주는 함수 
void print_header(void);

// 플레이어 데이터베이스 추가 함수 
int input_name(char *, Charactor *);

// 전투 처리 함수 
void fight(Charactor *, Charactor *);

// 스탯 입력 처리 함수 
void input_stat(int *, char *, int, int);

// 정수 범위안 여부 체크 
int check_range(int, int, int); 

// 정수 범위안 여부 체크후 범위안으로 제한 
int cap_range(int *, int, int);

void load_stat(char *filename, double *array);

void replace_whitespace(char *, int);
