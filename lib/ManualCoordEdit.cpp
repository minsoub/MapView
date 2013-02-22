/*
 * ManualCoordEdit.cpp
 *
 *  Created on: 2012. 3. 2.
 *      Author: HIST002
 */
#include <cmath>
#include <iostream>
#include "ManualCoordEdit.h"
#include "CalcAir.h"
#include "XpmPickerDialog.h"
#include "ConfigParser.h"

ManualCoordEdit::ManualCoordEdit(QWidget* parent) : QDialog(parent) {
	// TODO Auto-generated constructor stub
	layerid = new AUserLayerId;
	drawtype = QChar('P');

	QHBoxLayout* hTop = new QHBoxLayout;
	QGroupBox* groupBox = new QGroupBox(tr("Draw Type"));
	radioPolyline = new QRadioButton(tr("&Polyline"));
	radioPolygon  = new QRadioButton(tr("Poly&gon"));
	radioCircle   = new QRadioButton(tr("&Circle"));
	radioSymbol   = new QRadioButton(tr("&Symbol"));
	radioPolyline->setChecked(true);

	QHBoxLayout* hbox0 = new QHBoxLayout;
	hbox0->addWidget(radioPolyline);
	hbox0->addWidget(radioPolygon);
	hbox0->addWidget(radioCircle);
	hbox0->addWidget(radioSymbol);
	hbox0->addStretch(1);
	groupBox->setLayout(hbox0);

	QHBoxLayout* hbox1 = new QHBoxLayout;
	comboBoundaryVia = new QComboBox;

	comboBoundaryVia->addItem(tr("select via type..."), "X");
	comboBoundaryVia->addItem(tr("Greate Circle"), "G");
	comboBoundaryVia->addItem(tr("Rhumb Line"), "H");
	comboBoundaryVia->addItem(tr("Counter clockwise Arc"), "L");
	comboBoundaryVia->addItem(tr("Clockwise Arc"), "R");
	comboBoundaryVia->addItem(tr("Circle"), "C");
	comboBoundaryVia->addItem(tr("Symbol"), "S");
	comboBoundaryVia->setCurrentIndex(0);
	connect(comboBoundaryVia, SIGNAL(currentIndexChanged(int)), this, SLOT(onViacomboChanged()));

	// Symbol Image
	editSymbol = new QLineEdit;
	editSymbol->setReadOnly(true);

	buttonSymbol = new QPushButton;
	buttonSymbol->setIcon(QIcon(":/images/object_symbol.png"));
	buttonSymbol->setToolTip(QString("Select Symbol"));
	buttonSymbol->setEnabled(false);
	connect(buttonSymbol, SIGNAL(clicked()), this, SLOT(selectSymbol()));

	hbox1->addWidget(comboBoundaryVia);
	hbox1->addWidget(editSymbol);
	hbox1->addWidget(buttonSymbol);

	QGroupBox *groupBox2 = new QGroupBox(tr("Boundary &Via"));
	groupBox2->setLayout(hbox1);

	hTop->addWidget(groupBox);
	hTop->setSpacing(10);
	hTop->addWidget(groupBox2);
	hTop->addStretch(1);

	// Point
	groupPoint = new QGroupBox(tr("Point"));
	QGridLayout* grid1 = new QGridLayout;
	QLabel* label2 = new QLabel(tr("L&atitude:"));
	QLabel* label3 = new QLabel(tr("L&ongitude:"));
	editPointLat = new QLineEdit;
	editPointLat->setInputMask("\\N99:99:99.99;_");
	editPointLon = new QLineEdit;
	editPointLon->setInputMask("\\E999:99:99.99;_");
	label2->setBuddy(editPointLat);
	label3->setBuddy(editPointLon);
	grid1->setMargin(0);
	grid1->setSpacing(3);
	grid1->addWidget(label2, 0, 0);
	grid1->addWidget(editPointLat, 0, 1);
	grid1->addWidget(label3, 1, 0);
	grid1->addWidget(editPointLon, 1, 1);
	groupPoint->setLayout(grid1);

	// Arc/Circle
	QGridLayout* grid2 = new QGridLayout;
	QLabel* label4 = new QLabel(tr("Center L&atitude:"));
	QLabel* label5 = new QLabel(tr("Center L*ongitude:"));
	QLabel* label6 = new QLabel(tr("&Distance:"));
	QLabel* label7 = new QLabel(tr("&Bearing:"));
	QLabel* label8 = new QLabel(tr("NM"));
	QLabel* label9 = new QLabel(tr("do"));

	editCenterLat = new QLineEdit;
	editCenterLat->setInputMask("\\N99:99:99.99;_");
	label4->setBuddy(editCenterLat);
	editCenterLon = new QLineEdit;
	editCenterLon->setInputMask("\\E999:99:99.99;_");
	label5->setBuddy(editCenterLon);
	editDistance = new QLineEdit;
	editDistance->setInputMask("999.9;_");
	editDistance->setAlignment(Qt::AlignRight);
	label6->setBuddy(editDistance);
	editBearing = new QLineEdit;
	editBearing->setInputMask("999.9;_");
	editBearing->setAlignment(Qt::AlignRight);
	label7->setBuddy(editBearing);
	grid2->setMargin(0);
	grid2->setSpacing(3);
	grid2->addWidget(label4, 0, 0);
	grid2->addWidget(editCenterLat, 0, 1);
	grid2->addWidget(label5, 1, 0);
	grid2->addWidget(editCenterLon, 1, 1);
	grid2->addWidget(label6, 0, 2);
	grid2->addWidget(editDistance, 0, 3);
	grid2->addWidget(label7, 1, 2);
	grid2->addWidget(editBearing, 1, 3);
	grid2->addWidget(label8, 0, 4);
	grid2->addWidget(label9, 1, 4);

	groupArcCircle = new QGroupBox(tr("Arc/Circle"));
	groupArcCircle->setLayout(grid2);

	QHBoxLayout* hBox2 = new QHBoxLayout;
	hBox2->addWidget(groupPoint);
	hBox2->addWidget(groupArcCircle);

	// Buttons
	QHBoxLayout* hBox3 = new QHBoxLayout;

	buttonInsert = new QPushButton(tr("&Insert"));
	buttonUpdate = new QPushButton(tr("&Update"));
	buttonDelete = new QPushButton(tr("&Delete"));
	buttonClear  = new QPushButton(tr("&Clear"));
	buttonDone   = new QPushButton(tr("&Done"));
	buttonCancel = new QPushButton(tr("C&ancel"));
	connect(buttonInsert, SIGNAL(clicked()), this, SLOT(insertPoint()));
	connect(buttonUpdate, SIGNAL(clicked()), this, SLOT(updatePoint()));
	connect(buttonDelete, SIGNAL(clicked()), this, SLOT(deletePoint()));
	connect(buttonClear,  SIGNAL(clicked()), this, SLOT(clearPoints()));
	connect(buttonDone,   SIGNAL(clicked()), this, SLOT(accept()));
	connect(buttonCancel, SIGNAL(clicked()), this, SLOT(reject()));

	hBox3->addStretch();
	hBox3->addWidget(buttonInsert);
	hBox3->addWidget(buttonUpdate);
	hBox3->addWidget(buttonDelete);
	hBox3->addWidget(buttonClear);
	hBox3->addWidget(buttonDone);
	hBox3->addWidget(buttonCancel);
	hBox3->addStretch();

	// Coordination Info
	QGroupBox* groupboxInfo = new QGroupBox(tr("Coordinate Info"));
	QVBoxLayout* v2 = new QVBoxLayout;
	v2->addLayout(hTop);
	v2->addLayout(hBox2);
	v2->addLayout(hBox3);
	groupboxInfo->setLayout(v2);

	// Coordination List
	QGroupBox* groupboxList = new QGroupBox(tr("Coordinates List"));
	tableList = new QTableWidget(0, 8);
	tableList->setHorizontalHeaderLabels(
			QStringList() << tr("Via") << tr("LAT") << tr("LON") << tr("Center Lat") << tr("CenterLon")
			<< tr("Dist.") << tr("Bearing") << tr("Symbol")
			);
	tableList->setSelectionMode(QAbstractItemView::SingleSelection);
	tableList->setSelectionBehavior(QAbstractItemView::SelectRows);
	connect(tableList, SIGNAL(itemSelectionChanged()), this, SLOT(currentRowToEdit()));

	QVBoxLayout* v = new QVBoxLayout;
	v->addWidget(tableList);
	groupboxList->setLayout(v);

	QVBoxLayout* vBoxMain = new QVBoxLayout;
	vBoxMain->addWidget(groupboxInfo);
	vBoxMain->addWidget(groupboxList);

	groupPoint->setEnabled(false);
	groupArcCircle->setEnabled(false);

	// Circle connect
	connect(radioCircle,   SIGNAL(clicked(bool)), this, SLOT(circleradioclick(bool)));
	connect(radioPolyline, SIGNAL(clicked(bool)), this, SLOT(polylineradioclick(bool)));
	connect(radioPolygon,  SIGNAL(clicked(bool)), this, SLOT(polygonradioclick(bool)));
	connect(radioSymbol,   SIGNAL(clicked(bool)), this, SLOT(symbolradioclick(bool)));

	setLayout(vBoxMain);

	setWindowTitle(tr("ManualCoord. Input"));
}

