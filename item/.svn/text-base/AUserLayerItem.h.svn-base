/*
 * AUserLayerItem.h
 *
 *  Created on: 2012. 2. 22.
 *      Author: HIST002
 */

#ifndef AUSERLAYERITEM_H_
#define AUSERLAYERITEM_H_

#include <QtSql>
#include <QPainter>
#include <QtGui>
#include <QGraphicsItem>
#include "../lib_layer/LayerDefine.h"
#include "../lib/Log424.h"
#include "../lib/CalcAir.h"
#include "../lib/AMapconf.h"
#include "../lib/AirDraw.h"
#include "../lib_layer/MsbBound.h"
#include "../lib_layer/LayerProperty.h"
#include "../lib_layer/MapDefine.h"
#include "../lib_layer/ALayer.h"
#include "../lib/MapUtil.h"
#include "../lib/LatLonBound.h"

class AUserLayerItem : public ALayerBase, public QGraphicsItem{
public:
	enum { Type = 998 };
	AUserLayerItem() : ALayerBase(Layer_User) {
		_classtype = ClassUser;
		setFlag(QGraphicsItem::ItemIsSelectable);
		setFlag(ItemIgnoresTransformations, true);
		setZValue(998);
		setSelected(false);
	};
	int type() const { return Type; }
	LayerClassType classtype() { return _classtype; }
	QString lasterror() const { return _lasterror; }
	void setLog(Log424* log) { _log = log; }
	void logprint(const QString& msg) { if (!_log) return; _log->print(msg); }
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	void updateInfo();
	QRectF boundingRect() const;



	void setLayerVisible(bool b) { _visible = b; }
	bool layerVisible() { return _visible; }
	void setTextVisible(bool b) { _textvisible = b; }
	bool textVisible() { return _textvisible; }



	void setAirdraw(AirDraw* air) { ad = air; }

	AUserLayerId* getUserLayer() { return userLayer; }
	void setUserLayer(AUserLayerId* layer) { userLayer = layer; }
	void setSymboldir(QString symboldir) { _symboldir = symboldir; }

	void updateMove(QPoint center, QRect rect);
	void updateMove(QPoint center);
	void setMoving(bool m) { ismoving = m; };
	bool isMoving() { return ismoving; };
private:

	QString _symboldir;
	LayerProperty _lp;
	QString _lasterror;
	AirDraw* ad;
	AUserLayerId* userLayer;		// User Layer Info
	bool _visible;
	bool _textvisible;
	bool ismoving;
protected:
	CalcAir _ca;
	Log424* _log;
};

#endif /* AUSERLAYERITEM_H_ */
