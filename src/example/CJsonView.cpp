//------------------------------------------------------------------------------
#include "CJsonView.h"
//------------------------------------------------------------------------------
void CJsonView::setJson(QString json) {
	CJson *cJson=new CJson();
	bool ok;

	this->json=cJson->fromString(json, ok);
	update();
}
//------------------------------------------------------------------------------
void CJsonView::paintEvent(QPaintEvent *event) {
}
//------------------------------------------------------------------------------