void ManualCoordEdit::insertPoint()
{
	int i = comboBoundaryVia->currentIndex();

	QVariant v = comboBoundaryVia->itemData(i);
	QString c = v.toString();

	if (c == "G" || c == "H") {
		QString lat = editPointLat->text();
		QString lon = editPointLon->text();
		if (lat.length() != 12) {
			QMessageBox::warning(this, tr("Error"), "Please, Fill Latitude Point");
			editPointLat->setFocus();
			return;
		}
		if (lon.length() != 13) {
			QMessageBox::warning(this, tr("Error"), "Please, Fill Longitude Point");
			editPointLon->setFocus();
			return;
		}
		insertRow();
		clearPoints();
		comboBoundaryVia->setFocus();
	}else if(c == "L" || c == "R") {
		QString lat = editPointLat->text();
		QString lon = editPointLon->text();
		QString clat = editCenterLat->text();
		QString clon = editCenterLon->text();
		QString dist = editDistance->text();
		QString bearing = editBearing->text();
		if (lat.length() != 12) {
			QMessageBox::warning(this, tr("Error"), "Please, Fill Latitude Point");
			editPointLat->setFocus();
			return;
		}
		if (lon.length() != 13) {
			QMessageBox::warning(this, tr("Error"), "Please, Fill Longitude Point");
			editPointLon->setFocus();
			return;
		}
		if (clat.length() != 12) {
			QMessageBox::warning(this, tr("Error"), "Please, Fill Center Laitude Point");
			editCenterLat->setFocus();
			return;
		}
		if (clon.length() != 13) {
			QMessageBox::warning(this, tr("Error"), "Please, Fill Center Longitude Point");
			editCenterLon->setFocus();
			return;
		}
		if (dist.length() < 2) {
			QMessageBox::warning(this, tr("Error"), "Please, Fill Distance");
			editDistance->setFocus();
			return;
		}
		if (bearing.length() < 2) {
			QMessageBox::warning(this, tr("Error"), "Please, Fill Bearing");
			editBearing->setFocus();
			return;
		}
		insertRow();
		clearPoints();
		comboBoundaryVia->setFocus();
	}else if(c == "C") {
		// 이미 레코드가 있다면
		int rowNo = tableList->rowCount();
		if (rowNo > 0) {
			QMessageBox::warning(this, tr("Error"), "Circle should have one record but already record exists");
			return;
		}
		QString clat = editCenterLat->text();
		QString clon = editCenterLon->text();
		QString dist = editDistance->text();
		if (clat.length() != 12) {
			QMessageBox::warning(this, tr("Error"), "Please, Fill Center Laitude Point");
			editCenterLat->setFocus();
			return;
		}
		if (clon.length() != 13) {
			QMessageBox::warning(this, tr("Error"), "Please, Fill Center Longitude Point");
			editCenterLon->setFocus();
			return;
		}
		if (dist.length() < 2) {
			QMessageBox::warning(this, tr("Error"), "Please, Fill Distance");
			editDistance->setFocus();
			return;
		}
		insertRow();
		clearPoints();
		comboBoundaryVia->setFocus();
	}else if(c == "S") {
		// 이미 레코드가 있다면
		int rowNo = tableList->rowCount();
		if (rowNo > 0) {
			QMessageBox::warning(this, tr("Error"), "Symbol should have one record but already record exists");
			return;
		}
		QString lat = editPointLat->text();
		QString lon = editPointLon->text();
		QString imageFile = editSymbol->text();
		if (lat.length() != 12) {
			QMessageBox::warning(this, tr("Error"), "Please, Fill Latitude Point");
			editPointLat->setFocus();
			return;
		}
		if (lon.length() != 13) {
			QMessageBox::warning(this, tr("Error"), "Please, Fill Longitude Point");
			editPointLon->setFocus();
			return;
		}
		if (imageFile.length() < 1) {
			QMessageBox::warning(this, tr("Error"), "Please, select Symbol");
			editSymbol->setFocus();
			return;
		}
		insertRow();
		clearPoints();
		comboBoundaryVia->setFocus();
	}else {
		QMessageBox::warning(this, tr("Error"), "Please, select via and fill points");
	}

	if (check() == true) {
		emit manualeditchanged();
	}
}

