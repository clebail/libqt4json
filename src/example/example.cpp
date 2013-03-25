#include <libqt4json.h>
#include <QVariant>
#include <QRegExp>
#include <iostream>
#include "CPerson.h"

using libqt4json::CJson;
using namespace std;

QString indent(QString json);
QString variantToString(QVariant variant);

int main(int argc, char **argv) {
	CJson *json=new CJson();
	CPerson *parent1=new CPerson("Dad", new CBirthDay(QDate::fromString("07/04/1977", "dd/MM/yyyy")));
	CPerson *parent2=new CPerson("Mum", new CBirthDay(QDate::fromString("15/07/1977", "dd/MM/yyyy")));
	CPerson *child1=new CPerson("Cindy", new CBirthDay(QDate::fromString("01/10/2011", "dd/MM/yyyy")));
	QVariantMap family;
	QVariantList parents;
	QVariantList childs;
	bool ok;
	
	parents.append(QVariant::fromValue((QObject *)parent1));
	parents.append(QVariant::fromValue((QObject *)parent2));
	
	childs.append(QVariant::fromValue((QObject *)child1));
	
	family.insert("parents", QVariant(parents));
	family.insert("childs", QVariant(childs));
	
	QString sJson=json->toString(QVariant(family));
	
	cout << QObject::tr("Generated json").toStdString() << ":" << endl;
	cout << indent(sJson).toStdString();
	cout << endl;

	QVariant variant=json->fromString(sJson+"ff", ok);
	if(!ok) {
		cout << json->getLastError().toStdString() << endl;
	}else {
		cout << QObject::tr("Generated QVariant").toStdString() << ":" << endl;
		cout << variantToString(variant).toStdString() << endl;
	}
	
	return 0;
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

QString variantToString(QVariant variant) {
	QString ret="";
	return ret;
}
