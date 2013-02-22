/*
 * MapUtil.cpp
 *
 *  Created on: 2012. 2. 17.
 *      Author: HIST002
 */
#include <iostream>
#include <QStringList>
#include "MapUtil.h"

// QString Utility member function
void QSU::qstrcpy(char* des, const QString& str)
{
	strcpy(des, str.toAscii().data());
}

// LLU member functions
QString LLU::lat(const QString& latlon)
{
	return latlon.left(9);
}
QString LLU::lon(const QString& latlon)
{
	return latlon.right(10);
}

void LAU::set(ALayerAttr& attr, const QStringList& list)
{
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
}

void LAU::set(ALayerAttr* attr, const QStringList& list)
{
	if (list.length() > 10) {
		attr->linetype = list[2];
		attr->linewidth = list[3];
		attr->linecolor = list[4];
		attr->fillpattern = list[5];
		attr->fillcolor = list[6];
		attr->fontname = list[7];
		attr->fontsize = list[8];
		attr->fontcolor = list[9];
		attr->symbol = list[10];
	}
}

QString LAU::toString(ALayerAttr& attr)
{
	return QString("LineType:%1, LineWidth:%2, LineColor:%3"
			"FillPattern:%4,FillColor:%5,FontName:%6,FontSize:%7"
			"FontColor:%8,Symbol:%9")
			.arg(attr.linetype)
			.arg(attr.linewidth)
			.arg(attr.linecolor)
			.arg(attr.fillpattern)
			.arg(attr.fillcolor)
			.arg(attr.fontname)
			.arg(attr.fontsize)
			.arg(attr.fontcolor)
			.arg(attr.symbol);
}
