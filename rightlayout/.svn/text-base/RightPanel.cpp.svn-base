/*
 * RightPanel.cpp
 *
 *  Created on: 2012. 1. 16.
 *      Author: HIST002
 */

#include "RightPanel.h"

RightPanel::RightPanel(QWidget *widget):QWidget(widget) {
	// TODO Auto-generated constructor stub
	inputusertextDialog = NULL;
	uid = QString("");
	uid_index = -1;
	selectFlag = false;
	mapcanvasMPP = 0;			// meter per 1 pixcel
	objectpanelMPP = 0;			// meter per 1 pixcel

	// Object Panel define
	selectButton = new QToolButton;
	selectButton->setIcon(QIcon(":/images/object_select.png"));
	selectButton->setToolTip(QString("Selection"));
	selectButton->adjustSize();
	connect(selectButton, SIGNAL(clicked()), this, SLOT(setDownSelect()));

	lineButton = new QToolButton;
	lineButton->setIcon(QIcon(":/images/object_line.png"));
	lineButton->setToolTip(QString("Line"));
	lineButton->adjustSize();
	connect(lineButton, SIGNAL(clicked()), this, SLOT(setDownLine()));

	circleButton = new QToolButton;
	circleButton->setIcon(QIcon(":/images/object_circle.png"));
	circleButton->setToolTip(QString("Circle"));
	circleButton->adjustSize();
	connect(circleButton, SIGNAL(clicked()), this, SLOT(setDownCircle()));

	eclipseButton = new QToolButton;
	eclipseButton->setIcon(QIcon(":/images/object_ellipse.png"));
	eclipseButton->setToolTip(QString("Eclipse"));
	eclipseButton->adjustSize();
	connect(eclipseButton, SIGNAL(clicked()), this, SLOT(setDownEllipse()));

	rectangleButton = new QToolButton;
	rectangleButton->setIcon(QIcon(":/images/object_rectangle.png"));
	rectangleButton->setToolTip(QString("Rectangle"));
	rectangleButton->adjustSize();
	connect(rectangleButton, SIGNAL(clicked()), this, SLOT(setDownRectangle()));

	polygonButton = new QToolButton;
	polygonButton->setIcon(QIcon(":/images/object_polygon.png"));
	polygonButton->setToolTip(QString("Polygon"));
	polygonButton->adjustSize();
	connect(polygonButton, SIGNAL(clicked()), this, SLOT(setDownPolygon()));

	polylineButton = new QToolButton;
	polylineButton->setIcon(QIcon(":/images/object_polyline.png"));
	polylineButton->setToolTip(QString("Polyline"));
	polylineButton->adjustSize();
	connect(polylineButton, SIGNAL(clicked()), this, SLOT(setDownPolyline()));

	textButton = new QToolButton;
	textButton->setIcon(QIcon(":/images/object_text.png"));
	textButton->setToolTip(QString("Text"));
	textButton->adjustSize();
	connect(textButton, SIGNAL(clicked()), this, SLOT(setDownText()));

	arcButton = new QToolButton;
	arcButton->setIcon(QIcon(":/images/object_arc.png"));
	arcButton->setToolTip(QString("Arc"));
	arcButton->adjustSize();
	connect(arcButton, SIGNAL(clicked()), this, SLOT(setDownArc()));

	symbolButton = new QToolButton;
	symbolButton->setIcon(QIcon(":/images/object_symbol.png"));
	symbolButton->setToolTip(QString("Symbol"));
	symbolButton->adjustSize();
	connect(symbolButton, SIGNAL(clicked()), this, SLOT(setDownSymbol()));

	QGroupBox* groupboxDrawObject = new QGroupBox("Draw Object");
	QVBoxLayout* vb1 = new QVBoxLayout;
	QGridLayout* grid = new QGridLayout;
	grid->addWidget(selectButton,       0, 0);
	grid->addWidget(lineButton,         0, 1);
	grid->addWidget(circleButton,       0, 2);
	grid->addWidget(eclipseButton,      0, 3);
	grid->addWidget(arcButton,          0, 4);

	grid->addWidget(rectangleButton,    1, 0);
	grid->addWidget(polygonButton,      1, 1);
	grid->addWidget(polylineButton,     1, 2);
	grid->addWidget(textButton,         1, 3);
	grid->addWidget(symbolButton,       1, 4);

	manualButton = new QPushButton(tr("&Manual Coord. Input"));
	connect(manualButton, SIGNAL(clicked()), this, SLOT(setDownManual()));
	QHBoxLayout* hb1 = new QHBoxLayout;
	hb1->addStretch();
	hb1->addWidget(manualButton);
	hb1->addStretch();
	vb1->addLayout(grid);
	vb1->addLayout(hb1);

	groupboxDrawObject->setLayout(vb1);

	// Line Properties
	QLabel* labelLineType = new QLabel(tr("Type"));
	QLabel* labelLineWidth = new QLabel(tr("Width"));
	QLabel* labelLineColor = new QLabel(tr("Color"));

	comboLineType = new LineTypeCombo;
	connect(comboLineType, SIGNAL(currentIndexChanged(int)), this, SLOT(setLineType(int)));

	spinLineWidth = new QSpinBox;
	spinLineWidth->setValue(1);
	spinLineWidth->setRange(1, 5);
	connect(spinLineWidth, SIGNAL(valueChanged(int)), this, SLOT(setLineWidth(int)));

	rgbLineColor = new ColorRgbPicker;
	connect(rgbLineColor, SIGNAL(changed()), this, SLOT(setLineColor()));

	QGridLayout* gridLine = new QGridLayout;

	gridLine->addWidget(labelLineType, 0, 0);
	gridLine->addWidget(comboLineType, 0, 1);

	gridLine->addWidget(labelLineWidth, 1, 0);
	gridLine->addWidget(spinLineWidth, 1, 1);

	gridLine->addWidget(labelLineColor, 2, 0);
	gridLine->addWidget(rgbLineColor, 2, 1);

	QGroupBox* groupboxLineProperties = new QGroupBox("Line Properties");
	groupboxLineProperties->setLayout(gridLine);

	// Fill Properties
	QLabel* labelLineFillColor = new QLabel(tr("Fill Color"));
	QLabel* labelLinePattern = new QLabel(tr("Pattern"));

	rgbLineFillColor = new ColorRgbPicker;
	connect(rgbLineFillColor, SIGNAL(changed()), this, SLOT(setLineFillColor()));

	comboLinePattern = new FillPatternCombo;
	connect(comboLinePattern, SIGNAL(currentIndexChanged(int)), this, SLOT(setFillPattern(int)));

	QGridLayout* gridFill = new QGridLayout;
	gridFill->addWidget(labelLineFillColor, 0, 0);
	gridFill->addWidget(rgbLineFillColor, 0, 1);

	gridFill->addWidget(labelLinePattern, 1, 0);
	gridFill->addWidget(comboLinePattern, 1, 1);

	QGroupBox* groupboxFillProperties = new QGroupBox("Fill Properties");
	groupboxFillProperties->setLayout(gridFill);

	// Text Properties
	QLabel* labelTextFont = new QLabel(tr("Font"));
	QLabel* labelTextSize = new QLabel(tr("Size"));
	QLabel* labelTextColor = new QLabel(tr("Color"));

	comboTextFont = new QFontComboBox;
	comboTextFont->setFontFilters(QFontComboBox::ScalableFonts);
	comboTextFont->setCurrentFont(QFont("Courier"));
	connect(comboTextFont, SIGNAL(currentFontChanged(QFont)), this, SLOT(setFontName(QFont)));

	spinTextSize = new QSpinBox;
	spinTextSize->setValue(10);
	spinTextSize->setRange(8, 30);
	connect(spinTextSize, SIGNAL(valueChanged(int)), this, SLOT(setTextSize(int)));

	rgbTextColor = new ColorRgbPicker;
	connect(rgbTextColor, SIGNAL(changed()), this, SLOT(setTextColor()));

	QGridLayout* gridText = new QGridLayout;

	gridText->addWidget(labelTextFont,   0, 0);
	gridText->addWidget(comboTextFont,   0, 1);
	gridText->addWidget(labelTextSize,   1, 0);
	gridText->addWidget(spinTextSize,    1, 1);
	gridText->addWidget(labelTextColor,  2, 0);
	gridText->addWidget(rgbTextColor,    2, 1);

	QGroupBox* groupboxTextProperties = new QGroupBox("Text Properties");
	groupboxTextProperties->setLayout(gridText);

	// Usermap id List
	QGroupBox* groupboxUserMapId = new QGroupBox("User Map Id");
	listUserMapId = new CheckListBox;
	listUserMapId->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
	connect(listUserMapId, SIGNAL(currentRowChanged(QString)), this, SLOT(uidChanged(QString)));

	// Usermap delete changename button
	buttonUserMapIdDelete = new QPushButton(tr("&Delete"));
	connect(buttonUserMapIdDelete, SIGNAL(clicked()), this, SLOT(deleteUid()));

	buttonUserIdChange = new QPushButton(tr("&Change Id name"));
	connect(buttonUserIdChange, SIGNAL(clicked()), this, SLOT(changeUidName()));

	QVBoxLayout* umiVLayout = new QVBoxLayout;
	QHBoxLayout* umiHLayout = new QHBoxLayout;
	umiHLayout->addStretch();
	umiHLayout->addWidget(buttonUserMapIdDelete);
	umiHLayout->addWidget(buttonUserIdChange);
	umiHLayout->addStretch();

	umiVLayout->addWidget(listUserMapId);
	umiVLayout->addLayout(umiHLayout);
	groupboxUserMapId->setLayout(umiVLayout);

	// Zoom
	groupboxZoom = new QGroupBox("Zoom");
	groupboxZoom->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);

	spinBoxZoom = new QSpinBox();
	spinBoxZoom->setRange(10, 2000);		// MPP

	hSliderZoom = new QSlider();
	hSliderZoom->setOrientation(Qt::Horizontal);
	hSliderZoom->setRange(10, 2000);
	hSliderZoom->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);

	connect(spinBoxZoom, SIGNAL(valueChanged(int)), hSliderZoom, SLOT(setValue(int)));
	connect(hSliderZoom, SIGNAL(valueChanged(int)), spinBoxZoom, SLOT(setValue(int)));
	connect(spinBoxZoom, SIGNAL(valueChanged(int)), this,        SLOT(changeZoom()));
	connect(hSliderZoom, SIGNAL(valueChanged(int)), this,        SLOT(changeZoom()));

	zoomHLayout = new QHBoxLayout;
	zoomHLayout->addWidget(hSliderZoom);
	zoomHLayout->addWidget(spinBoxZoom);
	groupboxZoom->setLayout(zoomHLayout);

	// Main Setting
	QVBoxLayout* mainLayout = new QVBoxLayout;
	mainLayout->addWidget(groupboxDrawObject);
	mainLayout->addWidget(groupboxLineProperties);
	mainLayout->addWidget(groupboxFillProperties);
	mainLayout->addWidget(groupboxTextProperties);
	mainLayout->addWidget(groupboxUserMapId);
	mainLayout->addWidget(groupboxZoom);
	mainLayout->addStretch();

	setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
	setLayout(mainLayout);

	property = new LayerProperty;
	nowDrawType = Select;

	setDown(Select);
}

