/*
 * FillPatternCombo.h
 *
 *  Created on: 2012. 2. 29.
 *      Author: HIST002
 */

#ifndef FILLPATTERNCOMBO_H_
#define FILLPATTERNCOMBO_H_

#include <QtGui>

class FillPatternCombo : public QComboBox {
public:
	FillPatternCombo(QWidget* parent=0, const char* name = 0);
	void insertFillPattern(int index, const Qt::BrushStyle& brushstyle, const QString& name);
	inline void addFillPattern(const Qt::BrushStyle& brushstyle, const QString& name)
	{
		insertFillPattern(fillpatternCount(), brushstyle, name);
	}
	int fillpatternCount() const;
	void setCurrentFillPattern(const Qt::BrushStyle& brushstyle);
	int currentFillPattern() const;
	int fillpattern(int index) const;
};

#endif /* FILLPATTERNCOMBO_H_ */
