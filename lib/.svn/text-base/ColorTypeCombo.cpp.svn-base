/*
 * ColorTypeCombo.cpp
 *
 *  Created on: 2012. 4. 27.
 *      Author: JMS
 *  Description : QComboBox를 상속받아 Color icon을 출력하는 콤보박스를 구현한다.
 */

#include "ColorTypeCombo.h"


ColorTypeCombo::ColorTypeCombo(QWidget* parent, const char* /*name*/ ): QComboBox(parent)
{

	for (int i=0; i< GlobalColorCount; i++) {
		addColorType(i, userColor[i]);
	}
}
void ColorTypeCombo::insertColorType(int index, int& color, const QString& name)
{
	setIconSize(QSize(50, 13));
	QPixmap pix(50, 13);
	QPainter painter(&pix);
	painter.setBrush(QBrush(userRGBColor[color]));
	painter.setPen(Qt::NoPen);
	painter.drawRect(0, 0, 50, 13);

	QIcon icon;
	icon.addPixmap(pix);

	insertItem(index, icon, name, color);
}

/**
 * 입력된 콤보박스의 개수를 리턴한다.
 */
int ColorTypeCombo::colorTypeCount() const
{
	return QComboBox::count();
}

/**
 * 선택된 데이터의 인덱스를 리턴한다.
 */
void ColorTypeCombo::setCurrentColorType(int& color)
{
	for (int i=0; i<colorTypeCount(); i++) {
		if (ColorTypeCombo::colorType(i) == color) {
			setCurrentIndex(i);
			break;
		}
	}
}

/**
 * 현재 선택된 컬러 타입을 리턴한다.
 */
int ColorTypeCombo::currentColorType() const
{
	return qVariantValue<int>(itemData(currentIndex()));
}

/**
 * 주어진 인덱스의 컬러 타입을 리턴한다.
 */
int ColorTypeCombo::colorType(int index) const
{
	QVariant var = itemData(index);

	if (!var.isValid())
		return (int)-1;

	return qVariantValue<int>(var);
}
