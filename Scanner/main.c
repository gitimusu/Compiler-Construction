#include <stdio.h>
#include <stdlib.h>
#include "tn.h"
#include "glob.h"
#include "SymbolTable.h"
#include "ReportError.h"

extern int yylex();
extern char *yytext;

//tn�� ���̽��� �°� ������ִ� �Լ�
void printtoken(enum tokennumber tn){ 
 switch(tn){ //�������� LineNumber�� 0���� �ʱ�ȭ �Ǿ��ֱ� ������ 1�� ������ �� ������ش�.
	case TCONST			: printf("%d		TCONST				const\n", LineNumber+1); break;
	case TELSE			: printf("%d		TELSE				else\n", LineNumber+1); break;
	case TIF			: printf("%d		TIF				if\n", LineNumber+1); break;
	case TINT			: printf("%d		TINT				int\n", LineNumber+1); break;
	case TRETURN		: printf("%d		TRETURN				return\n", LineNumber+1); break;
	case TVOID			: printf("%d		TVOID				void\n", LineNumber+1); break;
	case TWHILE			: printf("%d		TWHILE				while\n", LineNumber+1); break;
	case TPLUS			: printf("%d		TPLUS				+\n", LineNumber+1); break;
	case TMINUS			: printf("%d		TMINUS				-\n", LineNumber+1); break;
	case TSTAR			: printf("%d		TSTAR				*\n", LineNumber+1); break;
	case TSLASH			: printf("%d		TSLASH				/\n", LineNumber+1); break;
	case TMOD			: printf("%d		TMOD				%\n", LineNumber+1); break;
	case TASSIGN		: printf("%d		TASSIGN				=\n", LineNumber+1); break;
	case TADDASSIGN		: printf("%d		TADDASSIGN			+=\n", LineNumber+1); break;
	case TSUBASSIGN		: printf("%d		TSUBASSIGN			-=\n", LineNumber+1); break;
	case TMULASSIGN		: printf("%d		TMULASSIGN			*=\n", LineNumber+1); break;
	case TDIVASSIGN		: printf("%d		TDIVASSIGN			/=\n", LineNumber+1); break;
	case TMODASSIGN		: printf("%d		TMODASSIGN			%=\n", LineNumber+1); break;
	case TNOT			: printf("%d		TNOT				!\n", LineNumber+1); break;
	case TAND			: printf("%d		TAND				&&\n", LineNumber+1); break;
	case TOR			: printf("%d		TOR					||\n", LineNumber+1); break;
	case TEQUAL			: printf("%d		TEQUAL				==\n", LineNumber+1); break;
	case TNOTEQU		: printf("%d		TNOTEQU				!=\n", LineNumber+1); break;
	case TGREAT			: printf("%d		TGREAT				<\n", LineNumber+1); break;
	case TLESS			: printf("%d		TLESS				>\n", LineNumber+1); break;
	case TGREATE		: printf("%d		TGREATE				<=\n", LineNumber+1); break;
	case TLESSE			: printf("%d		TLESSE				>=\n", LineNumber+1); break;
	case TINC			: printf("%d		TINC				++\n", LineNumber+1); break;
	case TDEC			: printf("%d		TDEC				--\n", LineNumber+1); break;
	case TOPEN			: printf("%d		TOPEN				(\n", LineNumber+1); break;
	case TCLOSE			: printf("%d		TCLOSE				)\n", LineNumber+1); break;
	case TCOMMA			: printf("%d		TCOMMA				,\n", LineNumber+1); break;
	case TBIGOPEN		: printf("%d		TBIGOPEN			{\n", LineNumber+1); break;
	case TBIGCLOSE		: printf("%d		TBIGCLOSE			}\n", LineNumber+1); break;
	case TOPENBRACKET	: printf("%d		TOPENBRACKET		[\n", LineNumber+1); break;
	case TCLOSEBRACKET	: printf("%d		TCLOSEBRACKET			]\n", LineNumber+1); break;
	case TSEMICOLON		: printf("%d		TSEMICOLON			;\n", LineNumber+1); break;
	case TNUMBER		: printf("%d		TNUMBER				%s\n", LineNumber+1, yytext); break;
	case TREALNUMBER	: printf("%d		TREALNUMBER			%s\n", LineNumber+1, yytext); break;
	case TSTRING		: printf("%d		TSTRING				%s\n", LineNumber+1, yytext); break;
	//TIDENT�� TERROR�� SymbolTable.c�� ReportError.c���� ���� �۾����ֱ� ������ �ƹ��͵� ��������� �ʾҴ�. 
	case TIDENT			: break;
	case TERROR			: break;
 }
}

void main(){
	enum tokennumber tn; //tn.h�� ���ǵǾ��ִ� tokennumber ������ tn���������� ������
	printf("\n<<<Start of LEX!!!>>>\n\n");

	printf("Line number	Token type	ST-index	Token\n");
	printf("-------------------------------------------------------\n");

	/*yylex()�Լ��� ȣ���ϸ� lex.yy.c�� �۾��� �Ѿ
	yylex()�� ���� �޾ƿ� �� �ش�Ǵ� tn�� �°� ������ִ� �Լ� printtoken() ȣ��*/
	while((tn = yylex()) != TEOF){ 
		printtoken(tn);
	}

	//��� �۾��� ����� �� ���������� ������ cError���� ���
	if(cErrors == 0){ //������ ���� ���
		printf("No errors detected.\n");
	}
	else{ //cError���� 0�� �ƴ� ���
		printf("%d errors detected.\n", cErrors);
	}
}