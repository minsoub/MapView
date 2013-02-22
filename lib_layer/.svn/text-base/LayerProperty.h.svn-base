/*
 * LayerProperty.h
 *
 *  Created on: 2012. 1. 30.
 *      Author: HIST002
 */

#ifndef LAYERPROPERTY_H_
#define LAYERPROPERTY_H_

#include <QString>
#include <QPainter>
#include <QColor>
#include <QPen>
#include <QBrush>
#include <QFont>

#include "../lib/Log424.h"
#include "MapDefine.h"

class LayerProperty {
public:
	LayerProperty() { setDefault(); };
	LayerProperty(const QString& line);
	void set(const QString& line);
	void set(const ALayerAttr* attr);
	void set(const QStringList& list);
	void setDefault();
	void setDefaultFColor(const QColor& color) { defaultFColor = QColor(color); }
	void setDefaultBColor(const QColor& color) { defaultBColor = QColor(color); }
	void changePainter(QPainter* painter);
	void setLineType(int i) { LineType = i; };
	void setLineWidth(int i) { LineWidth = i; };
	void setLineColor(int r, int g, int b) { LineColor = QColor::fromRgb(r, g, b); };
	void setLineColor(const QColor& color) { LineColor = color; };
	void setFillPattern(int i) { FillPattern = i; };
	void setFillColor(int r, int g, int b) { FillColor = QColor::fromRgb(r, g, b); };
	void setFillColor(const QColor& color) { FillColor = color; };
	void setFontName(const QString& s) { FontName = s; };
	void setFontSize(int i) { FontSize = i; };
	void setFontColor(int r, int g, int b) { FontColor = QColor::fromRgb(r, g, b); };
	void setFontColor(const QColor& color) { FontColor = color; };
	void setSymbol(const QString& s) { Symbol = s; };

	Qt::PenStyle lineType() {
		if (LineType == 1) return Qt::SolidLine;
		else if(LineType == 2) return Qt::DashLine;
		else if(LineType == 3) return Qt::DotLine;
		else return Qt::SolidLine;
	};
	int lineWidth() { return LineWidth; };
	QColor lineColor() { return LineColor; };
	QColor lineFillColor() { return FillColor; };
	Qt::BrushStyle fillStyle() {
		if (FillPattern == 0) return Qt::NoBrush;
		else if(FillPattern == 1) return Qt::SolidPattern;
		else if(FillPattern == 2) return Qt::Dense7Pattern;
		else if(FillPattern == 3) return Qt::HorPattern;
		else if(FillPattern == 4) return Qt::VerPattern;
		else if(FillPattern == 5) return Qt::CrossPattern;
		else if(FillPattern == 6) return Qt::BDiagPattern;
		else if(FillPattern == 7) return Qt::FDiagPattern;
		else if(FillPattern == 8) return Qt::DiagCrossPattern;
		else return Qt::NoBrush;
	};
	QColor fontColor() { return FontColor; };
	int fontSize() { return FontSize; };
	QString fontName() { return FontName; };
	QPen getPen();
	QBrush getBrush();
	QFont getFont();
	QString layerString();
	QString toString() const;
	QString getSymbol() { return Symbol; };
	ALayerAttr layerAttr() const;

private:
	int LineType;
	int LineWidth;
	QColor LineColor;
	int FillPattern;
	QColor FillColor;
	QString FontName;
	int FontSize;
	QColor FontColor;
	QString Symbol;
	QColor defaultFColor;
	QColor defaultBColor;

	QPen pen;
	QBrush brush;
	QFont font;
};

#endif /* LAYERPROPERTY_H_ */
