#include <stdio.h>
#include <stdlib.h>
#include "tn.h"
#include "glob.h"
#include "SymbolTable.h"
#include "ReportError.h"

extern int yylex();
extern char *yytext;

//tn의 케이스에 맞게 출력해주는 함수
void printtoken(enum tokennumber tn){ 
 switch(tn){ //전역변수 LineNumber는 0으로 초기화 되어있기 때문에 1씩 더해준 후 출력해준다.
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
	//TIDENT와 TERROR는 SymbolTable.c와 ReportError.c에서 따로 작업해주기 때문에 아무것도 출력해주지 않았다. 
	case TIDENT			: break;
	case TERROR			: break;
 }
}

void main(){
	enum tokennumber tn; //tn.h에 정의되어있는 tokennumber 값들을 tn변수명으로 재정의
	printf("\n<<<Start of LEX!!!>>>\n\n");

	printf("Line number	Token type	ST-index	Token\n");
	printf("-------------------------------------------------------\n");

	/*yylex()함수를 호출하면 lex.yy.c로 작업이 넘어감
	yylex()로 값을 받아온 후 해당되는 tn에 맞게 출력해주는 함수 printtoken() 호출*/
	while((tn = yylex()) != TEOF){ 
		printtoken(tn);
	}

	//모든 작업이 종료된 후 전역변수로 설정된 cError값을 출력
	if(cErrors == 0){ //에러가 없을 경우
		printf("No errors detected.\n");
	}
	else{ //cError값이 0이 아닐 경우
		printf("%d errors detected.\n", cErrors);
	}
}