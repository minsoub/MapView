/*
 * RightPanel.h
 *
 *  Created on: 2012. 1. 16.
 *      Author: HIST002
 */

#ifndef RIGHTPANEL_H_
#define RIGHTPANEL_H_

#include <QtGui>
#include "../lib/LineTypeCombo.h"
#include "../lib/FillPatternCombo.h"
#include "../lib/ColorRgbPicker.h"
#include "../lib_layer/LayerProperty.h"
#include "EditDefine.h"
#include "InputUserText.h"
#include "CheckListBox.h"

class RightPanel : public QWidget  {
	Q_OBJECT
public:
	RightPanel(QWidget *widget=0);
	DrawType drawType() { return nowDrawType; }
	LayerProperty* getProperty() { return property; }
	void addUid(const QString& s);
	QString getUid() { return uid; }
	int getUidIndex() { return uid_index; }
	void setProperty(const QString& line);			// 라인으로 속성변경 & component 값 변경
	void clearUid();
	void setSelectFlag(bool b) { selectFlag = b; }
	void setUidListCurrentRow(const QString& uid);
public slots:
	void setDown(DrawType dt);
	void setDownSelect() { setDown(Select); }
	void setDownLine() { setDown(Line); }
	void setDownCircle() { setDown(Circle); }
	void setDownEllipse() { setDown(Ellipse); }
	void setDownRectangle() { setDown(Rectangle); }
	void setDownPolyline() { setDown(Polyline); }
	void setDownPolygon() { setDown(Polygon); }
	void setDownText() { setDown(Text); }
	void setDownArc() { setDown(Arc); }
	void setDownSymbol() { setDown(Symbol); }
	void setDownManual() { setDown(Manual); }

	void setLineType(int i);
	void setLineWidth(int w);
	void setLineColor();
	void setLineFillColor();
	void setFillPattern(int i);
	void setFontName(const QFont& font);
	void setTextSize(int i);
	void setTextColor();

	void deleteUid();
	void changeUidName();
	void uidChanged(const QString& uid);
	void changeZoom();
	void setChangeZoom(double zoom);

signals:
	void changedDrawtype(DrawType dt);
	void changedLayerProperty();
	void changedSelectedUid(const QString& uid);
	void deletedUid(const QString& uids);
	void changedUidName(const QString& oldid, const QString& newid);
	void changeZoom(double zoom);
private:
	InputUserText* inputusertextDialog;
	DrawType nowDrawType;
	LayerProperty* property;

	// Draw object button
	QToolButton* selectButton;
	QToolButton* lineButton;
	QToolButton* circleButton;
	QToolButton* eclipseButton;
	QToolButton* rectangleButton;
	QToolButton* polygonButton;
	QToolButton* polylineButton;
	QToolButton* textButton;
	QToolButton* arcButton;
	QToolButton* symbolButton;

	QPushButton* manualButton;			// manual input

	QButtonGroup* buttongroup;

	// Line Properties
	LineTypeCombo* comboLineType;
	QSpinBox* spinLineWidth;
	ColorRgbPicker* rgbLineColor;
	ColorRgbPicker* rgbLineFillColor;
	FillPatternCombo* comboLinePattern;

	// Text Properties
	QFontComboBox* comboTextFont;
	QSpinBox* spinTextSize;
	ColorRgbPicker* rgbTextColor;

	// User Map Id
	QPushButton* buttonUserMapIdDelete;
	QPushButton* buttonUserIdChange;
	CheckListBox* listUserMapId;

	// Zoom
	QGroupBox* groupboxZoom;
	QHBoxLayout* zoomHLayout;
	QSpinBox* spinBoxZoom;
	QSlider* hSliderZoom;
	double mapcanvasMPP;			// meter per 1 pixcel
	double objectpanelMPP;			// meter per 1 pixcel

	QString uid;
	int uid_index;
	bool selectFlag;
};

#endif /* RIGHTPANEL_H_ */
