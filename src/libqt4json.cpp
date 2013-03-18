//------------------------------------------------------------------------------
#include <QMetaProperty>
#include <QtDebug>
#include "libqt4json.h"
//------------------------------------------------------------------------------
namespace libqt4json {
	//------------------------------------------------------------------------------
	extern "C" {
		void scan_string(char *input);
	}// extern "C"
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
	QVariant CJson::fromString(QString json) {
		scan_string(json.toUtf8().data());
	}
	//------------------------------------------------------------------------------
	QString CJson::variantToString(QVariant variant, bool& simpleType) {
		simpleType=false;
		qDebug() << variant.type();
		
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
				simpleType=true;
				return "\""+protect(variant.toString())+"\"";
		}
	}
	//------------------------------------------------------------------------------
	QString CJson::objectStarToString(QVariant variant) {
		QObject *object=qvariant_cast<QObject *>(variant);
		
		qDebug() << "Object";
		
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
		
		return "null";
	}
	//------------------------------------------------------------------------------
	QString CJson::listToString(QVariant variant) {
		QVariantList l=qvariant_cast<QVariantList>(variant);
		int i;
		QString json="[";
		QString s="";
		bool simpleType;
		
		qDebug() << "List" << l.size();
		
		for(i=0;i<l.size();i++) {
			qDebug() << l.at(i);
			json+=s+variantToString(l.at(i), simpleType);
			s=", ";
		}
		
		json+="]";
		
		return json;
	}
	//------------------------------------------------------------------------------
	QString CJson::mapToString(QVariant variant) {
		QVariantMap m=qvariant_cast<QVariantMap>(variant);
		QMapIterator<QString, QVariant> i(m);
		QString json="{";
		QString s="";
		bool simpleType;
		
		qDebug() << "Map";
		
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
		
		return str;
	}
	//------------------------------------------------------------------------------
} //namespace
//------------------------------------------------------------------------------