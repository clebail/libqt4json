%{
#include <stdio.h>
#include "libqt4json.y.h"
%}
SPACE	[ \t\r\n]
DIGIT	[0-9]
NUMBER	{DIGIT}+
%%
{NUMBER}	{	sscanf(yytext, "%d", &yylval); 
				return NUMBER; 
			}
"["			{	return LISTO;
			}
"]"			{	return LISTF;
			}
"{"			{	return MAPO;
			}
"}"			{	return MAPF;
			}
","			{	return COMMA;
			}
":"			{	return COLON;
			}
{SPACE}		{}
.			{ 	printf("\nUnkown lexem %s\n", yytext);
			}
%%
int yyerror(char *msg) {
	printf("\n%s\n", msg);
	return 0;
}
