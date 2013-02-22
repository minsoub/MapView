/*
 * LayerProperty.cpp
 *
 *  Created on: 2012. 1. 30.
 *      Author: HIST002
 */

#include "LayerProperty.h"

LayerProperty::LayerProperty(const QString& line) {
	// TODO Auto-generated constructor stub
	defaultFColor = QColor(Qt::white);
	defaultBColor = QColor(Qt::white);

	set(line);
}

void LayerProperty::set(const QStringList& list)
{
	ALayerAttr attr;

	if (list.length() > 10) {
		attr.linetype = list[2];
		attr.linewidth = list[3];
		attr.linecolor = list[4];
		attr.fillpattern = list[5];
		attr.fillcolor = list[6];
		attr.fontname = list[7];
		attr.fontsize = list[8];
		attr.fontcolor = list[9];
		attr.symbol = list[10];
	}
	set(&attr);
}

void LayerProperty::set(const QString& line)
{
	QStringList list = line.split(':');
	QString tmp;

	// LineType
	if (list[2].length() > 0) LineType = list[2].toInt();
	else LineType = 1;
	// LineWidth
	if (list[3].length() > 0) LineWidth = list[3].toInt();
	else LineWidth = 1;
	// LineColor
	tmp = list[4];
	if (tmp.length() > 0) {
		QStringList tmpList = tmp.split(',');
		LineColor = QColor::fromRgb(tmpList[0].toInt(), tmpList[1].toInt(), tmpList[2].toInt(), TuMyungDo);
	}else {
		LineColor = defaultFColor;
	}
	// FillPattern
	if (list[5].length() > 0) {
		FillPattern = list[5].toInt();
	}else {
		FillPattern = 0;
	}
	// FillColor
	tmp = list[6];
	if (tmp.length() > 0) {
		QStringList tmpList = tmp.split(',');
		FillColor = QColor::fromRgb(tmpList[0].toInt(), tmpList[1].toInt(), tmpList[2].toInt(), TuMyungDo);
	}else {
		FillColor = QColor(0, 0, 0, TuMyungDo);
	}
	if (list[7].length() > 0) {
		FontName = list[7];
	}else {
		FontName = "Times";
	}
	if (list[8].length() > 0) {
		FontSize = list[8].toInt();
	}else {
		FontSize = 8;
	}
	// FontColor
	if (list[9].length() > 0) {
		tmp = list[9];
		QStringList tmpList = tmp.split(',');
		FontColor = QColor::fromRgb(tmpList[0].toInt(), tmpList[1].toInt(), tmpList[2].toInt(), TuMyungDo);
	}else {
		FontColor = defaultFColor;
	}
	if (list.count() >= 10) {
		Symbol = list[10];
	}else {
		Symbol = QString("");
	}
}

void LayerProperty::setDefault()
{
	defaultFColor = QColor(Qt::white);
	defaultBColor = QColor(Qt::black);
	LineType = 1;
	LineWidth = 1;
	LineColor = defaultFColor;

	FillPattern = Qt::NoBrush;
	FillColor = defaultFColor;

	FontName = "Times";
	FontSize = 8;
	FontColor = defaultFColor;
	Symbol = QString("");
}

