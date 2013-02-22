/*
 * CheckListBox.cpp
 *
 *  Created on: 2012. 2. 29.
 *      Author: HIST002
 */

#include "CheckListBox.h"

CheckListBox::CheckListBox(QWidget* parent):QWidget(parent) {
	// TODO Auto-generated constructor stub
	model = new QStandardItemModel;

	QVBoxLayout* vBox = new QVBoxLayout;

	checkListBox = new QListView;
	checkListBox->setModel(model);
	checkListBox->setSelectionMode(QAbstractItemView::SingleSelection);

	QItemSelectionModel* sm = checkListBox->selectionModel();
	connect(sm, SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this, SLOT(OnSelectedIndexChanged(QModelIndex, QModelIndex)));

	vBox->addWidget(checkListBox);
	setLayout(vBox);
}

void CheckListBox::add(const QString& s, bool checked)
{
	Qt::CheckState cs = checked ? Qt::Checked : Qt::Unchecked;

	QStandardItem* item = new QStandardItem(s);
	item->setCheckable(true);
	item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
	item->setData(QVariant(cs), Qt::CheckStateRole);
	model->appendRow(item);
}

void CheckListBox::setCheck(bool checked)
{
	Qt::CheckState cs = checked ? Qt::Checked : Qt::Unchecked;
	for (int i=0; i<model->rowCount(); i++) {
		QStandardItem* item = model->item(i);
		item->setCheckState(cs);
	}
}

/**
 * check된 개수를 리턴한다
 */
int CheckListBox::checkedCount()
{
	int count = 0;
	for (int i=0; i<model->rowCount(); i++) {
		QStandardItem* item = model->item(i);
		if (item->checkState() == Qt::Checked) {
			count++;
		}
	}
	return count;
}

QString CheckListBox::getText(int index) const
{
	if (index < model->rowCount() && index >= 0) {
		QStandardItem* item = model->item(index);
		QStringList tmp = item->text().split(":");
		return tmp[0];
	}
	return QString("");
}

/**
 * 체크된 것들을 지우고 그 id를 :로 엮어서 리턴한다.
 */
QString CheckListBox::deleteCheckedItem()
{
	QString s = QString("");
	for (int i=model->rowCount()-1; i>=0; i--)
	{
		QStandardItem* item = model->item(i);
		if (item->checkState() == Qt::Checked) {
			QStringList tmp = item->text().split(":");
			s += QString("%1;").arg(tmp[0]);
			model->removeRow(i);
		}
	}
	if (s.length() > 0) {
		s = s.mid(0, s.length() - 1);
	}

	return s;
}

void CheckListBox::clearAll()
{
	model->clear();
}

void CheckListBox::changeCurrentData(const QString& newdata)
{
	QModelIndex idx = checkListBox->currentIndex();
	if (idx.isValid()) {
		model->setData(idx, QVariant(newdata));
	}
}

void CheckListBox::OnSelectedIndexChanged(const QModelIndex& current, const QModelIndex& prev)
{
	currenttext = current.data().toString();
	if (current != prev) {
		QString uid = current.data().toString();
		emit(currentRowChanged(uid));
	}
}
int CheckListBox::count() const
{
	int i = 0;
	if (model) {
		i = model->rowCount();
	}

	return i;
}
