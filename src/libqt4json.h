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
			QString toString(QObject *object);
			QVariant fromString(QString json) { return QVariant(); }
		private:
			QString variantToString(QVariant variant);
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