%skeleton "lalr1.cc"

%defines
%define namespace "libqt4json"
%define parser_class_name "CParser"
%code requires {
	#include <iostream>
	#include <QVariant>
	#include <QList>
	#include <QtDebug>
	
	using namespace std;
	
	namespace libqt4json {
		class CScanner;
	}
}

%lex-param		{ CScanner &scanner }
%parse-param	{ CScanner &scanner }

%code {
	static QList<QVariant> filo;
	
	static int yylex(libqt4json::CParser::semantic_type *yylval, libqt4json::CScanner &scanner);
	static void addListItem(QVariant *v);
	static void addListItem(QVariant v);
	static void addMapItem(QVariant *k, QVariant *v);
	static void addMapItem(QVariant *k, QVariant v);
	
	QVariant result;
	QString lastError;

	int lineno=0;
}
%union {
	QVariant *variant;
}
%token <variant> DOUBLE
%token <variant> INT
%token <variant> STRING
%token TRUEVALUE FALSEVALUE NULLVALUE
%token LISTO LISTF
%token MAPO MAPF
%token COMMA COLON

%start AXIOME
%%
AXIOME	:	EXP						{ 	result=filo.takeLast(); }
		;
EXP		:	LIST					{}
		|	MAP						{}
		;
DEBLIST	:	LISTO					{ 	QVariantList vl;
										filo.append(QVariant(vl));
									}
		;
DEBMAP	:	MAPO					{	QVariantMap vm;
										filo.append(QVariant(vm));
									}
		;
LIST	:	DEBLIST SUITE LISTF		{}
		;
MAP		:	DEBMAP PAIR MAPF		{}
		;
SUITE	:	INT						{	addListItem($1); }
		|	DOUBLE					{ 	addListItem($1); }
		|	STRING					{ 	addListItem($1); }
		|	TRUEVALUE				{ 	addListItem(QVariant(true)); }
		|	FALSEVALUE				{ 	addListItem(QVariant(false)); }
		|	NULLVALUE				{ 	addListItem(QVariant()); }
		|	MAP						{	addListItem(filo.takeLast()); }
		|	LIST					{	addListItem(filo.takeLast()); }
		|	SUITE COMMA SUITE		{}
		;	
PAIR	:	STRING COLON INT		{	addMapItem($1, $3); }
		|	STRING COLON DOUBLE		{ 	addMapItem($1, $3); }
		|	STRING COLON STRING		{	addMapItem($1, $3); }
		|	STRING COLON TRUEVALUE	{ 	addMapItem($1, QVariant(true)); }
		|	STRING COLON FALSEVALUE	{ 	addMapItem($1, QVariant(false)); }
		|	STRING COLON NULLVALUE	{ 	addMapItem($1, QVariant()); }
		|	STRING COLON LIST		{	addMapItem($1, filo.takeLast()); }
		|	STRING COLON MAP		{	addMapItem($1, filo.takeLast()); }
		|	PAIR COMMA PAIR			{}
		;
%%

void libqt4json::CParser::error(const libqt4json::CParser::location_type &l, const string &errMessage) {
	lastError=QObject::tr("Error")+":"+errMessage.c_str();
}

#include "CScanner.h"
static int yylex(libqt4json::CParser::semantic_type *yylval, libqt4json::CScanner &scanner) {
	return scanner.yylex(yylval);
}

static void addListItem(QVariant *v) {
	QVariant variant(*v);
	addListItem(variant);
	delete v;
}

static void addListItem(QVariant v) {
	QVariantList vl=qvariant_cast<QVariantList>(filo.takeLast());
	vl.append(v);
	filo.append(QVariant(vl));
}

static void addMapItem(QVariant *k, QVariant *v) {
	QVariant variant(*v);
	addMapItem(k, variant);
	delete v;
}

static void addMapItem(QVariant *k, QVariant v) {
	QVariantMap vm=qvariant_cast<QVariantMap>(filo.takeLast());
	vm.insert(k->toString(), v);
	filo.append(QVariant(vm));
	delete k;
}

