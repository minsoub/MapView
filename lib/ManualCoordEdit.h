/*
 * ManualCoordEdit.h
 *
 *  Created on: 2012. 3. 2.
 *      Author: HIST002
 */

#ifndef MANUALCOORDEDIT_H_
#define MANUALCOORDEDIT_H_
#include <QtGui>
#include "../lib_layer/MapDefine.h"

class ManualCoordEdit : public QDialog {
	Q_OBJECT
public:
	ManualCoordEdit(QWidget* parent=0);
	void clearAll();
	AUserLayerId* getUsermap();		// 결과를 userlayerid에 담아서 리턴한다.
	QChar getDrawType();
	QString getSymbol() const { return symbolFile; }
private:
	QChar drawtype;
	AUserLayerId* layerid;
	QString symbolFile;
	QRadioButton* radioPolyline;
	QRadioButton* radioPolygon;
	QRadioButton* radioCircle;
	QRadioButton* radioSymbol;
	QComboBox*    comboBoundaryVia;
	QGroupBox*    groupPoint;
	QGroupBox*    groupArcCircle;
	QLineEdit*    editPointLat;
	QLineEdit*    editPointLon;
	QLineEdit*    editCenterLat;
	QLineEdit*    editCenterLon;
	QLineEdit*    editDistance;
	QLineEdit*    editBearing;
	QLineEdit*    editSymbol;
	QPushButton*  buttonInsert;
	QPushButton*  buttonUpdate;
	QPushButton*  buttonDelete;
	QPushButton*  buttonClear;
	QPushButton*  buttonDone;
	QPushButton*  buttonCancel;
	QPushButton*  buttonSymbol;

	QTableWidget* tableList;
	void insertRow();
	void editToRow(int rowNo);
private slots:
	void insertPoint();
	void updatePoint();
	void deletePoint();
	void clearPoints();
	void done();
	void onViacomboChanged();
	void currentRowToEdit();
	void circleradioclick(bool);
	bool check();
	void polylineradioclick(bool);
	void polygonradioclick(bool);
	void symbolradioclick(bool);
	void selectSymbol();
signals:
	void manualeditchanged();
	void manualeditdone();
};

#endif /* MANUALCOORDEDIT_H_ */
