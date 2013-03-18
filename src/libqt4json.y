%{
#include <stdio.h>
%}

%token NUMBER
%token LISTO LISTF
%token MAPO MAPF
%token COMMA COLON

%start AXIOME
%%
AXIOME	:	EXP					{ printf("resultat\n"); }
		;
EXP		:	LIST				{ printf("list\n"); }
		|	MAP					{ printf("map\n"); }
		;
LIST	:	LISTO SUITE LISTF	{ printf("suite\n"); }
		;
MAP		:	MAPO PAIR MAPF		{ printf("pair\n"); }
		;
SUITE	:	NUMBER				{ printf("suite number\n"); }
		|	MAP					{ printf("suite map\n"); }
		|	LIST				{ printf("suite list\n"); }
		|	SUITE COMMA SUITE	{ printf("next suite\n"); }
		;
PAIR	:	NUMBER COLON NUMBER	{ printf("pair number\n"); }
		|	NUMBER COLON LIST	{ printf("pair list\n"); }
		|	NUMBER COLON MAP	{ printf("pair map\n"); }
		|	PAIR COMMA PAIR		{ printf("next pair\n"); }
		;
%%

int main(void) {
	yyparse();
	return 0;
}

int yywrap(void) {
	return 1;
}

