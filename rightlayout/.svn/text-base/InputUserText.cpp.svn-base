/*
 * InputUserText.cpp
 *
 *  Created on: 2012. 2. 29.
 *      Author: HIST002
 */

#include "InputUserText.h"

InputUserText::InputUserText(QWidget* parent, int len, const QString& title, const QString& prompt): QDialog(parent)
{
	// TODO Auto-generated constructor stub
	setUp();
	setWindowTitle(title);
	label->setText(prompt);
	lineEdit->setMaxLength(len);
}

InputUserText::InputUserText(QWidget* parent) : QDialog(parent)
{
	// TODO Auto-generated destructor stub
	setUp();
}

void InputUserText::setUp()
{
	label = new QLabel(tr("User Text"));
	lineEdit = new QLineEdit;
	lineEdit->setMaxLength(100);
	label->setBuddy(lineEdit);

	okButton = new QPushButton(tr("&Ok"));
	okButton->setDefault(true);
	okButton->setEnabled(false);

	cancelButton = new QPushButton(tr("&Cancel"));

	connect(lineEdit, SIGNAL(textChanged(const QString&)), this, SLOT(enableOkButton(const QString &)));
	connect(okButton, SIGNAL(clicked()), this, SLOT(accept()));
	connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));

	QHBoxLayout *h1 = new QHBoxLayout;
	h1->addWidget(label);
	h1->addWidget(lineEdit);

	QHBoxLayout *h2 = new QHBoxLayout;
	h2->addStretch();
	h2->addWidget(okButton);
	h2->addWidget(cancelButton);
	h2->addStretch();

	QVBoxLayout *v1 = new QVBoxLayout;
	v1->addLayout(h1);
	v1->addLayout(h2);
	setLayout(v1);
	setFixedHeight(sizeHint().height());
}

void InputUserText::enableOkButton(const QString& text1)
{
	okButton->setEnabled(!text1.isEmpty());
}

QString InputUserText::getText()
{
	return lineEdit->text();
}

void InputUserText::setText(const QString& str)
{
	lineEdit->setText(str);
}

void InputUserText::setMaxLength(int len)
{
	lineEdit->setMaxLength(len);
}

void InputUserText::setTitle(const QString& str)
{
	setWindowTitle(str);
}
