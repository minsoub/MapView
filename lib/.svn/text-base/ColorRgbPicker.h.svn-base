/*
 * ColorRgbPicker.h
 *
 *  Created on: 2012. 2. 29.
 *      Author: HIST002
 */

#ifndef COLORRGBPICKER_H_
#define COLORRGBPICKER_H_

#include <QtGui>

class ColorRgbPicker : public QWidget {
	Q_OBJECT
public:
	ColorRgbPicker(QWidget* parent = 0);
	QColor color();
public slots:
	void setColor();
	void setColor(int r, int g, int b);
	void setColor(const QColor& color);
signals:
	void changed();
protected:
	void mousePressEvent(QMouseEvent* event);
private:
	QLabel* labelR;
	QLabel* labelG;
	QLabel* labelB;
	QSpinBox* spinboxR;
	QSpinBox* spinboxG;
	QSpinBox* spinboxB;
	QLabel* labelDisplay;
	QPixmap* pixmap;
};

#endif /* COLORRGBPICKER_H_ */
