#include <libqt4json.h>
#include <QApplication>
#include <QVariant>
#include <QRegExp>
#include <QTextCodec>
#include <QtDebug>
#include <QFile>
#include <QTextStream>
#include <iostream>
#include "CPerson.h"
#include "CJsonView.h"

using libqt4json::CJson;
using namespace std;

int main(int argc, char **argv) {
	int i;

	QTextCodec::setCodecForTr(QTextCodec::codecForName("utf8"));
	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("utf8"));

	CJson *json=new CJson();
	bool ok;
	
	QString sJson = "";
	QFile file("testBig.json");
	if(file.open(QIODevice::ReadOnly)) {
		QTextStream in(&file);
	
		while(!in.atEnd()) {
			QString line = in.readLine();
			sJson.append(line);	
		}

		file.close();
	}
	qDebug() << QDateTime::currentDateTime();

	QVariant variant=json->fromString(sJson, ok);
	if(!ok) {
		cout << json->getLastError().toStdString() << endl;
	}
	
	qDebug() << QDateTime::currentDateTime();

	delete json;
	
	return 0;
}
