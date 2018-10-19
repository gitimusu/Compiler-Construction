/*SymbolTable.c���� ����� �Լ� �� ���� ����*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STsize 1000
//#define STsize 30
#define HTsize 100

#define isLetter(x) ( ((x) >= 'a' && (x) <= 'z') || ((x) >= 'A' && (x) <= 'Z') || (x) == '_')
#define isDigit(x) ( (x) >= '0' && (x) <= '9' )

typedef struct HTentry *HTpointer;
typedef struct HTentry {
	int index;
	HTpointer next;
}HTentry;

HTpointer HT[HTsize];
char ST[STsize];

static int nextid = 0; //���� identifier ��ġ
static int nextfree = 0; //���� identifier�� �� ��ġ �ε���
static int hashcode; //identifier�� ���� �ؽ��ڵ�
static int sameid; //�̹� �ִ� identifier�� ��� ù identifier�� �ε��� 

static int found = 0; //�̹� �ִ��� ������ �Ǵ��� �� ���̴� ����(�ִٸ� 1, ó�� �� ���̶�� 0)
static int error = 0; //������ ������ �Ǵ��� �� ���̴� ���� 


//SymbolTable.c �Լ���
void SkipSeperators();
void ReadID();
void ComputeHS(int nid, int nfree);
void LookupHS(int nid, int hscode);
void ADDHT(int hscode);
void PrintHStable();
void SymbolTable();