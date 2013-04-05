//------------------------------------------------------------------------------
#ifndef __CJSONVIEW_H__
#define __CJSONVIEW_H__
//------------------------------------------------------------------------------
#include <QWidget>
#include <libqt4json.h>
//------------------------------------------------------------------------------
using namespace libqt4json;
//------------------------------------------------------------------------------
class CJsonViewItem {
	public:
		CJsonViewItem(QVariant varaint) {}
		int getWidth(void) { return 0; }
		bool isExpanded(void) { return false; }
		void setExpanded(bool expanded) {}
		QVariant getValue(void) { return QVariant(); }
};
//------------------------------------------------------------------------------
class CJsonView : public QWidget {
	public:
		void setJson(QString json);
	protected:
		virtual void paintEvent(QPaintEvent *event);
	private:
		QVariant json;
		
		void makeItems(void);
};
//------------------------------------------------------------------------------
#endif //__CJSONVIEW_H__
//------------------------------------------------------------------------------
