#include "SymbolTable.h"
#include "ReportError.h"
#include "glob.h"

/*yytext로 문자열 형태로 들어오게 된다. 따라서 문자열을 문자마다 처리해주어야 하기 때문에 
입력받는 변수는 char input으로 설정하고, 인덱스를 int a로 설정하였다.*/
char input; //입력될 문자에 관한 변수
int a = 0; //yytext에 사용될 인덱스 변수

extern int yylex();
extern char *yytext;

/*지정된 문자, 숫자, delimiter이외의 character를 구분하는 함수이다.*/
void SkipSeperators() {
	while ( input != EOF && !(isLetter(input) || isDigit(input)) ) {
		if(input != ' ' && input != '\t' && input != ',' && input != ';' && input != '?' && input != '!'
			&& input != '.' && input != ':' && input != '\n'){
			ReportError(2); //ReportError 함수 호출
		}
		strcpy(&input, &yytext[a++]); //yytext에서 다음 문자를 input변수에 복사
	}
}

/*한 글자(character)씩 읽어서 처리하는 함수이다.*/
void ReadID() {
	nextid = nextfree;

	//첫 character가 숫자로 시작하면 에러
	if (isDigit(input)) { 
		ReportError(3);
	}

	//첫 character가 숫자로 시작하지 않는 경우
	else {
		error = 0; //error번호를 0으로 만들어서 위의 error=3과 다른 경우라는 것을 명시해줌
		while (input != EOF && (isLetter(input) || isDigit(input))) {
			if (nextfree == STsize) { //nextfree가 STsize와 같다면 오버플로우 발생
				ReportError(1);
				exit(0);
			}
			//그 외의 정상적인 경우
			ST[nextfree++] = input;
			input = yytext[a++];
		}
	}
}

/*해시테이블의 해시코드 계산하는 함수이다. 
delimiter로 구분되는 스트링의 정수값을 모두 더한 후 해시테이블 사이즈로 나눈다.*/
void ComputeHS(int nid, int nfree) {
	int code, i;
	code = 0;
	for (i = nid; i < nfree - 1; i++) {
		code += (int)ST[i];
	}
	hashcode = code % HTsize;
}

/*이미 해시테이블에 존재하는 identifier인지 아닌지 구별하는 함수이다.*/
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
		printf("%d		TIDENT		%d		", LineNumber+1, nextid);
		for (i = nextid+1; i < nextfree - 1; i++) {	
			printf("%c", ST[i]);	
		}	
		printf("\n");
		ADDHT(hashcode);
		nextfree -= 1;
	}

	//이미 들어온 identifier와 겹치는 경우(found == 1)
	else {
		ReportError(4);
		nextfree = nextid;	
	}
}

/*해시테이블에 추가하는 함수이다.*/
void ADDHT(int hscode) {
	HTpointer ptr;

	ptr = (HTpointer)malloc(sizeof(ptr));
	ptr->index = nextid;
	ptr->next = HT[hscode];
	HT[hscode] = ptr;
}

/*SymbolTable.c프로그램에서 가장 먼저 수행될 함수이다. 
lex.yy.c에서 identifier가 인식되면 호출된다.*/
void SymbolTable() {

	//소문자 변환(대소문자 구분 없애기 위해)
	yytext = strlwr(yytext); 
	
	//yytext 길이가 10보다 크면 길이가 10인 character까지 잘라서 yytext에 다시 저장,
	if(strlen(yytext) > 10){ 
		strncpy(yytext, yytext ,10);
		yytext[10] = 0;
	}
	
	//yytext는 문자열이므로 첫 문자부터 마지막 문자까지 for문을 수행
	for(a = 0; a<strlen(yytext); a++) {
		input = yytext[a]; //input에 해당 character 대입

		SkipSeperators();  
		ReadID();

		if(input != EOF && error != 3){
			if (nextfree == STsize) {//오버플로우 발생 조건
				ReportError(1);
				exit(0);
			}
			ST[nextfree++] = '\0';

			ComputeHS(nextid, nextfree);
			LookupHS(nextid, hashcode);
		}
	}
}