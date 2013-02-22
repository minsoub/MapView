/*
 * CustomItemDelegate.cpp
 *
 *  Created on: 2012. 4. 27.
 *      Author: JMS
 *  Description : QTableView 에 출력될 양식을 설정한다.
 *                     그리드에 출력되는 체크박스와 콤보박스를 정의한다.
 */
#include <QtCore>
#include "CustomItemDelegate.h"

CustomItemDelegate::CustomItemDelegate(QObject* parent) : QItemDelegate(parent) {
	// TODO Auto-generated constructor stub

	checkBoxColumn    = -1;		// QCheckBox column field number.
	comboSymbolColumn = 5;	   // SymbolTypeCombo column field number.
	comboBoxColumn    = 6;		// ColorComboBox column field number.
	textBoxColumn     = 7;		// QTextBox column field number
	//qDebug() << "CustomItemDelegate called....";
}

CustomItemDelegate::~CustomItemDelegate()
{

}

void CustomItemDelegate::emitCommitData()
{
     emit commitData(qobject_cast<QWidget *>(sender()));
}

QWidget* CustomItemDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem &option,
		const QModelIndex& index) const
{
	//qDebug() << "createEditor : " << index.column();

	if (index.isValid() && index.column() == checkBoxColumn)
	{
		QCheckBox *editor = new QCheckBox(parent);
		editor->installEventFilter(const_cast<CustomItemDelegate*>(this));
		return editor;
	}else if(index.isValid() && index.column() == comboBoxColumn)
	{
		ColorTypeCombo* editor = new ColorTypeCombo(parent);
		editor->setCurrentIndex(-1);
		//editor->setMinimumWidth(120);
		connect(editor, SIGNAL(activated(int)), this, SLOT(emitCommitData()));

		return editor;
	}else if(index.isValid() && index.column() == comboSymbolColumn)
	{
		SymbolTypeCombo* editor = new SymbolTypeCombo(parent);
		editor->setCurrentIndex(-1);
		//editor->setMinimumWidth(120);
		connect(editor, SIGNAL(activated(int)), this, SLOT(emitCommitData()));

		return editor;
	}else if(index.isValid() && index.column() == textBoxColumn) {
		QLineEdit* editor = new QLineEdit(parent);
		QRegExp reg("[0-9]{5}");
		editor->setValidator(new QRegExpValidator(reg, parent));
		connect(editor, SIGNAL(editingFinished()), this, SLOT(commitAndCloseEditor()));
		//editor->installEventFilter(const_cast<CustomItemDelegate*>(this));
		return editor;
	}else {
		return QItemDelegate::createEditor(parent, option, index);
	}
}

/**
 * When the user is done editing, we emit commitData() and closeEditor() (both declared in QAbstractItemDelegate),
 * to tell the model that there is edited data and to inform the view that the editor is no longer needed.
 * The setEditorData() function is called when an editor is created to initialize it with data from the model:
 * @param editor
 * @param index
 */
void CustomItemDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const
{
	//qDebug() << "setEditorData" << index.column();
	if (index.isValid() && index.column() == checkBoxColumn)
	{
		QString value = index.model()->data(index, Qt::DisplayRole).toString();

		//qDebug() << value;
		QCheckBox *checkBox = static_cast<QCheckBox*>(editor);
		if (value == "Y") {
			checkBox->setCheckState(Qt::Checked);
		}else {
			checkBox->setCheckState(Qt::Unchecked);
		}
	}else if(index.isValid() && index.column() == comboBoxColumn)
	{
		ColorTypeCombo* comboBox = static_cast<ColorTypeCombo*>(editor);
		if (index.model()->data(index, Qt::DisplayRole).toString() == "") {
			comboBox->setCurrentIndex(-1);
		}else {
			comboBox->setCurrentIndex(index.model()->data(index, Qt::DisplayRole).toInt());
		}
	}else if(index.isValid() && index.column() == comboSymbolColumn)
	{
		QString findData;

		//qDebug() << "UserRole : " << index.model()->data(index, Qt::UserRole).toString();
		//qDebug() << "DisplayRole : " << index.model()->data(index, Qt::DisplayRole).toString();

		SymbolTypeCombo* comboBox = static_cast<SymbolTypeCombo*>(editor);

		if (index.model()->data(index, Qt::DisplayRole).toString() == "") {
			findData = index.model()->data(index, Qt::UserRole).toString();
			int idx = comboBox->getFindString(findData);
			comboBox->setCurrentIndex(idx);
		}else {
			comboBox->setCurrentIndex(index.model()->data(index, Qt::DisplayRole).toInt());
		}
	}else if(index.isValid() && index.column() == textBoxColumn)
	{
		QString tt = index.model()->data(index, Qt::DisplayRole).toString();  // qVariantValue<QString>(index.data());
		QLineEdit *starEditor = qobject_cast<QLineEdit *>(editor);
		starEditor->setText(tt);
	}else {
		QItemDelegate::setEditorData(editor, index);
	}
}

/**
 * Reimplemented from QAbstractItemDelegate::setModelData().
 * Gets data from the editor widget and stores it in the specified model at the item index.
 * he default implementation gets the value to be stored in the data model from the editor widget's user property.
 * See also QMetaProperty::isUser().
 */
void CustomItemDelegate::setModelData(QWidget* editor, QAbstractItemModel* model,
				const QModelIndex& index) const
{
	//qDebug() << "setModelData : " << index.column();
	if (index.isValid() && index.column() == checkBoxColumn)
	{
		QCheckBox* checkBox = static_cast<QCheckBox*>(editor);
		QString value;
		if (checkBox->checkState() == Qt::Checked) {
			value = "Y";
		}else {
			value = "N";
		}
		model->setData(index, value);		// Default :: DisplayRole = 0
	}else if(index.isValid() && index.column() == comboBoxColumn)
	{
		ColorTypeCombo *comboBox = static_cast<ColorTypeCombo*>(editor);
		model->setData(index, comboBox->currentIndex(), Qt::EditRole);
	}else if(index.isValid() && index.column() == comboSymbolColumn)
	{
		SymbolTypeCombo *comboBox = static_cast<SymbolTypeCombo*>(editor);
		model->setData(index, comboBox->currentIndex(), Qt::EditRole);
		//qDebug() << comboBox->currentText();
		model->setData(index, comboBox->currentText(), Qt::UserRole);
	}else if(index.isValid() && index.column() == textBoxColumn)
	{
		QLineEdit *starEditor = qobject_cast<QLineEdit *>(editor);
		//qDebug() << "data : " << starEditor->text();
		model->setData(index, qVariantFromValue(starEditor->text()), Qt::DisplayRole);
	}else {
		QItemDelegate::setModelData(editor, model, index);
	}
}

void CustomItemDelegate::updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option,
				const QModelIndex& index) const
{
	//qDebug() << "updateEditorGeometry : " << index.column();
	if (index.isValid() && ( index.column() == checkBoxColumn || index.column() == comboBoxColumn
				|| index.column() == comboSymbolColumn || index.column() == textBoxColumn ) )
	{
		editor->setGeometry(option.rect);
	}else {
		QItemDelegate::updateEditorGeometry(editor, option, index);
	}
}


void CustomItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	//qDebug() << "paint : " << index.column();

	if (index.isValid() && ( index.column() == comboBoxColumn || index.column() == comboSymbolColumn))
	{
		QStyleOptionViewItemV4 myOption = option;
		//QString text = "text1";
		//myOption.text = text;

		QApplication::style()->drawControl(QStyle::CE_ItemViewItem, &myOption, painter);

	}else {
		QItemDelegate::paint(painter, option, index);
	}
}


void CustomItemDelegate::commitAndCloseEditor()
{
	QLineEdit *editor = qobject_cast<QLineEdit *>(sender());
	emit commitData(editor);
	emit closeEditor(editor);
}
