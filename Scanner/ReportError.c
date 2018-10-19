#include "ReportError.h"
#include "SymbolTable.h"
#include "glob.h"

extern int yylex();
extern char *yytext;
 
/*SymbolTable.c���� ������ �ν��ϸ� ȣ��Ǵ� c���α׷�
error��ȣ�� ���� switch�� �̿��ؼ� ��µǴ� ���� �ٸ���*/
void ReportError(int error){
	switch(error){
	case 1: //�����÷ο찡 �߻����� ���
		printf("%d		**Error**			OVERFLOW \n", LineNumber+1);
		cErrors++;
		exit(0);
		break;
	case 2: //������ ���ڰ� �ƴ� ���
		printf("%d		**Error**			%s		Illegal Character \n", LineNumber+1, yytext);
		cErrors++;
		break;
	case 3: //ù ���ڰ� ���ڷ� �����ϴ� ���
		printf("%d		**Error**			%s		Illegal IDENT \n", LineNumber+1, yytext);
		cErrors++;
		break;
	case 4: //�̹� �����ϴ� identifier�� ��ġ�� ���
		printf("%d		**Error**			%s		Already Existed \n", LineNumber+1, yytext);
		cErrors++;
		break;
	} 
}