void ManualCoordEdit::updatePoint()
{
	int rowNo = tableList->currentRow();
	editToRow(rowNo);
	if (check() == true) {
		emit manualeditchanged();
	}
}

void ManualCoordEdit::deletePoint()
{
	int i = tableList->currentRow();
	if (i >= 0) {
		QString msg = QString("Do you want to delete %1 row ? ").arg(i+1);
		int reply = QMessageBox::question(this, tr("Delete"), msg, QMessageBox::Yes|QMessageBox::No);
		if (reply == QMessageBox::Yes) {
			tableList->removeRow(i);
		}
	}
	if (check() == true) {
		emit manualeditchanged();
	}
}

void ManualCoordEdit::clearPoints()
{
	comboBoundaryVia->setCurrentIndex(0);
	editSymbol->setText("");
	editPointLat->setText("");
	editPointLon->setText("");
	editCenterLat->setText("");
	editCenterLon->setText("");
	editDistance->setText("");
	editBearing->setText("");
	groupPoint->setEnabled(false);
	groupArcCircle->setEnabled(false);
	buttonSymbol->setEnabled(false);
}

void ManualCoordEdit::done()
{
	close();
}

void ManualCoordEdit::onViacomboChanged()
{
	int i = comboBoundaryVia->currentIndex();
	QVariant v = comboBoundaryVia->itemData(i);
	QString c = v.toString();

	editPointLat->setCursorPosition(1);

	if (c == "S") {
		buttonSymbol->setEnabled(true);
	}else {
		buttonSymbol->setEnabled(false);
	}

	if (c == "G" || c == "H" || c == "S") {
		groupPoint->setEnabled(true);
		groupArcCircle->setEnabled(false);
		editPointLat->setFocus();
	}else if(c == "C") {
		groupPoint->setEnabled(false);
		groupArcCircle->setEnabled(true);
		editBearing->setEnabled(false);
		editCenterLat->setCursorPosition(1);
		editCenterLat->setFocus();
	}else {
		groupPoint->setEnabled(true);
		groupArcCircle->setEnabled(true);
		editBearing->setEnabled(true);
		editPointLat->setFocus();
	}
}

