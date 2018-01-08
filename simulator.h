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

// �ܼ� ���� ���濡 ����ϴ� �ڵ� 
HANDLE hC;

// �÷��̾� �����ͺ��̽� �ε� �Լ� 
int load_list(FILE *);

// Ȯ�� ���� �Լ� 
int init_prob(double);

// �Է��� Ȯ����� 0 Ȥ�� 1 ��ȯ 
int X_prob(double);

// ������ ���� �۾��� ������ִ� �Լ� 
void error(char *);

// ����� ������ִ� �Լ� 
void print_header(void);

// �÷��̾� �����ͺ��̽� �߰� �Լ� 
int input_name(char *, Charactor *);

// ���� ó�� �Լ� 
void fight(Charactor *, Charactor *);

// ���� �Է� ó�� �Լ� 
void input_stat(int *, char *, int, int);

// ���� ������ ���� üũ 
int check_range(int, int, int); 

// ���� ������ ���� üũ�� ���������� ���� 
int cap_range(int *, int, int);

void load_stat(char *filename, double *array);

void replace_whitespace(char *, int);
