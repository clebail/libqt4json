//------------------------------------------------------------------------------
#ifndef __CSCANNER_H__
#define __CSCANNER_H__
//------------------------------------------------------------------------------
#if ! defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

#undef  YY_DECL
#define YY_DECL int libqt4json::CScanner::yylex()
 
#include <QStringList>
#include "libqt4json.y.hpp"
//------------------------------------------------------------------------------
namespace libqt4json {
	//------------------------------------------------------------------------------
	class CScanner : public yyFlexLexer {
		public:
			CScanner(std::istream *in) : yyFlexLexer(in), yylval(0), errors() { lineNo=1; onError=0; }
			
			int yylex(libqt4json::CParser::semantic_type *lval) {
				yylval=lval;
				return yylex();
			}
			
			int getLineNo(void) { return lineNo; }
			bool isOnError(void) { return onError; }
			QStringList getErrors(void) { return errors; }
		private:
			int yylex();
			int lineNo;
			bool onError;
			QStringList errors;
			libqt4json::CParser::semantic_type *yylval;
	};		
} //namespace
//------------------------------------------------------------------------------
#endif //__CSCANNER_H__
//------------------------------------------------------------------------------
