#include "SymbolTable.h"
#include "ReportError.h"
#include "glob.h"

/*yytext�� ���ڿ� ���·� ������ �ȴ�. ���� ���ڿ��� ���ڸ��� ó�����־�� �ϱ� ������ 
�Է¹޴� ������ char input���� �����ϰ�, �ε����� int a�� �����Ͽ���.*/
char input; //�Էµ� ���ڿ� ���� ����
int a = 0; //yytext�� ���� �ε��� ����

extern int yylex();
extern char *yytext;

/*������ ����, ����, delimiter�̿��� character�� �����ϴ� �Լ��̴�.*/
void SkipSeperators() {
	while ( input != EOF && !(isLetter(input) || isDigit(input)) ) {
		if(input != ' ' && input != '\t' && input != ',' && input != ';' && input != '?' && input != '!'
			&& input != '.' && input != ':' && input != '\n'){
			ReportError(2); //ReportError �Լ� ȣ��
		}
		strcpy(&input, &yytext[a++]); //yytext���� ���� ���ڸ� input������ ����
	}
}

/*�� ����(character)�� �о ó���ϴ� �Լ��̴�.*/
void ReadID() {
	nextid = nextfree;

	//ù character�� ���ڷ� �����ϸ� ����
	if (isDigit(input)) { 
		ReportError(3);
	}

	//ù character�� ���ڷ� �������� �ʴ� ���
	else {
		error = 0; //error��ȣ�� 0���� ���� ���� error=3�� �ٸ� ����� ���� �������
		while (input != EOF && (isLetter(input) || isDigit(input))) {
			if (nextfree == STsize) { //nextfree�� STsize�� ���ٸ� �����÷ο� �߻�
				ReportError(1);
				exit(0);
			}
			//�� ���� �������� ���
			ST[nextfree++] = input;
			input = yytext[a++];
		}
	}
}

/*�ؽ����̺��� �ؽ��ڵ� ����ϴ� �Լ��̴�. 
delimiter�� ���еǴ� ��Ʈ���� �������� ��� ���� �� �ؽ����̺� ������� ������.*/
void ComputeHS(int nid, int nfree) {
	int code, i;
	code = 0;
	for (i = nid; i < nfree - 1; i++) {
		code += (int)ST[i];
	}
	hashcode = code % HTsize;
}

/*�̹� �ؽ����̺� �����ϴ� identifier���� �ƴ��� �����ϴ� �Լ��̴�.*/
void LookupHS(int nid, int hscode) {
	HTpointer here;
	int i, j, k;

	found = 0; 

	if(HT[hscode] != NULL) {
		here = HT[hscode];
		if(here != NULL && found == 0) {
			found = 1; //�⺻���� 1�̶�� ����
			i = here->index;
			j = nid;
			sameid = i;

			if(ST[i] != '\0' && ST[j] != '\0' && found == 1) {
				if (ST[i] != ST[j]) { //���� ���� �ʴٸ� ó�� ���� ���̶� �Ǵ�
					found = 0;
				}
				else { //�ε����� �÷������� ��� ��
					i++;
					j++;
				}
			}
			here = here->next;
		}
	}

	//ó�� ���� identifier
	if (found == 0) { 
		printf("%d		TIDENT		%d		", LineNumber+1, nextid);
		for (i = nextid+1; i < nextfree - 1; i++) {	
			printf("%c", ST[i]);	
		}	
		printf("\n");
		ADDHT(hashcode);
		nextfree -= 1;
	}

	//�̹� ���� identifier�� ��ġ�� ���(found == 1)
	else {
		ReportError(4);
		nextfree = nextid;	
	}
}

/*�ؽ����̺� �߰��ϴ� �Լ��̴�.*/
void ADDHT(int hscode) {
	HTpointer ptr;

	ptr = (HTpointer)malloc(sizeof(ptr));
	ptr->index = nextid;
	ptr->next = HT[hscode];
	HT[hscode] = ptr;
}

/*SymbolTable.c���α׷����� ���� ���� ����� �Լ��̴�. 
lex.yy.c���� identifier�� �νĵǸ� ȣ��ȴ�.*/
void SymbolTable() {

	//�ҹ��� ��ȯ(��ҹ��� ���� ���ֱ� ����)
	yytext = strlwr(yytext); 
	
	//yytext ���̰� 10���� ũ�� ���̰� 10�� character���� �߶� yytext�� �ٽ� ����,
	if(strlen(yytext) > 10){ 
		strncpy(yytext, yytext ,10);
		yytext[10] = 0;
	}
	
	//yytext�� ���ڿ��̹Ƿ� ù ���ں��� ������ ���ڱ��� for���� ����
	for(a = 0; a<strlen(yytext); a++) {
		input = yytext[a]; //input�� �ش� character ����

		SkipSeperators();  
		ReadID();

		if(input != EOF && error != 3){
			if (nextfree == STsize) {//�����÷ο� �߻� ����
				ReportError(1);
				exit(0);
			}
			ST[nextfree++] = '\0';

			ComputeHS(nextid, nextfree);
			LookupHS(nextid, hashcode);
		}
	}
}