//------------------------------------------------------------------------------
#include <QMetaProperty>
#include <QtDebug>
#include <sstream>
#include <json.h>
#include "libqt4json.h"
#include "CCommon.h"
//------------------------------------------------------------------------------
namespace libqt4json {
	//------------------------------------------------------------------------------
	static QVariant jsonParse(json_object *jObj);
	//------------------------------------------------------------------------------
    static QVariant jsonParseObject(json_object *jObj) {
        QVariantMap map;

		struct json_object_iterator it;
        struct json_object_iterator itEnd;

        it = json_object_iter_begin(jObj);
        itEnd = json_object_iter_end(jObj);

        while(!json_object_iter_equal(&it, &itEnd)) {
			QString key = QString(json_object_iter_peek_name(&it));

			map.insert(key, jsonParse(json_object_iter_peek_value(&it)));

            json_object_iter_next(&it);
        }

        return map;
    }
    //------------------------------------------------------------------------------
    static QVariant jsonParseArray(json_object *jObj) {
		QVariantList list;
		struct array_list *aList = json_object_get_array(jObj);
		int len = json_object_array_length(jObj);
		int i;

		for(i=0;i<len;i++) {
			json_object *val = json_object_array_get_idx(jObj, i);

			list.append(jsonParse(val));
		}

        return list;
    }
	//------------------------------------------------------------------------------
	static QVariant jsonParse(json_object *jObj) {
		switch(json_object_get_type(jObj)) {
			case json_type_null:
				return QVariant(QVariant::Invalid);
			case json_type_boolean:
				return QVariant((bool)json_object_get_boolean(jObj));
			case json_type_double:
				return QVariant(json_object_get_double(jObj));
			case json_type_int:
				return QVariant(json_object_get_int(jObj));
			case json_type_object:
				return jsonParseObject(jObj);
			case json_type_array:
				return jsonParseArray(jObj);;
			case json_type_string:
				return QVariant(CCommon::fromUnicode(QString(json_object_get_string(jObj))));
		}
	}
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
		struct json_object *jObj = 0;
		struct json_tokener *tok = json_tokener_new();
		enum json_tokener_error jerr;
		QVariant ret;
		QString uJson = CCommon::toUnicode(json);

		do {
			jObj = json_tokener_parse_ex(tok, uJson.toAscii().data(), uJson.size());
		}while((jerr = json_tokener_get_error(tok)) == json_tokener_continue);

		if(jerr != json_tokener_success) {
			lastError = QString(json_tokener_error_desc(jerr));
			ok = false;
		}else {
			ret = jsonParse(jObj);
			ok = true;
		}

		json_tokener_free(tok);

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
		
		return CCommon::toUnicode(str);
	}
	//------------------------------------------------------------------------------
} //namespace
//------------------------------------------------------------------------------
