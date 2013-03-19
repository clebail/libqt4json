%{
#include <stdio.h>
#include <string.h>
#include "libqt4json.y.h"
%}
SPACE			[ \t\r\n]
DIGIT1to9		[1-9]
DIGIT			[0-9]
DIGITS			{DIGIT}+
INT				{DIGIT}|{DIGIT1to9}{DIGITS}|-{DIGIT}|-{DIGIT1to9}{DIGITS}
FRAC			[.]{DIGITS}
EXP				{E}{DIGITS}
E				[eE][+-]?
HEX_DIGIT		[0-9a-f]
NUMBER			{INT}|{INT}{FRAC}|{INT}{EXP}|{INT}{FRAC}{EXP}
UNESCAPEDCHAR	[ -!#-\[\]-~]
ESCAPEDCHAR		\\["\\bfnrt/]
UNICODECHAR		\\u{HEX_DIGIT}{HEX_DIGIT}{HEX_DIGIT}{HEX_DIGIT}
CHAR			{UNESCAPEDCHAR}|{ESCAPEDCHAR}|{UNICODECHAR}
CHARS			{CHAR}+
DBL_QUOTE		["]
TRUE			[tT][rR][uU][eE]
FALSE			[fF][aA][lL][sS][eE]
NULL			[nN][uU][lL]{2}
%%
{NUMBER}	{	double *d=(double *)malloc(sizeof(double));
				sscanf(yytext, "%lf", d); 
				yylval=(int)d;
				return NUMBER; 
			}
{DBL_QUOTE}{DBL_QUOTE}|{DBL_QUOTE}{CHARS}{DBL_QUOTE} {
				char *s=(char *)malloc(strlen(yytext)+1);
				strcpy(s, yytext);
				yylval=(int)s;
				return STRING;
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
{TRUE}		{	return TRUEVALUE;
			}
{FALSE}		{	return FALSEVALUE;
			}
{NULL}		{	return NULLVALUE;
			}
{SPACE}		{}
.			{ 	printf("\nUnkown lexem %s\n", yytext);
			}
%%
int yyerror(char *msg) {
	printf("\n%s\n", msg);
	return 0;
}
