/*
 * FillPatternCombo.cpp
 *
 *  Created on: 2012. 2. 29.
 *      Author: HIST002
 */

#include "FillPatternCombo.h"

FillPatternCombo::FillPatternCombo(QWidget* parent, const char */*name*/): QComboBox(parent) {
	// TODO Auto-generated constructor stub
	addFillPattern(Qt::NoBrush,           tr("None"));
	addFillPattern(Qt::SolidPattern,      tr("Solid"));
	addFillPattern(Qt::Dense7Pattern,     tr("Dotted"));
	addFillPattern(Qt::HorPattern,        tr("Horizontal Line"));
	addFillPattern(Qt::VerPattern,        tr("Vertical Line"));
	addFillPattern(Qt::CrossPattern,      tr("Cross Line"));
	addFillPattern(Qt::BDiagPattern,      tr("Slashed"));
	addFillPattern(Qt::FDiagPattern,      tr("Reverse Slashed"));
	addFillPattern(Qt::DiagCrossPattern,  tr("Cross Slashed"));
}

void FillPatternCombo::insertFillPattern(int index, const Qt::BrushStyle& brushstyle, const QString& name)
{
	setIconSize(QSize(25, 25));
	QPixmap pix(25, 25);
	QPainter painter(&pix);
	painter.setBrush(QBrush(Qt::white, Qt::SolidPattern));
	painter.drawRect(0, 0, 24, 24);
	painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap));
	painter.setBrush(QBrush(Qt::black, brushstyle));
	painter.drawRect(0, 0, 24, 24);

	QIcon icon;
	icon.addPixmap(pix);

	insertItem(index, icon, name, (int)brushstyle);
}

int FillPatternCombo::fillpatternCount() const
{
	return QComboBox::count();
}

int FillPatternCombo::currentFillPattern() const
{
	return qVariantValue<int>(itemData(currentIndex()));
}

void FillPatternCombo::setCurrentFillPattern(const Qt::BrushStyle& brushstyle)
{
	for (int i=0; i<fillpatternCount(); i++) {
		if (FillPatternCombo::fillpattern(i) == (int)brushstyle) {
			setCurrentIndex(i);
			break;
		}
	}
}

int FillPatternCombo::fillpattern(int index) const
{
	QVariant var = itemData(index);

	if (!var.isValid())
		return (int)Qt::NoBrush;

	return qVariantValue<int>(var);
}