void RightPanel::setDown(DrawType dt)
{
	selectButton->setDown(false);
	lineButton->setDown(false);
	circleButton->setDown(false);
	eclipseButton->setDown(false);
	rectangleButton->setDown(false);
	polygonButton->setDown(false);
	polylineButton->setDown(false);
	textButton->setDown(false);
	arcButton->setDown(false);
	symbolButton->setDown(false);
	manualButton->setDown(false);

	switch(dt) {
	case Select:
		selectButton->setDown(true);
		emit changedDrawtype(Select);
		break;
	case Line:
		lineButton->setDown(true);
		emit changedDrawtype(Line);
		break;
	case Circle:
		circleButton->setDown(true);
		emit changedDrawtype(Circle);
		break;
	case Ellipse:
		eclipseButton->setDown(true);
		emit changedDrawtype(Ellipse);
		break;
	case Rectangle:
		rectangleButton->setDown(true);
		emit changedDrawtype(Rectangle);
		break;
	case Polyline:
		polylineButton->setDown(true);
		emit changedDrawtype(Polyline);
		break;
	case Polygon:
		polygonButton->setDown(true);
		emit changedDrawtype(Polygon);
		break;
	case Text:
		textButton->setDown(true);
		emit changedDrawtype(Text);
		break;
	case Arc:
		arcButton->setDown(true);
		emit changedDrawtype(Arc);
		break;
	case Symbol:
		symbolButton->setDown(true);
		emit changedDrawtype(Symbol);
		break;
	case Manual:
		manualButton->setDown(true);
		emit changedDrawtype(Manual);
		break;
	default:
		break;
	}
}

