/*
 * InputUserText.h
 *
 *  Created on: 2012. 2. 29.
 *      Author: HIST002
 */

#ifndef INPUTUSERTEXT_H_
#define INPUTUSERTEXT_H_

#include <QtGui>

class InputUserText : public QDialog {
	Q_OBJECT
public:
	InputUserText(QWidget* parent=0);
	InputUserText(QWidget* parent, int len, const QString& title, const QString& prompt);
	QString getText();
	void setMaxLength(int len);
	void setText(const QString& str);
	void setTitle(const QString& str);
private:
	int maxlength;
	QLabel* label;
	QLineEdit* lineEdit;
	QPushButton* okButton;
	QPushButton* cancelButton;
	void setUp();
private slots:
	void enableOkButton(const QString& text1);
};

#endif /* INPUTUSERTEXT_H_ */
