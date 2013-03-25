//------------------------------------------------------------------------------
#include <sstream>
#include "CDriver.h"
//------------------------------------------------------------------------------
namespace libqt4json {
	//------------------------------------------------------------------------------
	void CDriver::parse(QString json, bool& ok) {
		std::istringstream iss(json.toStdString());
		CScanner *scanner=new CScanner(&iss);
		CParser *parser=new CParser(*scanner, *this);
		ok=!parser->parse();

		delete parser;
		delete scanner;
	}
} //namespace
//------------------------------------------------------------------------------
