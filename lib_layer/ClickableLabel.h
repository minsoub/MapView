/*
 * ClickableLabel.h
 *
 *  Created on: 2012. 1. 27.
 *      Author: HIST002
 */

#ifndef CLICKABLELABEL_H_
#define CLICKABLELABEL_H_

#include <QWidget>
#include <QLabel>
#include <QEvent>
#include <QPainter>
#include <QHoverEvent>
#include <QMessageBox>

class ClickableLabel : public QLabel
{
	Q_OBJECT

public:
	ClickableLabel(QWidget *parent = 0, int LayerNo = 0, const QString &text = QString("unknown")):QLabel(parent)
	{
		setAttribute(Qt::WA_Hover);
		layerno = LayerNo;
		setText(text);
		setFrameStyle(QFrame::NoFrame);
		pal = this->palette();
	}
protected:
	bool event(QEvent *e)
	{
		bool retVal = QLabel::event(e);
		if (e->type() == QEvent::MouseButtonPress)
		{
			emit clicked(layerno);
			retVal = true;
		}else if(e->type() == QEvent::MouseButtonRelease) {

		}else if(e->type() == QEvent::HoverEnter) {
			pal.setColor(QPalette::Foreground, Qt::blue);
			setPalette(pal);
		}else if(e->type() == QEvent::HoverLeave) {
			pal.setColor(QPalette::Foreground, pal.color(QPalette::Text));
			setPalette(pal);
		}
		return retVal;
	};
private:
	int layerno;
	QPalette pal;
signals:
	void clicked(int);
};

#endif /* CLICKABLELABEL_H_ */
