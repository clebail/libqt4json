#include <libqt4json.h>
#include <QVariant>
#include <QtDebug>

using libqt4json::CJson;

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
	qDebug() << sJson;
	sJson="[35, \"corentin\", {\"day\": 7, \"month\": \"April\", \"year\": 1977}]";
	qDebug() << sJson;
	qDebug() << json->fromString(sJson);
	
	delete json;
	
	return 0;
}