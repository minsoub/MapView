/*
 * LineTypeCombo.h
 *
 *  Created on: 2012. 2. 29.
 *      Author: HIST002
 */

#ifndef LINETYPECOMBO_H_
#define LINETYPECOMBO_H_

#include <QtGui>

class LineTypeCombo : public QComboBox {
	Q_OBJECT
public:
	LineTypeCombo(QWidget* parent=0, const char* name = 0);
	void insertLineType(int index, const Qt::PenStyle& penstyle, const QString& name);
	inline void addLineType(const Qt::PenStyle& penstyle, const QString& name)
	{
		insertLineType(linetypeCount(), penstyle, name);
	}
	int linetypeCount() const;
	void setCurrentLineType(const Qt::PenStyle& penstyle);
	int currentLineType() const;
	int linetype(int index) const;
};

#endif /* LINETYPECOMBO_H_ */
