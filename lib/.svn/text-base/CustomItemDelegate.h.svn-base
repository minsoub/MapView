/*
 * CustomItemDelegate.h
 *
 *  Created on: 2012. 4. 27.
 *      Author: JMS
 *  Description : QTableView 에 출력될 양식을 설정한다.
 *                     그리드에 출력되는 체크박스와 콤보박스를 정의한다.
 */

#ifndef CUSTOMITEMDELEGATE_H_
#define CUSTOMITEMDELEGATE_H_
#include <QItemDelegate>
#include <QCheckBox>
#include <QLineEdit>
#include <QObject>
#include <QComboBox>
#include <QWidget>
#include <QModelIndex>
#include <QApplication>
#include <QString>

#include "ColorTypeCombo.h"
#include "SymbolTypeCombo.h"

class CustomItemDelegate : public QItemDelegate {

	Q_OBJECT

public:
	CustomItemDelegate(QObject* parent = 0);
	~CustomItemDelegate();
   QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const;

   void setEditorData(QWidget *editor, const QModelIndex &index) const;
   void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const;

   void updateEditorGeometry(QWidget *editor,
        const QStyleOptionViewItem &option, const QModelIndex &index) const;
   void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

private slots:
	void emitCommitData();
	void commitAndCloseEditor();
private:
	int checkBoxColumn;
	int comboBoxColumn;
	int comboSymbolColumn;
	int textBoxColumn;
};

#endif /* CUSTOMITEMDELEGATE_H_ */
