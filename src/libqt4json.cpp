//------------------------------------------------------------------------------
#include <QMetaProperty>
#include <QtDebug>
#include <sstream>
#include "libqt4json.h"
#include "CDriver.h"
//------------------------------------------------------------------------------
namespace libqt4json {
	//------------------------------------------------------------------------------
	QString CJson::toString(QVariant variant) {
		bool simpleType;
		QString json=variantToString(variant, simpleType);
		if(simpleType) {
			json="["+json+"]";
		}
		return json;
	}
	//------------------------------------------------------------------------------
	QVariant CJson::fromString(QString json, bool& ok) {
		CDriver *driver=new CDriver();
		QVariant ret;

		driver->parse(json, ok);
		if(ok) {
			ret=driver->getResult();
		}

		lastError=driver->getLastError();

		delete driver;

		return ret;
	}
	//------------------------------------------------------------------------------
	QString CJson::getLastError(void) {
		return lastError;
	}
	//------------------------------------------------------------------------------
	QString CJson::variantToString(QVariant variant, bool& simpleType) {
		simpleType=false;
		
		switch(variant.type()) {
			case QVariant::Double:
			case QVariant::Int:
			case QVariant::LongLong:
				simpleType=true;
				return variant.toString();
			case QMetaType::QObjectStar:
				return objectStarToString(variant);
			case QVariant::List:
				return listToString(variant);
			case QVariant::Map:
				return mapToString(variant);
			default:
				if(variant.canConvert<QString>()) {
					simpleType=true;
					return "\""+protect(variant.toString())+"\"";
				}
		}
		
		qDebug() << QObject::tr("Unable to convert") << variant.type() << QObject::tr("in json");
		
		return "null";
	}
	//------------------------------------------------------------------------------
	QString CJson::objectStarToString(QVariant variant) {
		QObject *object=qvariant_cast<QObject *>(variant);
		
		if(object != 0) {
			QString json="{";
			QString s="";
			bool simpleType;

			const QMetaObject *metaObject=object->metaObject();
			for(int i=metaObject->propertyOffset();i<metaObject->propertyCount();i++) {
				QMetaProperty property=metaObject->property(i);

				json+=s+"\""+property.name()+"\": "+variantToString(property.read(object), simpleType);
				s=", ";
			}
			json+="}";
			
			return json;
		}
		
		qDebug() << QObject::tr("Cannot cast") << variant.type() << QObject::tr("as QObject *");
		
		return "null";
	}
	//------------------------------------------------------------------------------
	QString CJson::listToString(QVariant variant) {
		QVariantList l=variant.toList();
		int i;
		QString json="[";
		QString s="";
		bool simpleType;
		
		for(i=0;i<l.size();i++) {
			json+=s+variantToString(l.at(i), simpleType);
			s=", ";
		}
		
		json+="]";
		
		return json;
	}
	//------------------------------------------------------------------------------
	QString CJson::mapToString(QVariant variant) {
		QVariantMap m=variant.toMap();
		QMapIterator<QString, QVariant> i(m);
		QString json="{";
		QString s="";
		bool simpleType;
		
		while (i.hasNext()) {
			i.next();
			json+=s+"\""+i.key()+"\": "+variantToString(i.value(), simpleType);
			s=", ";
		}
		
		json+="}";
		
		return json;
	}
	//------------------------------------------------------------------------------
	QString CJson::protect(QString str) {
		str=str.replace("\"", "\\\"");
		str=str.replace("\\", "\\\\");
		str=str.replace("/", "\\/");
		str=str.replace("\b", "\\\b");
		str=str.replace("\f", "\\\f");
		str=str.replace("\n", "\\\n");
		str=str.replace("\r", "\\\r");
		str=str.replace("\t", "\\\t");
		
		return CDriver::toUnicode(str);
	}
	//------------------------------------------------------------------------------
} //namespace
//------------------------------------------------------------------------------
