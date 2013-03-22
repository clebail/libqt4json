//------------------------------------------------------------------------------
#ifndef __CSCANNER_H__
#define __CSCANNER_H__
//------------------------------------------------------------------------------
#if ! defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

#undef  YY_DECL
#define YY_DECL int libqt4json::CScanner::yylex()
 
#include <QList>
#include <QVariant>
#include "libqt4json.y.hpp"
//------------------------------------------------------------------------------
namespace libqt4json {
	//------------------------------------------------------------------------------
	class CScanner : public yyFlexLexer {
		public:
			CScanner(std::istream *in) : yyFlexLexer(in), yylval(0) {}
			
			int yylex(libqt4json::CParser::semantic_type *lval) {
				yylval=lval;
				return yylex();
			}
			
			QVariant getResult() { return result; }
			void setResult(QVariant result) { this->result=result; }
		private:
			int yylex();
			libqt4json::CParser::semantic_type *yylval;
			QVariant result;
	};		
} //namespace
//------------------------------------------------------------------------------
#endif //__CSCANNER_H__
//------------------------------------------------------------------------------