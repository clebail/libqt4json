//------------------------------------------------------------------------------
#include <QByteArray>
#include <QtDebug>
#include "CCommon.h"
//------------------------------------------------------------------------------
#define UNICODE_CHAR_MASK			0x80
#define NEXT_CHAR_MASK				0x3F
#define START_PLAGE_CONTINUATION	0x80
#define END_PLAGE_CONTINUATION		0xBF
#define BAD_START_SEQUENCE_0		0xC0
#define BAD_START_SEQUENCE_1		0xC1
//------------------------------------------------------------------------------
namespace libqt4json {
	//------------------------------------------------------------------------------
	QString CCommon::fromUnicode(QString str) {
		int idx;
		while((idx = str.indexOf("\\u")) != -1) {
			int nHex = str.mid(idx+2, 4).toInt(0, 16);
			str.replace(idx, 6, QChar(nHex));
		}
		return str;
	}
	//------------------------------------------------------------------------------
	QString CCommon::toUnicode(QString str, bool &ok) {
		QByteArray ba = str.toAscii();
		int i;
		QString uJson = "";
		
		ok = true;
	
		//TODO valid UTF-8	
		for(i=0;i<ba.count();i++) {
			const unsigned char c=ba.at(i);

			if(c & UNICODE_CHAR_MASK) {
				if(c == BAD_START_SEQUENCE_0 || c == BAD_START_SEQUENCE_1) {
					ok = false;

					return str;
				}

				unsigned code = 0;
				int nbUnicodeChar = getNbUnicodeChar(c);

				code |= ((unsigned)c & ((1 << (7-nbUnicodeChar))-1)) << ((nbUnicodeChar-1)*6);  			
				for(int j=1;j<nbUnicodeChar;j++) {
					const unsigned char d = ba.at(++i);

					if(d < START_PLAGE_CONTINUATION || d > END_PLAGE_CONTINUATION) {
						ok = false;

						return str;
					}
					code |= (((unsigned)d) & NEXT_CHAR_MASK) << (nbUnicodeChar-j-1)*6;
				}

				uJson.append("\\u"+QString(QByteArray::number(code, 16).rightJustified(4, '0')));
			}else {
				uJson.append(c);
			}
		}

		return uJson;
	}
	//------------------------------------------------------------------------------
	int CCommon::getNbUnicodeChar(unsigned char c) {
		int nbChar = 0;
		while(c & UNICODE_CHAR_MASK) {
			nbChar++;
			c <<= 1;
		}

		return nbChar;
	}
	//------------------------------------------------------------------------------
} //namespace
//------------------------------------------------------------------------------
