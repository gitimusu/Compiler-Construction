/*SymbolTable.c에서 사용할 함수 및 변수 정의*/

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

static int nextid = 0; //현재 identifier 위치
static int nextfree = 0; //다음 identifier가 올 위치 인덱스
static int hashcode; //identifier가 가질 해시코드
static int sameid; //이미 있는 identifier일 경우 첫 identifier의 인덱스 

static int found = 0; //이미 있는지 없는지 판단할 때 쓰이는 변수(있다면 1, 처음 온 것이라면 0)
static int error = 0; //각각의 에러를 판단할 때 쓰이는 변수 


//SymbolTable.c 함수들
void SkipSeperators();
void ReadID();
void ComputeHS(int nid, int nfree);
void LookupHS(int nid, int hscode);
void ADDHT(int hscode);
void PrintHStable();
void SymbolTable();