void RightPanel::setLineType(int i)
{
	property->setLineType(i+1);
	if (selectFlag) emit changedLayerProperty();
}

void RightPanel::setLineWidth(int w)
{
	property->setLineWidth(w);
	if (selectFlag) emit changedLayerProperty();
}

void RightPanel::setLineColor()
{
	property->setLineColor(rgbLineColor->color());
	if (selectFlag) emit changedLayerProperty();
}

void RightPanel::setLineFillColor()
{
	property->setFillColor(rgbLineFillColor->color());
	if (selectFlag) emit changedLayerProperty();
}

void RightPanel::setFillPattern(int i)
{
	property->setFillPattern(i);
	if (selectFlag) emit changedLayerProperty();
}

void RightPanel::setFontName(const QFont& font)
{
	property->setFontName(font.family());
	if (selectFlag) emit changedLayerProperty();
}

void RightPanel::setTextSize(int i)
{
	property->setFontSize(i);
	if (selectFlag) emit changedLayerProperty();
}

void RightPanel::setTextColor()
{
	property->setFontColor(rgbTextColor->color());
	if (selectFlag) emit changedLayerProperty();
}

void RightPanel::addUid(const QString& s)
{
	listUserMapId->add(s, false);
}

void RightPanel::deleteUid()
{
	if (listUserMapId->checkedCount() > 0) {
		QMessageBox::StandardButton reply;
		QString message = QString("Do you want to delete ? ");
		reply = QMessageBox::question(this, tr("Delete Confirm"), message,
									QMessageBox::Yes | QMessageBox::No);

		if (reply == QMessageBox::Yes) {
			QString ids = listUserMapId->deleteCheckedItem();
			emit deletedUid(ids);
		}
	}else {
		QMessageBox::warning(this, "Information", QString("Need to check one or more"));
	}
}

