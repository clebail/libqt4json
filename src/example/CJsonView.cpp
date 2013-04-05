//------------------------------------------------------------------------------
#include <QPainter>
#include "CJsonView.h"
//------------------------------------------------------------------------------
void CJsonView::setJson(QString json) {
	CJson *cJson=new CJson();
	bool ok;

	this->json=cJson->fromString(json, ok);
	makeItems();
	update();
}
//------------------------------------------------------------------------------
void CJsonView::paintEvent(QPaintEvent *event) {
	QPainter painter(this);
	
	painter.setPen(Qt::white);
	painter.setBrush(Qt::white);
	painter.drawRect(rect());
}
//------------------------------------------------------------------------------
void CJsonView::makeItems(void) {
}
//------------------------------------------------------------------------------
