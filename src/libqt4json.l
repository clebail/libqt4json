%{
#include <iostream>
#include <QVariant>
#include <QtDebug>
#include "CScanner.h"

typedef libqt4json::CParser::token token;

using namespace std;
%}

%option yyclass="CScanner"
%option noyywrap
%option c++

SPACE			[ \t]
DIGIT1to9		[1-9]
DIGIT			[0-9]
DIGITS			{DIGIT}+
INT				{DIGIT}|{DIGIT1to9}{DIGITS}|-{DIGIT}|-{DIGIT1to9}{DIGITS}
FRAC			[.]{DIGITS}
EXP				{E}{DIGITS}
E				[eE][+-]?
HEX_DIGIT		[0-9a-f]
DOUBLE			{INT}|{INT}{FRAC}|{INT}{EXP}|{INT}{FRAC}{EXP}
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
{INT}		{	int i;
				sscanf(yytext, "%d", &i);
				QVariant *v=new QVariant(i);
				yylval->variant=v;
				return token::INT;
			}
{DOUBLE}	{	double d;
				sscanf(yytext, "%lf", &d);
				QVariant *v=new QVariant(d);
				yylval->variant=v;
				return token::DOUBLE;
			}
{DBL_QUOTE}{DBL_QUOTE}|{DBL_QUOTE}{CHARS}{DBL_QUOTE} {
				yytext[strlen(yytext)-1]=0;
				QVariant *v=new QVariant(yytext+1);
				yylval->variant=v;
				return token::STRING;
			}
"["			{	return token::LISTO;
			}
"]"			{	return token::LISTF;
			}
"{"			{	return token::MAPO;
			}
"}"			{	return token::MAPF;
			}
","			{	return token::COMMA;
			}
":"			{	return token::COLON;
			}
{TRUE}		{	return token::TRUEVALUE;
			}
{FALSE}		{	return token::FALSEVALUE;
			}
{NULL}		{	return token::NULLVALUE;
			}
{SPACE}		{}
"\n"		{	yylineno++;
			}
.			{ 	qDebug() << QObject::tr("Unkown lexem") << yytext << QObject::tr("at line") << yylineno;
			}
%%