/**
 * 라인으로 속성변경 & component 값 변경
 */
void RightPanel::setProperty(const QString& line)
{
	property->set(line);

	setDown(Select);

	comboLineType->setCurrentLineType(property->lineType());
	spinLineWidth->setValue(property->lineWidth());
	rgbLineColor->setColor(property->lineColor());
	rgbLineFillColor->setColor(property->lineFillColor());
	comboLinePattern->setCurrentFillPattern(property->fillStyle());
	comboTextFont->setCurrentFont(property->getFont());
	spinTextSize->setValue(property->fontSize());
	rgbTextColor->setColor(property->fontColor());
}

void RightPanel::clearUid()
{
	listUserMapId->clearAll();
}

void RightPanel::setUidListCurrentRow(const QString& uid)
{
	listUserMapId->changeCurrentData(uid);
}

/**
 * Current Row가 변경되었을 때
 */
void RightPanel::uidChanged(const QString& uidtype)
{
	if (uidtype.length() > 0) {
		QString uid;
		QStringList slist = uidtype.split(':');
		uid = slist[0];

		emit changedSelectedUid(uid);
	}
}

void RightPanel::changeUidName()
{
	QString selectedUid = listUserMapId->currentText();
	if (selectedUid.length() < 1) return;

	QStringList ts = selectedUid.split(':');
	QString nowid = ts[0];
	QString text;

	if (inputusertextDialog == NULL) {
		inputusertextDialog = new InputUserText(this, 20, QString("Change User Id"), QString("Enter new User id:"));
	}
	inputusertextDialog->setText(nowid);
	int r = inputusertextDialog->exec();

	if (r == 1) {
		text = inputusertextDialog->getText();
	}else {
		return;
	}
	if (text == nowid) return;
	if (!text.isEmpty()) {
		for (int i=0; i<listUserMapId->count(); i++) {
			QString s = listUserMapId->getText(i);
			if (s == text) {
				QMessageBox::critical(this, "Error", QString("%1 is already exist").arg(text));
				return;
			}
		}
		QMessageBox::warning(this, "Message", QString("%1 ==> %2").arg(nowid).arg(text));
		emit changedUidName(nowid, text);
	}
}

/**
 * SpinBox 내용이 변경되었을 때 호출되는 Slot
 */
void RightPanel::changeZoom()
{
	if (objectpanelMPP == spinBoxZoom->value()) return;

	if (mapcanvasMPP != spinBoxZoom->value()) {
		objectpanelMPP = spinBoxZoom->value();
		emit changeZoom(objectpanelMPP);
	}
}

void RightPanel::setChangeZoom(double zoom)
{
	if (zoom > 2000) {
		mapcanvasMPP = zoom;
		objectpanelMPP = mapcanvasMPP;
		return;
	}

	if (mapcanvasMPP == 0 || mapcanvasMPP != zoom || mapcanvasMPP != objectpanelMPP)
	{
		mapcanvasMPP = zoom;
		objectpanelMPP = mapcanvasMPP;
		spinBoxZoom->setValue(mapcanvasMPP);
	}
}
