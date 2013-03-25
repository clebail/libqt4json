//------------------------------------------------------------------------------
#ifndef __CSCANNER_H__
#define __CSCANNER_H__
//------------------------------------------------------------------------------
#if ! defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

#undef  YY_DECL
#define YY_DECL int libqt4json::CScanner::yylex(libqt4json::CParser::semantic_type *lval, libqt4json::CParser::location_type *lloc)
 
#include <QList>
#include <QVariant>
#include "libqt4json.y.hpp"
//------------------------------------------------------------------------------
namespace libqt4json {
	//------------------------------------------------------------------------------
	class CScanner : public yyFlexLexer {
		public:
			CScanner(std::istream *in) : yyFlexLexer(in), yylval(0), yylloc(0) { }
			
			int yylex(libqt4json::CParser::semantic_type *lval, libqt4json::CParser::location_type *lloc) {
				yylval=lval;
				yylloc=lloc;
				return yylex();
			}
			
			QVariant getResult() { return result; }
			void setResult(QVariant result) { this->result=result; }
		private:
			int yylex();
			libqt4json::CParser::semantic_type *yylval;
			libqt4json::CParser::location_type *yylloc;
			QVariant result;
	};		
} //namespace
//------------------------------------------------------------------------------
#endif //__CSCANNER_H__
//------------------------------------------------------------------------------
