//------------------------------------------------------------------------------
#include <QMetaProperty>
#include "libqt4json.h"
//------------------------------------------------------------------------------
namespace libqt4json {
	//------------------------------------------------------------------------------
	QString CJson::toString(QObject *object) {
		QString json="{";
		QString s="";

		const QMetaObject *metaObject=object->metaObject();
		for(int i=metaObject->propertyOffset();i<metaObject->propertyCount();i++) {
			QMetaProperty property=metaObject->property(i);

			json+=s+"\""+property.name()+"\": "+variantToString(property.read(object));
			s=", ";
		}
		json+="}";
		
		return json;
	}
	//------------------------------------------------------------------------------
	QString CJson::variantToString(QVariant variant) {
		switch(variant.type()) {
			case QVariant::Double:
			case QVariant::Int:
			case QVariant::LongLong:
				return variant.toString();
			case QMetaType::QObjectStar:
				return objectStarToString(variant);
			case QVariant::List:
				return listToString(variant);
			case QVariant::Map:
				return mapToString(variant);
			default:
				return "\""+protect(variant.toString())+"\"";
		}
	}
	//------------------------------------------------------------------------------
	QString CJson::objectStarToString(QVariant variant) {
		QObject *object=qvariant_cast<QObject *>(variant);
		
		if(object != 0) {
			return toString(object);
		}
		
		return "";
	}
	//------------------------------------------------------------------------------
	QString CJson::listToString(QVariant variant) {
		QVariantList l=qvariant_cast<QVariantList>(variant);
		int i;
		QString json="[";
		QString s="";
		
		for(i=0;i<l.size();i++) {
			json+=s+variantToString(l.at(i));
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
		
		while (i.hasNext()) {
			i.next();
			json+=s+"\""+i.key()+"\": "+variantToString(i.value());
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