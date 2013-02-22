/*
 * CheckClickLabel.cpp
 *
 *  Created on: 2012. 2. 24.
 *      Author: HIST002
 */
#include <QtGui>
#include <cmath>
#include "CheckClickLabel.h"

CheckClickLabel::CheckClickLabel(QWidget* parent, int LayerNo, QString& text)
:QWidget(parent)
{
	// TODO Auto-generated constructor stub
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);

	layerno = LayerNo;
	layername = text;

	QHBoxLayout* hbox = new QHBoxLayout;

	checkbox = new LayerCheckBox(this, LayerNo);
	label = new ClickableLabel(this, LayerNo, text);
	connect(label, SIGNAL(clicked(int)), this, SLOT(labelclick(int)));
	connect(checkbox, SIGNAL(clicked(int)), this, SLOT(checkclick(int)));

	hbox->addWidget(checkbox);
	hbox->addWidget(label);
	hbox->addStretch();  // Adds a stretchable space with zero minimum size and stretch factor stretch to the end of this box layout.

	setLayout(hbox);
}

void CheckClickLabel::labelclick(int layerno)
{
	emit labelclicked(layerno);
}

void CheckClickLabel::checkclick(int layerno)
{
	emit checkclicked(layerno);
}

QSize CheckClickLabel::sizeHint() const
{
	return QSize(50, 10);
}