void ManualCoordEdit::editToRow(int rowNo)
{
	if (rowNo < 0 || rowNo > tableList->rowCount()) {
		return;
	}
	int i = comboBoundaryVia->currentIndex();
	if (i == 0) {
		return;
	}
	QVariant v = comboBoundaryVia->itemData(i);
	QString via = v.toString();
	QString lat = editPointLat->text();
	QString lon = editPointLon->text();
	QString clat = editCenterLat->text();
	QString clon = editCenterLon->text();
	QString dist = editDistance->text();
	QString bearing = editBearing->text();
	QString imageFile = editSymbol->text();

	if (via == "G" || via == "H") {
		clat = clon = dist = bearing = imageFile = QString("");
	}else if(via == "C") {
		lat = lon = bearing = imageFile = QString("");
	}else if(via == "S") {
		clat = clon = dist = bearing = QString("");
	}

	QTableWidgetItem* item0 = new QTableWidgetItem;
	item0->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
	item0->setText(via);
	tableList->setItem(rowNo, 0, item0);

	QTableWidgetItem* item1 = new QTableWidgetItem;
	item1->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	item1->setText(lat);
	tableList->setItem(rowNo, 1, item1);

	QTableWidgetItem* item2 = new QTableWidgetItem;
	item2->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	item2->setText(lon);
	tableList->setItem(rowNo, 2, item2);

	QTableWidgetItem* item3 = new QTableWidgetItem;
	item3->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	item3->setText(clat);
	tableList->setItem(rowNo, 3, item3);

	QTableWidgetItem* item4 = new QTableWidgetItem;
	item4->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	item4->setText(clon);
	tableList->setItem(rowNo, 4, item4);

	QTableWidgetItem* item5 = new QTableWidgetItem;
	item5->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
	item5->setText(dist);
	tableList->setItem(rowNo, 5, item5);

	QTableWidgetItem* item6 = new QTableWidgetItem;
	item6->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
	item6->setText(bearing);
	tableList->setItem(rowNo, 6, item6);

	QTableWidgetItem* item7 = new QTableWidgetItem;
	item7->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	item7->setText(imageFile);
	tableList->setItem(rowNo, 7, item7);
}

