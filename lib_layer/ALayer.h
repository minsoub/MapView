/*
 * ALayer.h
 *
 *  Created on: 2012. 1. 30.
 *      Author: HIST002
 */

#ifndef ALAYER_H_
#define ALAYER_H_

#include <iostream>
#include <QtSql>
#include <QPainter>
#include <QtGui>
#include <QGraphicsItem>
#include "LayerDefine.h"
#include "../lib/Log424.h"
#include "../lib/CalcAir.h"
#include "../lib/AMapconf.h"
#include "../lib/AirDraw.h"
#include "MsbBound.h"
#include "LayerProperty.h"
#include "MapDefine.h"

enum LayerClassType { ClassBase, ClassLayer, ClassPoint, ClassSymbol, ClassLines, ClassHold, ClassArea, ClassUser };

class ALayerBase {
protected:
	LayerType _layertype;
	Log424* _log;
	LayerClassType _classtype;
public:
	ALayerBase(LayerType t) {_layertype = t; _classtype = ClassBase; }
	virtual ~ALayerBase() {}
	void setLog(Log424& log) { _log = &log; }
	void logprint(const QString& msg) { if(!_log) return; _log->print(msg); }
	LayerType layerType() { return _layertype; }
	LayerClassType classType() { return _classtype; }
};

class ALayer : public ALayerBase, public QGraphicsItem {
private:
	bool _visible;
	bool _textvisible;
protected:
	LayerDefine _layerdefine;
	MsgBound _msb;
	CalcAir  _ca;
	ALayerIdList _list;
	LayerProperty _lp;
public:
	ALayer(LayerType t):ALayerBase(t) {
		_visible = true;
		_textvisible = false;
		_log = NULL;
		_classtype = ClassLayer;

		setZValue(-1);		// 음의 값 - 노드 아래에 그려짐
		//setFlag(QGraphicsItem::ItemIsMovable
		//setFlags(ItemIgnoresTransformations);  //, true);
		//setCacheMode(QGraphicsItem::DeviceCoordinateCache);
	}
	AirDraw* ad;
	virtual ~ALayer() { clear(); }
	void setAirdraw(AirDraw* air) { this->ad = air; }
	QString toString() const {
		return QString("%1:%2").arg(shortName()).arg(fullName());
	}
	QString shortName() const { return _layerdefine.shortName(_layertype); }
	QString fullName() const { return _layerdefine.fullName(_layertype); }
	void setLayerVisible(bool b) {
		//qDebug() << "ALayer::setLayerVisible : " << b;
		_visible = b;
	}
	bool layerVisible() { return _visible; }
	void setTextVisible(bool b) { _textvisible = b; }
	bool textVisible() { return _textvisible; }
	void setAllIdVisible(bool b) {
		//qDebug() << "ALayer::setAllIdVisible : " << b;
		for (int i=0; i<_list.count(); i++) {
			_list[i]->visible = b;
		}
	}
	bool setIdVisible(const QString& idName, bool b) {
		ALayerId* id = findId(idName);
		if (id != NULL) { id->visible = b; return true; }
		return false;
	}
	bool getIdVisible(int idx) {
		if (idx < 0 || idx >= _list.count()) return false;
		return _list[idx]->visible;
	}
	void setLayerproperty(const QString& line) { _lp.set(line); }
	void setLayerproperty(const QStringList& list) { _lp.set(list); }
	ALayerAttr layerAttr() { return _lp.layerAttr(); }

	QString getId(const int i) {
		if (i<0 || i>= _list.count()) return QString("");
		return _list[i]->id;
	}
	void fillId(QStringList& list) {
		for (int i=0; i<_list.count(); i++) {
			int b = _list[i]->visible ? 1 : 0;
			QString s = QString("%1:%2").arg(_list[i]->id).arg(b);
			list.append(s);
		}
	}
	int idCount() const { return _list.count(); }
	void clear() { _list.clear(); }
	ALayerId* getLayerId(int idx) {
		if (idx < 0 || idx >= _list.count()) return NULL;
		return _list[idx];
	}
	void appendLayerId(const ALayerId* layerid) {
		ALayerId* newLayerId = new ALayerId();
		*newLayerId = *layerid;
		_list.append(newLayerId);
	}
	ALayerId* findId(const QString& idName) {
		for (int i=0; i<_list.count(); i++) {
			if (_list[i]->id == idName) return _list[i];
		}
		return NULL;
	}
	int findIndex(const QString& idName) {
		for (int i=0; i<_list.count(); i++) {
			if (_list[i]->id == idName) return i;
		}
		return -1;
	}
	void deleteId(const int idx) {
		if (idx>=0) {
			_list.remove(idx);
		}
	}

	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) = 0;
	virtual QRectF boundingRect() const = 0;
	virtual void print(QTextStream& out, AMapconf& mapconf) = 0;
	virtual bool query(QSqlQuery* query, const QString& sql) = 0;
	virtual void read(QTextStream& in, int& lineNo) = 0;
	virtual ALayer* clone() = 0;
	virtual void updateInfo() = 0;

};
#endif /* ALAYER_H_ */
