/*
 * SymbolTypeCombo.h
 *
 *  Created on: 2012. 4. 27.
 *      Author: JMS
 *  Description : QComboBox를 상속받아 Symbol icon을 출력하는 콤보박스를 구현한다.
 */

#ifndef SYMBOLTYPECOMBO_H_
#define SYMBOLTYPECOMBO_H_
#include <QtGui>
#include "ConfigParser.h"

class SymbolTypeCombo : public QComboBox {
	Q_OBJECT
public:
	SymbolTypeCombo(QWidget* parent=0, const char* name = 0);
	void insertSymbolType(int index, const QIcon& icon, const QString& name);
	inline void addSymbolType(const QIcon& icon, const QString& name)
	{
		insertSymbolType(symbolTypeCount(), icon, name);
	}
	int symbolTypeCount() const;
	void setCurrentSymbolType(const int& icon);
	int currentSymbolType() const;
	int symbolType(int index) const;
	int getFindString(QString fileName);
private:
	void readSymbolDir();
};


#endif /* SYMBOLTYPECOMBO_H_ */
