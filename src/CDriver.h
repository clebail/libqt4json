//------------------------------------------------------------------------------
#ifndef __CDRIVER_H__
#define __CDRIVER_H__
//------------------------------------------------------------------------------
#include <QVariant>
#include <QString>
#include "libqt4json.y.hpp"
//------------------------------------------------------------------------------
namespace libqt4json {
	//------------------------------------------------------------------------------
	class CDriver {
		public:
			CDriver(void) {}
			
			void parse(QString json, bool& ok);
			QVariant getResult() { return result; }
			void setResult(QVariant result) { this->result=result; }
			void setLastError(QString lastError) { this->lastError=lastError; }
			QString getLastError(void) { return lastError; }
			static QString fromUnicode(QString str);
			static QString toUnicode(QString str);
		private:
			QVariant result;
			QString lastError;

			static int getNbUnicodeChar(unsigned char c);
	};		
} //namespace
//------------------------------------------------------------------------------
#endif //__CDRIVER_H__
//------------------------------------------------------------------------------