void ManualCoordEdit::insertRow()
{
	int rowNo = tableList->rowCount();
	tableList->insertRow(rowNo);
	editToRow(rowNo);
}

/**
 * list - > edit
 */
void ManualCoordEdit::currentRowToEdit()
{
	int row = tableList->currentRow();
	if (row >= 0) {
		clearPoints();
		QTableWidgetItem* item = tableList->item(row, 0);
		QString s = item->text();
		if (s == "G") {
			comboBoundaryVia->setCurrentIndex(1);
		}else if(s == "H") {
			comboBoundaryVia->setCurrentIndex(2);
		}else if(s == "L") {
			comboBoundaryVia->setCurrentIndex(3);
		}else if(s == "R") {
			comboBoundaryVia->setCurrentIndex(4);
		}else if(s == "C") {
			comboBoundaryVia->setCurrentIndex(5);
		}else if(s == "S") {
			comboBoundaryVia->setCurrentIndex(6);
		}else {
			comboBoundaryVia->setCurrentIndex(0);
		}
		item = tableList->item(row, 1);
		editPointLat->setText(item->text());
		item = tableList->item(row, 2);
		editPointLon->setText(item->text());
		item = tableList->item(row, 3);
		editCenterLat->setText(item->text());
		item = tableList->item(row, 4);
		editCenterLon->setText(item->text());
		item = tableList->item(row, 5);
		editDistance->setText(item->text());
		item = tableList->item(row, 6);
		editBearing->setText(item->text());
		item = tableList->item(row, 7);
		editSymbol->setText(item->text());
	}
}

void ManualCoordEdit::clearAll()
{
	for (int i=tableList->rowCount()-1; i>=0; i--) {
		tableList->removeRow(i);
	}
	clearPoints();
	radioPolyline->setChecked(true);
	radioPolyline->setFocus();
}

/**
 * 입력한 결과를 lyaerid에 실어서 보낸다.
 */
