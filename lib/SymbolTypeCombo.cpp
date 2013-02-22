/*
 * SymbolTypeCombo.cpp
 *
 *  Created on: 2012. 4. 27.
 *      Author: JMS
 *  Description : QComboBox를 상속받아 Symbol icon을 출력하는 콤보박스를 구현한다.
 */
#include <iostream>
#include "SymbolTypeCombo.h"

/**
 * 생성자
 * $MAP_DIR 에서 symbol 데이터를 읽어서 출력한다.
 */
SymbolTypeCombo::SymbolTypeCombo(QWidget* parent, const char* /*name*/): QComboBox(parent)
{
	readSymbolDir();
}

/**
 * 콤보박스에 아이콘과 이름을 등록한다.
 */
void SymbolTypeCombo::insertSymbolType(int index, const QIcon& icon, const QString& name)
{
	insertItem(index, icon, name, index);
}

/**
 * 심볼 개수를 리턴한다.
 */
int SymbolTypeCombo::symbolTypeCount() const
{
	return QComboBox::count();
}

void SymbolTypeCombo::setCurrentSymbolType(const int& icon)
{
	for (int i=0; i<symbolTypeCount(); i++) {
		if (SymbolTypeCombo::symbolType(i) == (int)icon) {
			setCurrentIndex(i);
			break;
		}
	}
}

int SymbolTypeCombo::currentSymbolType() const
{
	return qVariantValue<int>(itemData(currentIndex()));
}

int SymbolTypeCombo::symbolType(int index) const
{
	QVariant var = itemData(index);

	if (!var.isValid())
		return -1;

	return qVariantValue<int>(var);
}

/**
 * 주어진 파일명으로 콤보박스의 인덱스를 찾아서 리턴한다.
 */
int SymbolTypeCombo::getFindString(QString fileName)
{
	//qDebug() << "getFindString : " << fileName << findData(fileName, Qt::DisplayRole);
	return findData(fileName, Qt::DisplayRole);
}
/**
 * $MAP_DIR의 심볼 디렉토리에서 데이터를 읽어서 pixmap으로 구성해서 등록한다.
 */
void SymbolTypeCombo::readSymbolDir()
{
	QString symboldir = QString("%1/images").arg(ConfigParser::getInstance().envMapDir());

	QDir dir(symboldir);
	if (!dir.exists()) return;

	QStringList filters;
	filters += "*.xpm";

	QStringList xpmFileList = dir.entryList(filters, QDir::Files);

	//std::cout << "xpm size : " << xpmFileList.size() << "\n";
	//std::cout << "symboldir : " << symboldir.toStdString() << "\n";
	foreach(QString s, xpmFileList)
	{
		QString fullname = QString("%1%2%3").arg(symboldir).arg(QDir::separator()).arg(s);
		//std::cout << "full name : " << fullname.toStdString() << "\n";
		QPixmap icon(fullname);

		QPixmap batang(QSize(icon.width()+2, icon.height()+2));
		batang.fill(QColor(0, 0, 0));

		QPainter painter(&batang);
		painter.initFrom(this);
		painter.drawPixmap(1, 1, icon);

		addSymbolType(QIcon(batang), s);
	}
}
