/*
 * ColorTypeCombo.h
 *
 *  Created on: 2012. 4. 27.
 *      Author: JMS
 *  Description : QComboBox를 상속받아 Color icon을 출력하는 콤보박스를 구현한다.
 */

#ifndef COLORTYPECOMBO_H_
#define COLORTYPECOMBO_H_
#include <QtGui>
#include "GlobalColor.h"

class ColorTypeCombo : public QComboBox {
	Q_OBJECT
public:
	ColorTypeCombo(QWidget* parent=0, const char* name = 0);
	void insertColorType(int index, int& color, const QString& name);
	inline void addColorType(int& color, const QString& name)
	{
		insertColorType(colorTypeCount(), color, name);
	}
	int colorTypeCount() const;
	void setCurrentColorType(int& color);
	int currentColorType() const;
	int colorType(int index) const;
};

#endif /* COLORTYPECOMBO_H_ */
