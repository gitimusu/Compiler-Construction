# Compiler-Construction

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "testdata3.txt"

#define STsize 1000
//#define STsize 30
#define HTsize 100

#define isLetter(x) ( ((x) >= 'a' && (x) <= 'z') || ((x) >= 'A' && (x) <= 'Z') || (x) == '_')
#define isDigit(x) ((x) >= '0' && (x) <= '9')

typedef struct HTentry *HTpointer;
typedef struct HTentry {
	int index;
	HTpointer next;
}HTentry;

HTpointer HT[HTsize];
char ST[STsize];

int nextid = 0; //현재 identifier 위치
int nextfree = 0; // 다음 identifier가 올 위치 인덱스
int hashcode; //identifier가 가질 해시코드
int sameid; //이미 있는 identifier일 경우 첫 identifier의 인덱스 

int found = 0; // 미 있는지 없는지 판단할 때 쓰이는 변수(있다면 1, 처음 온 것이라면 0)
int error = 0; //각각의 에러를 판단할 때 쓰이는 변수 

//사용할 함수들 정의
void initialize();
void PrintHStable();
void SkipSeperators();
void ReadID();
void ComputeHS(int nid, int nfree);
void LookupHS(int nid, int hscode);
void ADDHT(int hscode);

FILE *fp;
char input;

//파일 입출력 초기화 과정
//한 character 단위로 읽음
void initialize() {
	fp = fopen(FILE_NAME, "r");
	input = fgetc(fp);
}

//마지막 해시테이블 출력 함수
void PrintHStable() {
	int i, j;
	HTpointer here;

	printf("\n\n [[   HASH TABLE  ]] \n\n");

	for (i = 0; i < HTsize; i++) {
		if (HT[i] != NULL) {
			printf("  Hash Code %3d : ", i);
			for (here = HT[i]; here != NULL; here = here->next) {
				j = here->index;
				while (ST[j] != '\0' && j < STsize) {
					printf("%c", ST[j++]);
				}
				printf("     ");
			}
			printf("\n");
		}
	}
	printf("\n\n\n <%5d characters are used in the string table >\n", nextfree);
}

//지정된 문자, 숫자, delimiter이외의 character 구분하는 함수 
void SkipSeperators() {
	while( input != EOF && !(isLetter(input) || isDigit(input)) ) {
		if(input != ' ' && input != '\t' && input != ',' && input != ';' && input != '?' && input != '!'
			&& input != '.' && input != ':' && input != '\n'){
			error = 2;
			printf("...Error...		%c		 is illegal seperator \n", input);
		}
		input = fgetc(fp);
	}
}

//한 글자씩 읽어서 처리하는 함수
void ReadID() {
	nextid = nextfree;

	//첫 character가 숫자로 시작하면 에러
	if (isDigit(input)) {
		error = 3;
		printf("...Error...		");

		//goto문 사용해서 해당 스트링 끝까지 읽어옴
HERE:
		printf("%c", input);
		input = fgetc(fp);	
		if(input != EOF && (isLetter(input) || isDigit(input))){
			goto HERE;
		}
		printf("		 start with digit \n");
	}

	//첫 character가 숫자로 시작하지 않는 경우
	else {
		error = 0; //error번호를 0으로 만들어서 위의 error=3과 다른 경우라는 것을 명시해줌
		while (input != EOF && (isLetter(input) || isDigit(input))) {
			//nextfree가 STsize와 같다면 오버플로우 발생
			if (nextfree == STsize) { 
				error = 1;
				printf("...Error...			 OVERFLOW ");
				PrintHStable();
				exit(0);
			}
			//그 외의 정상적인 경우
			ST[nextfree++] = input;
			input = fgetc(fp);
		}
	}
}

//해시테이블의 해시코드 계산하는 함수
//delimiter로 구분되는 스트링의 정수값을 모두 더한 후 해시테이블 사이즈로 나눔
void ComputeHS(int nid, int nfree) {
	int code, i;
	code = 0;
	for (i = nid; i < nfree - 1; i++) {
		code += (int)ST[i];
	}
	hashcode = code % HTsize;
}
//이미 해시테이블에 존재하는지 아닌지 구별하는 함수
void LookupHS(int nid, int hscode) {
	HTpointer here;
	int i, j, k;

	found = 0; 

	if(HT[hscode] != NULL) {
		here = HT[hscode];
		if(here != NULL && found == 0) {
			found = 1; //기본값은 1이라고 설정
			i = here->index;
			j = nid;
			sameid = i;

			if(ST[i] != '\0' && ST[j] != '\0' && found == 1) {
				if (ST[i] != ST[j]) { //만약 같지 않다면 처음 들어온 것이라 판단
					found = 0;
				}
				else { //인덱스를 늘려나가며 계속 비교
					i++;
					j++;
				}
			}
			here = here->next;
		}
	}
	//처음 들어온 identifier
	if (found == 0) { 
		if((nextfree - nextid) >= 10){ //길이가 10 넘으면 에러 출력
			printf("...Error...		");
			for(k=nextid; k<nextfree -1; k++){
				printf("%c", ST[k]);
			}
			printf("	too long idetifier\n");
		}
		else{ //길이가 10 이내면 정상적으로 출력
			printf("%6d			", nextid);
			for (i = nextid; i < nextfree - 1; i++) {	
					printf("%c", ST[i]);	
			}	
			printf("		(entered)\n");
			ADDHT(hashcode);
		}
	}
	//이미 들어온 identifier와 겹치는 경우(found == 1)
	else {
		printf("%6d			", sameid);
		for (i = nextid; i < nextfree - 1; i++) {
			printf("%c", ST[i]);
		}
		printf("		(already existed)\n");
		nextfree = nextid;	
	}
}

//해시테이블에 추가하는 함수
void ADDHT(int hscode) {
	HTpointer ptr;

	ptr = (HTpointer)malloc(sizeof(ptr));
	ptr->index = nextid;
	ptr->next = HT[hscode];
	HT[hscode] = ptr;
}

int main() {

	printf("<Testdata_3 & ST=1000>\n");
	printf(" ------------          ------------\n");
	printf(" Index of ST            identifier \n");
	printf(" ------------          ------------\n");
	printf("\n");

	initialize(); 

	while (input != EOF) {
		SkipSeperators();  
		ReadID();

		if(input != EOF && error != 3){
			if (nextfree == STsize) {//오버플로우 발생 조건
				error = 1;
				printf("...Error...				OVERFLOW ");
				PrintHStable();
				exit(0);
			}
			ST[nextfree++] = '\0';

			ComputeHS(nextid, nextfree);
			LookupHS(nextid, hashcode);
		}
	}
	PrintHStable();
}

