#include "ReportError.h"
#include "SymbolTable.h"
#include "glob.h"

extern int yylex();
extern char *yytext;
 
/*SymbolTable.c에서 에러를 인식하면 호출되는 c프로그램
error번호에 따라 switch문 이용해서 출력되는 문이 다르다*/
void ReportError(int error){
	switch(error){
	case 1: //오버플로우가 발생했을 경우
		printf("%d		**Error**			OVERFLOW \n", LineNumber+1);
		cErrors++;
		exit(0);
		break;
	case 2: //지정된 문자가 아닌 경우
		printf("%d		**Error**			%s		Illegal Character \n", LineNumber+1, yytext);
		cErrors++;
		break;
	case 3: //첫 문자가 숫자로 시작하는 경우
		printf("%d		**Error**			%s		Illegal IDENT \n", LineNumber+1, yytext);
		cErrors++;
		break;
	case 4: //이미 존재하는 identifier와 겹치는 경우
		printf("%d		**Error**			%s		Already Existed \n", LineNumber+1, yytext);
		cErrors++;
		break;
	} 
}