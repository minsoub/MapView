/*
 * XpmPickerDialog.h
 *
 *  Created on: 2012. 3. 2.
 *      Author: HIST002
 */

#ifndef XPMPICKERDIALOG_H_
#define XPMPICKERDIALOG_H_

#include <QtGui>
/**
 * $MAP_DIR/images에 있는 xpm목록을 가져와서 아이콘과 함께 파일명을 보여주고 선택할 수 있게 한다.
 */
class XpmPickerDialog : public QDialog {
	Q_OBJECT
public:
	XpmPickerDialog(const QString& dir, QWidget* parent=0);
	void Refresh() { loadIcons(); }
	QString selectedSymbol() { return symbolname; }
	void done(int result);
public slots:
	void loadIcons();
private:
	QString symboldir;
	QString symbolname;
	QListView* listView;
	QStandardItemModel* model;
	QLabel* labelDir;
	QPushButton* buttonRefresh;
	QPushButton* buttonOk;
	QPushButton* buttonCancel;
};

#endif /* XPMPICKERDIALOG_H_ */
