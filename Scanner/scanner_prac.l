%{
/*
 * hw2_scanner.l - lexical analyzer for hw#2
 *
 * Programmer - Soomin, Muslimat 
 *
 * date - 4/7/2017
 *
 * modification history
 * 
*/

#include <stdio.h>
#include <stdlib.h>
#include "tn.h"
#include "glob.h"
#include "SymbolTable.h"
#include "ReportError.h"

%}

%%
"const"					return(TCONST);
"else"					return(TELSE);
"if"					return(TIF);
"int"					return(TINT);
"return"				return(TRETURN);
"void"					return(TVOID);
"while"					return(TWHILE);
"+"					return(TPLUS);
"-"					return(TMINUS);
"*"					return(TSTAR);
"/"					return(TSLASH);
"%"					return(TMOD);
"="					return(TASSIGN);
"+="					return(TADDASSIGN);
"-="					return(TSUBASSIGN);
"*="					return(TMULASSIGN);
"/="					return(TDIVASSIGN);
"%="					return(TMODASSIGN);
"!"					return(TNOT);
"&&"					return(TAND);
"||"					return(TOR);
"=="					return(TEQUAL);
"!="					return(TNOTEQU);
"<"					return(TGREAT);
">"					return(TLESS);
"<="					return(TGREATE);
">="					return(TLESSE);
"++"					return(TINC);
"--"					return(TDEC);
"("					return(TOPEN);
")"					return(TCLOSE);
","					return(TCOMMA);
"{"					return(TBIGOPEN);
"}"					return(TBIGCLOSE);
"["					return(TOPENBRACKET);
"]"					return(TCLOSEBRACKET);
";"					return(TSEMICOLON);

[A-Za-z_][A-Za-z0-9_]*			{ SymbolTable(); }

[1-9][0-9]*				return(TNUMBER);
[0-9]+"."[0-9]+(e[+-]?[0-9]+)?		return(TREALNUMBER);
\"[^"]*\"				return(TSTRING);
"/*"([^*]|\*+[^*/])*\**"*/"		;
"//".*					;
[ \t]					;
\n					LineNumber++;
.					{ ReportError(2); }
%%

void printtoken(enum tokennumber tn){
 switch(tn){
	case TCONST			: printf("%d	TCONST			const\n", LineNumber); break;
	case TELSE			: printf("%d	TELSE			else\n", LineNumber); break;
	case TIF			: printf("%d	TIF			if\n", LineNumber); break;
	case TINT			: printf("%d	TINT			int\n", LineNumber); break;
	case TRETURN			: printf("%d	TRETURN			return\n", LineNumber); break;
	case TVOID			: printf("%d	TVOID			void\n", LineNumber); break;
	case TWHILE			: printf("%d	TWHILE			while\n", LineNumber); break;
	case TPLUS			: printf("%d	TPLUS			+\n", LineNumber); break;
	case TMINUS			: printf("%d	TMINUS			-\n", LineNumber); break;
	case TSTAR			: printf("%d	TSTAR			*\n", LineNumber); break;
	case TSLASH			: printf("%d	TSLASH			/\n", LineNumber); break;
	case TMOD			: printf("%d	TMOD			%\n", LineNumber); break;
	case TASSIGN			: printf("%d	TASSIGN			=\n", LineNumber); break;
	case TADDASSIGN			: printf("%d	TADDASSIGN		+=\n", LineNumber); break;
	case TSUBASSIGN			: printf("%d	TSUBASSIGN		-=\n", LineNumber); break;
	case TMULASSIGN			: printf("%d	TMULASSIGN		*=\n", LineNumber); break;
	case TDIVASSIGN			: printf("%d	TDIVASSIGN		/=\n", LineNumber); break;
	case TMODASSIGN			: printf("%d	TMODASSIGN		%=\n", LineNumber); break;
	case TNOT			: printf("%d	TNOT			!\n", LineNumber); break;
	case TAND			: printf("%d	TAND			&&\n", LineNumber); break;
	case TOR			: printf("%d	TOR			||\n", LineNumber); break;
	case TEQUAL			: printf("%d	TEQUAL			==\n", LineNumber); break;
	case TNOTEQU			: printf("%d	TNOTEQU			!=\n", LineNumber); break;
	case TGREAT			: printf("%d	TGREAT			<\n", LineNumber); break;
	case TLESS			: printf("%d	TLESS			>\n", LineNumber); break;
	case TGREATE			: printf("%d	TGREATE			<=\n", LineNumber); break;
	case TLESSE			: printf("%d	TLESSE			>=\n", LineNumber); break;
	case TINC			: printf("%d	TINC			++\n", LineNumber); break;
	case TDEC			: printf("%d	TDEC			--\n", LineNumber); break;
	case TOPEN			: printf("%d	TOPEN			(\n", LineNumber); break;
	case TCLOSE			: printf("%d	TCLOSE			)\n", LineNumber); break;
	case TCOMMA			: printf("%d	TCOMMA			,\n", LineNumber); break;
	case TBIGOPEN			: printf("%d	TBIGOPEN		{\n", LineNumber); break;
	case TBIGCLOSE			: printf("%d	TBIGCLOSE		}\n", LineNumber); break;
	case TOPENBRACKET		: printf("%d	TOPENBRACKET		[\n", LineNumber); break;
	case TCLOSEBRACKET		: printf("%d	TCLOSEBRACKET		]\n", LineNumber); break;
	case TSEMICOLON			: printf("%d	TSEMICOLON		;\n", LineNumber); break;
	case TNUMBER			: printf("%d	TNUMBER			%s\n", LineNumber, yytext); break;
	case TREALNUMBER		: printf("%d	TREALNUMBER		%s\n", LineNumber, yytext); break;
	case TSTRING			: printf("%d	TSTRING			%s\n", LineNumber, yytext); break;
	case TIDENT			: break;
	case TERROR			: break;
 }
}

void main(){
 enum tokennumber tn;
 printf("\nStart of LEX!!!\n\n");

 printf("Line number	Token type	ST-index	Token\n");

 while((tn = yylex()) != TEOF){
  printtoken(tn);
 }

 if(cErrors == 0){
   printf("No errors detected.\n");
 }
 else{
   printf("%d errors detected.\n", cErrors);
 }
}

int yywrap(){
 printf("\n\nEnd of LEX!!!\n");
 return 1;
}

