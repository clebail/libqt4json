//------------------------------------------------------------------------------
#ifndef _LIBQT4JSON_H__
#define _LIBQT4JSON_H__
//------------------------------------------------------------------------------
#include <QObject>
#include <QString>
#include <QVariant>
//------------------------------------------------------------------------------
namespace libqt4json {
	//------------------------------------------------------------------------------
	class CJson {
		public:
			QString toString(QVariant variant);
			QVariant fromString(QString json) { return QVariant(); }
		private:
			QString variantToString(QVariant variant, bool& simpleType);
			QString objectStarToString(QVariant variant);
			QString listToString(QVariant variant);
			QString mapToString(QVariant variant);
			QString protect(QString str);
	};
	//------------------------------------------------------------------------------
} //namespace
//------------------------------------------------------------------------------
#endif //_LIBQT4JSON_H__
//------------------------------------------------------------------------------