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
	vm.insert("month", 4);
	vm.insert("year", 1977);
	
	vl.append(QVariant(vm));
	
	qDebug() << json->toString(QVariant(vl));
	
	delete json;
	
	return 0;
}