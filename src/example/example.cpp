#include <libqt4json.h>
#include <QVariant>
#include <QRegExp>
#include <iostream>

using libqt4json::CJson;
using namespace std;

QString indent(QString json);
QString variantToString(QVariant variant);

int main(int argc, char **argv) {
	CJson *json=new CJson();
	QVariantList vl;
	QVariantMap vm;
	
	vl.append(35);
	vl.append("Corentin");
	
	vm.insert("day", 7);
	vm.insert("month", "April");
	vm.insert("year", 1977);
	
	vl.append(QVariant(vm));
	
	QString sJson=json->toString(QVariant(vl));
	QVariant variant=json->fromString(sJson);
	
	cout << QObject::tr("Generated json").toStdString() << ":" << endl;
	cout << indent(sJson).toStdString();
	cout << endl;
	cout << QObject::tr("Generated QVariant").toStdString() << ":" << endl;
	cout << variantToString(variant).toStdString() << endl;
	
	delete json;
	
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