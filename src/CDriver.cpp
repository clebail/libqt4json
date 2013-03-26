//------------------------------------------------------------------------------
#include <sstream>
#include <QtDebug>
#include "CDriver.h"
#include "CScanner.h"
//------------------------------------------------------------------------------
namespace libqt4json {
	//------------------------------------------------------------------------------
	void CDriver::parse(QString json, bool& ok) {
		std::istringstream iss(json.toStdString());
		CScanner *scanner=new CScanner(&iss);
		CParser *parser=new CParser(*scanner, *this);
		ok=!parser->parse();
		if(scanner->isOnError()) {
			ok=false;
			
			setLastError(scanner->getErrors().join("\n"));
		}
		
		delete parser;
		delete scanner;
	}
} //namespace
//------------------------------------------------------------------------------
