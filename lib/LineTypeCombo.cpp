/*
 * LineTypeCombo.cpp
 *
 *  Created on: 2012. 2. 29.
 *      Author: HIST002
 */

#include "LineTypeCombo.h"

LineTypeCombo::LineTypeCombo(QWidget* parent, const char* /*name*/): QComboBox(parent) {
	// TODO Auto-generated constructor stub
	addLineType(Qt::SolidLine, tr("Solid"));
	addLineType(Qt::DashLine,  tr("Dash"));
	addLineType(Qt::DotLine,   tr("Dot"));
}

void LineTypeCombo::insertLineType(int index, const Qt::PenStyle& penstyle, const QString& name)
{
	setIconSize(QSize(50, 13));
	QPixmap pix(50, 13);
	QPainter painter(&pix);
	painter.setBrush(QBrush(Qt::gray));
	painter.setPen(Qt::NoPen);
	painter.drawRect(0, 0, 50, 13);

	QPen pen(Qt::black, 1, penstyle, Qt::RoundCap, Qt::RoundJoin);
	painter.setPen(pen);
	painter.drawLine(0, 6, 49, 6);
	QIcon icon;
	icon.addPixmap(pix);

	insertItem(index, icon, name, (int)penstyle);
}

int LineTypeCombo::linetypeCount() const
{
	return QComboBox::count();
}

int LineTypeCombo::currentLineType() const
{
	return qVariantValue<int>(itemData(currentIndex()));
}

void LineTypeCombo::setCurrentLineType(const Qt::PenStyle& penstyle)
{
	for (int i=0; i<linetypeCount(); i++) {
		if (LineTypeCombo::linetype(i) == (int)penstyle) {
			setCurrentIndex(i);
			break;
		}
	}
}

int LineTypeCombo::linetype(int index) const
{
	QVariant var = itemData(index);

	if (!var.isValid())
		return (int)Qt::NoPen;

	return qVariantValue<int>(var);
}