AUserLayerId* ManualCoordEdit::getUsermap()
{
	CalcAir ca;
	layerid->bndrylist.clear();
	layerid->drawtype = getDrawType();
	layerid->visible = true;

	for (int row=0; row<tableList->rowCount(); row++) {
		AUserbndry* bndry = new AUserbndry;
		bndry->bndry_idx = (row + 1);
		bndry->bndry_via = tableList->item(row, 0)->text()[0];
		bndry->latlon.lat = tableList->item(row, 1)->text().replace(":", "").replace(".", "");
		bndry->latlon.lon = tableList->item(row, 2)->text().replace(":", "").replace(".", "");
		bndry->latlon.p = ca.toDD(QString("%1%2").arg(bndry->latlon.lat).arg(bndry->latlon.lon));

		if (bndry->bndry_via == QChar('C')) {
			bndry->latlon.lat = tableList->item(row, 3)->text().replace(":", "").replace(".", "");
			bndry->latlon.lon = tableList->item(row, 4)->text().replace(":", "").replace(".", "");
			bndry->latlon.p = ca.toDD(QString("%1%2").arg(bndry->latlon.lat).arg(bndry->latlon.lon));
		}

		bndry->arc_center_latlon.lat = tableList->item(row, 3)->text().replace(":", "").replace(".", "");
		bndry->arc_center_latlon.lon = tableList->item(row, 4)->text().replace(":", "").replace(".", "");
		bndry->arc_center_latlon.p = ca.toDD(QString("%1%2").arg(bndry->arc_center_latlon.lat).arg(bndry->arc_center_latlon.lon));
		bndry->arc_dist = tableList->item(row, 5)->text().toDouble();
		bndry->arc_bearing = tableList->item(row, 6)->text().toDouble();
		layerid->bndrylist.append(bndry);
	}
	// what is this?
	QString attr = layerid->attr;

	return layerid;
}

QChar ManualCoordEdit::getDrawType()
{
	if (radioPolyline && radioPolyline->isChecked()) {
		drawtype = QChar('P');
	}else if(radioPolygon && radioPolygon->isChecked()) {
		drawtype = QChar('G');
	}else if(radioSymbol && radioSymbol->isChecked()) {
		drawtype = QChar('S');
	}else if(radioCircle) {
		drawtype = QChar('C');
	}
	return drawtype;
}

void ManualCoordEdit::symbolradioclick(bool b)
{
	if (b) {
		comboBoundaryVia->setCurrentIndex(6);
		selectSymbol();
		drawtype = QChar('S');
		if (check() == true) {
			emit manualeditchanged();
		}
	}
}

void ManualCoordEdit::polylineradioclick(bool b)
{
	if (b) {
		comboBoundaryVia->setCurrentIndex(1);
		drawtype = QChar('P');
		if (check() == true) {
			emit manualeditchanged();
		}
	}
}

void ManualCoordEdit::polygonradioclick(bool b)
{
	if (b) {
		comboBoundaryVia->setCurrentIndex(1);
		drawtype = QChar('G');
		if (check() == true) {
			emit manualeditchanged();
		}
	}
}

void ManualCoordEdit::circleradioclick(bool b)
{
	if (b) {
		comboBoundaryVia->setCurrentIndex(5);
		editCenterLat->setFocus();
	}
}

/**
 * 레코드 데이터가 올바른 지 체크한다.
 */
bool ManualCoordEdit::check()
{
	int rowNo = tableList->rowCount();

	// 1개라도 레코드가 있어야 함.
	if (rowNo < 1) return false;

	// 1개 이상이고 C가 있다면 오류 - Circle, Symbol인 경우 한개의 레코드가 가질 수 있다.
	if (rowNo > 1) {	// 2개이상의 레코드를 가진 경우 Circle, Symbol 데이터가 있는지 체크한다.
		for (int row=0; row<tableList->rowCount(); row++) {
			QChar bndary_via = tableList->item(row, 0)->text()[0];
			if (bndary_via == QChar('C')) {
				QMessageBox::warning(this, tr("Error"), "Please, Circle has only one record");
				return false;
			}else if(bndary_via == QChar('S')) {
				QMessageBox::warning(this, tr("Error"), "Please, Symbol has only one record");
				return false;
			}
		}
	}
	return true;
}

void ManualCoordEdit::selectSymbol()
{
	QString symboldir = QString("%1/images").arg(ConfigParser::getInstance().envMapDir());

	XpmPickerDialog* xpmpickerdialog = new XpmPickerDialog(symboldir);

	int i = xpmpickerdialog->exec();

	if (i > 0) {
		QString fileName = xpmpickerdialog->selectedSymbol();
		editSymbol->setText(fileName);
		symbolFile = QString("%1%2").arg(symboldir).arg(fileName);
		delete xpmpickerdialog;
	}else {
		editSymbol->setText("");
	}
}
