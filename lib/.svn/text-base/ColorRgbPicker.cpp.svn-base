/*
 * ColorRgbPicker.cpp
 *
 *  Created on: 2012. 2. 29.
 *      Author: HIST002
 */

#include "ColorRgbPicker.h"

ColorRgbPicker::ColorRgbPicker(QWidget* parent) : QWidget(parent) {
	// TODO Auto-generated constructor stub
	labelR = new QLabel(tr("R"));
	labelG = new QLabel(tr("G"));
	labelB = new QLabel(tr("B"));

	spinboxR = new QSpinBox;
	spinboxR->setMinimum(0);
	spinboxR->setMaximum(255);
	spinboxR->setValue(255);

	spinboxG = new QSpinBox;
	spinboxG->setMinimum(0);
	spinboxG->setMaximum(255);
	spinboxG->setValue(255);

	spinboxB = new QSpinBox;
	spinboxB->setMinimum(0);
	spinboxB->setMaximum(255);
	spinboxB->setValue(255);

	connect(spinboxR, SIGNAL(valueChanged(int)), this, SLOT(setColor()));
	connect(spinboxG, SIGNAL(valueChanged(int)), this, SLOT(setColor()));
	connect(spinboxB, SIGNAL(valueChanged(int)), this, SLOT(setColor()));

	pixmap = new QPixmap(20, 20);
	pixmap->fill(QColor(0, 0, 0));
	labelDisplay = new QLabel;
	labelDisplay->setPixmap(*pixmap);

	QHBoxLayout* hboxlayout = new QHBoxLayout;
	hboxlayout->addWidget(labelR);
	hboxlayout->addWidget(spinboxR);
	hboxlayout->addWidget(labelG);
	hboxlayout->addWidget(spinboxG);
	hboxlayout->addWidget(labelB);
	hboxlayout->addWidget(spinboxB);
	hboxlayout->addWidget(labelDisplay);

	setColor();
	setLayout(hboxlayout);
}

QColor ColorRgbPicker::color()
{
	return QColor::fromRgb(spinboxR->value(), spinboxG->value(), spinboxB->value());
}

void ColorRgbPicker::setColor()
{
	int r = spinboxR->value();
	int g = spinboxG->value();
	int b = spinboxB->value();

	QPixmap* p = (QPixmap*)labelDisplay->pixmap();
	p->fill(QColor::fromRgb(r, g, b));
	labelDisplay->update();
	emit changed();
}

void ColorRgbPicker::setColor(int r, int g, int b)
{
	spinboxR->setValue(r);
	spinboxG->setValue(g);
	spinboxB->setValue(b);

	setColor();
}

void ColorRgbPicker::setColor(const QColor& color)
{
	int r, g, b;
	color.getRgb(&r, &g, &b);

	setColor(r, g, b);
}

void ColorRgbPicker::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton) {
		QRect rect = labelDisplay->frameRect();

		QColor color = QColorDialog::getColor(Qt::green, this);
		if (color.isValid()) {
			int r, g, b;
			color.getRgb(&r, &g, &b);
			setColor(r, g, b);
		}
	}
}
