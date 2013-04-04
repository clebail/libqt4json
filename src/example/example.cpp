#include <libqt4json.h>
#include <QApplication>
#include <QVariant>
#include <QRegExp>
#include <iostream>
#include "CPerson.h"
#include "CJsonView.h"

using libqt4json::CJson;
using namespace std;

QString indent(QString json);
QString variantToString(QVariant variant, int level=0, QString memberName=QString());
QString variantMapToString(QVariantMap vm, int level);
QString variantListToString(QVariantList vl, int level);

int main(int argc, char **argv) {
	int i;

	CJson *json=new CJson();
	CPerson *parent1=new CPerson("Dad", new CBirthDay(QDate::fromString("07/04/1977", "dd/MM/yyyy")));
	CPerson *parent2=new CPerson("Mum", new CBirthDay(QDate::fromString("15/07/1977", "dd/MM/yyyy")));
	CPerson *child1=new CPerson("Cindy", new CBirthDay(QDate::fromString("01/10/2011", "dd/MM/yyyy")));
	QVariantMap family;
	QVariantList parents;
	QVariantList childs;
	bool ok;
	QApplication app(argc, argv);
	CJsonView *jsonView=new CJsonView();
	
	parents.append(QVariant::fromValue((QObject *)parent1));
	parents.append(QVariant::fromValue((QObject *)parent2));
	
	childs.append(QVariant::fromValue((QObject *)child1));
	
	family.insert("parents", QVariant(parents));
	family.insert("childs", QVariant(childs));
	
	QString sJson=indent(json->toString(QVariant(family)));
	
	/*cout << QObject::tr("Generated json").toStdString() << ":" << endl;
	cout << sJson.toStdString();
	cout << endl;

	QVariant variant=json->fromString(sJson, ok);
	if(!ok) {
		cout << json->getLastError().toStdString() << endl;
	}else {
		cout << QObject::tr("Generated QVariant").toStdString() << ":" << endl;
		cout << variantToString(variant).toStdString() << endl;
	}*/

	jsonView->setJson(sJson);
	jsonView->show();

	int ret=app.exec();

	delete child1;
	delete parent2;
	delete parent1;
	delete json;
	delete jsonView;
	
	return ret;
}

QString indent(QString json) {
	int level=0;
	int oldPos=0;
	int newPos;
	QString ret="";
	
	while((newPos=json.indexOf(QRegExp("\\[|\\{|\\]|\\}|\\,"), oldPos)) != -1) {
		switch(json[newPos].toAscii()) {
			case '[':
			case '{':
				ret+=QString(level, QChar('\t'))+json.mid(oldPos, newPos-oldPos+1).trimmed()+"\r\n";
				level++;
				break;
			case ',':
				ret+=QString(level, QChar('\t'))+json.mid(oldPos, newPos-oldPos+1).trimmed()+"\r\n";
				break;
			default:
				ret+=QString(level, QChar('\t'))+json.mid(oldPos, newPos-oldPos).trimmed()+"\r\n";
				level--;
				ret+=QString(level, QChar('\t'))+json[newPos]+"\r\n";
		}
		oldPos=newPos+1;
	}
	
	return ret;
}

QString variantToString(QVariant variant, int level, QString memberName) {
	QString ret="";
	QString tab=QString(level, QChar('\t'));
	
	memberName=QString("(")+QString(variant.typeName())+QString(") ")+memberName+QString(": ");
	switch(variant.type()) {
		case QVariant::Double:
		case QVariant::Int:
		case QVariant::LongLong:
			ret=tab+memberName+variant.toString();
			break;
		case QVariant::List:
			ret=tab+memberName+"\n"+variantListToString(variant.toList(), level+1);
			break;
		case QVariant::Map:
			ret=tab+memberName+"\n"+variantMapToString(variant.toMap(), level+1);
			break;
		default:
			if(variant.canConvert<QString>()) {
				ret=tab+memberName+variant.toString();
			}else {
				ret=tab+memberName+"Unkonwn type";
			}
			break;
	}
	
	return ret+"\n";
}

QString variantMapToString(QVariantMap vm, int level) {
	QMapIterator<QString, QVariant> i(vm);
	QString ret="";
		
	while (i.hasNext()) {
		i.next();
		ret+=variantToString(i.value(), level, i.key());
	}
	
	return ret;
}

QString variantListToString(QVariantList vl, int level) {
	int i;
	QString ret="";
		
	for(i=0;i<vl.size();i++) {
		ret+=variantToString(vl.at(i), level);
	}
	
	return ret;
}
