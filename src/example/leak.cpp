#include <libqt4json.h>
#include <QApplication>
#include <QVariant>
#include <QTextCodec>
#include <QtDebug>
#include <iostream>
#include "CPerson.h"
#include "CJsonView.h"

using libqt4json::CJson;
using namespace std;

int main(int argc, char **argv) {
	int i;

	QTextCodec::setCodecForTr(QTextCodec::codecForName("utf8"));
	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("utf8"));

	for(int i=0;i<1000000;i++) {
		CJson *json=new CJson();
		bool ok;
		
		QString sJson = "[ 1, \"corentin\", { \"a\": true, \"b\": null, \"c\": 45.32 } ]";

		QVariant variant=json->fromString(sJson, ok);
		if(!ok) {
			cout << json->getLastError().toStdString() << endl;
		}else {
			//qDebug() << variant;
		}

		delete json;
	}
	
	return 0;
}
