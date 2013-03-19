%{
#include <stdio.h>

typedef enum { edtDouble, edtString } EDataType;

typedef struct _SValue {
	EDataType dataType;
	void *data;
}SValue;

typedef struct _SMap {
	char *key;
	SValue *value;
}SMAP;
%}

%token NUMBER STRING TRUEVALUE FALSEVALUE NULLVALUE
%token LISTO LISTF
%token MAPO MAPF
%token COMMA COLON

%start AXIOME
%%
AXIOME	:	EXP						{ printf("resultat\n"); }
		;
EXP		:	LIST					{ printf("list\n"); }
		|	MAP						{ printf("map\n"); }
		;
LIST	:	LISTO SUITE LISTF		{ printf("suite\n"); }
		;
MAP		:	MAPO PAIR MAPF			{ printf("pair\n"); }
		;
SUITE	:	NUMBER					{ printf("suite number %lf\n", (double)*((double *)$$)); }
		|	STRING					{ printf("suite string %s\n", (char *)$$); }
		|	TRUEVALUE				{ printf("suite true\n"); }
		|	FALSEVALUE				{ printf("suite false\n"); }
		|	NULLVALUE				{ printf("suite null\n"); }
		|	MAP						{ printf("suite map\n"); }
		|	LIST					{ printf("suite list\n"); }
		|	SUITE COMMA SUITE		{ printf("next suite\n"); }
		;	
PAIR	:	STRING COLON NUMBER		{ printf("pair number : %s = %lf\n", (char *)$1, (double)*((double *)$3)); }
		|	STRING COLON STRING		{ printf("pair string : %s = %s\n", (char *)$1, (char *)$3); }
		|	STRING COLON TRUEVALUE	{ printf("pair true\n"); }
		|	STRING COLON FALSEVALUE	{ printf("pair false\n"); }
		|	STRING COLON NULLVALUE	{ printf("pair null\n"); }
		|	STRING COLON LIST		{ printf("pair list\n"); }
		|	STRING COLON MAP		{ printf("pair map\n"); }
		|	PAIR COMMA PAIR			{ printf("next pair\n"); }
		;
%%

void scan_string(const char* str) {
    yy_switch_to_buffer(yy_scan_string(str));
	yyparse();
}

int yywrap(void) {
	return 1;
}