void LayerProperty::set(const ALayerAttr* attr)
{
	setDefault();
	if (attr->linetype.length() > 0) {
		int i = attr->linetype.toInt();
		if (i>0 && i<=3) LineType = i;
	}
	if (attr->linewidth.length() > 0) {
		LineWidth = attr->linewidth.toInt();
	}
	if (attr->linecolor.length() > 0) {
		QString tmp = attr->linecolor;
		QStringList tmpList = tmp.split(',');
		LineColor = QColor::fromRgb(tmpList[0].toInt(), tmpList[1].toInt(), tmpList[2].toInt());
	}
	if (attr->fillpattern.length() > 0) {
		FillPattern = attr->fillpattern.toInt();
	}
	if (attr->fillcolor.length() > 0) {
		QString tmp = attr->fillcolor;
		QStringList tmpList = tmp.split(',');
		FillColor = QColor::fromRgb(tmpList[0].toInt(), tmpList[1].toInt(), tmpList[2].toInt());
	}
	if (attr->fontname.length() > 0) {
		FontName = attr->fontname;
	}
	if (attr->fontsize.length() > 0) {
		FontSize = attr->fontsize.toInt();
	}
	if (attr->fontcolor.length() > 0) {
		QString tmp = attr->fontcolor;
		QStringList tmpList = tmp.split(',');
		FontColor = QColor::fromRgb(tmpList[0].toInt(), tmpList[1].toInt(), tmpList[2].toInt());
	}
	if (attr->symbol.length() > 0) {
		Symbol = attr->symbol;
	}
}
void LayerProperty::changePainter(QPainter *painter)
{
	Qt::PenStyle penstyle[4] = { Qt::NoPen, Qt::SolidLine, Qt::DashLine, Qt::DotLine };
	Qt::BrushStyle brushstyle[9] =  {
			Qt::NoBrush, Qt::SolidPattern,
			Qt::Dense7Pattern, Qt::HorPattern,
			Qt::VerPattern, Qt::CrossPattern,
			Qt::BDiagPattern, Qt::FDiagPattern,
			Qt::DiagCrossPattern
	};
	QPen pen(Qt::white);
	pen.setStyle(penstyle[LineType]);
	pen.setWidth(LineWidth);
	pen.setColor(LineColor);
	QBrush brush(Qt::white);
	brush.setStyle(brushstyle[FillPattern]);
	brush.setColor(FillColor);

	QFont font;
	font.setFamily(FontName);
	font.setPointSize(FontSize);

	painter->setPen(pen);
	painter->setBrush(brush);
	painter->setFont(font);
}

QPen LayerProperty::getPen()
{
	pen.setColor(lineColor());
	pen.setStyle(lineType());
	pen.setWidth(lineWidth());

	return pen;
}

QBrush LayerProperty::getBrush()
{
	brush.setColor(lineFillColor());
	brush.setStyle(fillStyle());

	return brush;
}

QFont LayerProperty::getFont()
{
	pen.setColor(fontColor());
	font.setFamily(fontName());
	font.setPointSize(fontSize());

	return font;
}

QString LayerProperty::toString() const
{
	return QString(
			"LineType : %1"
			"LineWidth : %2"
			"LineColor : %3"
			"FillPattern : %4"
			"FillColor : %5"
			"FontName : %6"
			"FontSize : %7"
			"FontColor : %8"
			"Symbol : %9")
			.arg(LineType)
			.arg(LineWidth)
			.arg(LineColor.name())
			.arg(FillPattern)
			.arg(FillColor.name())
			.arg(FontName)
			.arg(FontSize)
			.arg(FontColor.name())
			.arg(Symbol);
}

QString LayerProperty::layerString()
{
	int r, g, b;
	LineColor.getRgb(&r, &g, &b);
	QString c1 = QString("%1,%2,%3").arg(r).arg(g).arg(b);

	FillColor.getRgb(&r, &g, &b);
	QString c2 = QString("%1,%2,%3").arg(r).arg(g).arg(b);

	FontColor.getRgb(&r, &g, &b);
	QString c3 = QString("%1,%2,%3").arg(r).arg(g).arg(b);

	return QString("%1:%2:%3:%4:%5:%6:%7:%8:%9")
					.arg(LineType)
					.arg(LineWidth)
					.arg(c1)
					.arg(FillPattern)
					.arg(c2)
					.arg(FontName)
					.arg(FontSize)
					.arg(c3)
					.arg(Symbol);
}

ALayerAttr LayerProperty::layerAttr() const
{
	ALayerAttr attr;
	int r, g, b;
	LineColor.getRgb(&r, &g, &b);
	QString c1 = QString("%1,%2,%3").arg(r).arg(g).arg(b);

	FillColor.getRgb(&r, &g, &b);
	QString c2 = QString("%1,%2,%3").arg(r).arg(g).arg(b);

	FontColor.getRgb(&r, &g, &b);
	QString c3 = QString("%1,%2,%3").arg(r).arg(g).arg(b);

	attr.linetype = QString("%1").arg(LineType);
	attr.linewidth = QString("%1").arg(LineWidth);
	attr.linecolor = c1;
	attr.fillpattern = QString("%1").arg(FillPattern);
	attr.fillcolor = c2;
	attr.fontname = FontName;
	attr.fontsize = QString("%1").arg(FontSize);
	attr.fontcolor = c3;
	attr.symbol = Symbol;

	return attr;
}
