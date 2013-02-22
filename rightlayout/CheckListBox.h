/*
 * CheckListBox.h
 *
 *  Created on: 2012. 2. 29.
 *      Author: HIST002
 */

#ifndef CHECKLISTBOX_H_
#define CHECKLISTBOX_H_

#include <QtGui>

class CheckListBox : public QWidget {
	Q_OBJECT
public:
	CheckListBox(QWidget* parent = 0);
	void add(const QString& s, bool checked = false);
	void checkAll() { setCheck(true); }
	void uncheckAll() { setCheck(false); }
	int checkedCount();
	void clearAll();
	QString deleteCheckedItem();
	void changeCurrentData(const QString& newdata);
	QString currentText() const { return currenttext; }
	QString getText(int i) const;
	int count() const;
private:
	QListView* checkListBox;
	QString currenttext;
	QStandardItemModel* model;
	void setCheck(bool checked);
private slots:
	void OnSelectedIndexChanged(const QModelIndex& current, const QModelIndex& prev);
signals:
	void currentRowChanged(QString uid);
};

#endif /* CHECKLISTBOX_H_ */
