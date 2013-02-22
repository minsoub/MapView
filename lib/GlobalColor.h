/*
 * GlobalColor.h
 *
 *  Created on: 2012. 5. 4.
 *      Author: JMS
 *  Description : Global Color variable define.
 */

#ifndef GLOBALCOLOR_H_
#define GLOBALCOLOR_H_

#include <QString>
#include <QColor>


static const int GlobalColorCount = 16;

enum UserGlobalColor {
        white,
        yellow,
        fuchsia,
        red,
        silver,
        gray,
        olive,
        purple,
        maroom,
        aqua,
        lime,
        teal,
        green,
        blue,
        navy,
        black
};

static const QString userColor[] = {
        "White",
        "Yellow",
        "Fuchsia",
        "Red",
        "Silver",
        "Gray",
        "Olive",
        "Purple",
        "Maroom",
        "Aqua",
        "Lime",
        "Teal",
        "Green",
        "Blue",
        "Navy",
        "Black"
};

static const QColor userRGBColor[] = {
		QColor(255, 255, 255),
		QColor(255, 255, 0),
		QColor(255, 0, 255),
		QColor(255, 0, 0),
		QColor(192, 192, 192),
		QColor(128, 128, 128),
		QColor(128, 128, 0),
		QColor(128, 0, 0),
		QColor(0, 255, 255),
		QColor(0, 255, 0),
		QColor(0, 128, 128),
		QColor(0, 128, 0),
		QColor(0, 0, 255),
		QColor(0, 0, 128),
		QColor(0, 0, 0)
};

#endif /* GLOBALCOLOR_H_ */
