/*
 * ASymbolLayerItem.h
 *
 *  Created on: 2012. 2. 21.
 *      Author: HIST002
 */

#ifndef ASYMBOLLAYERITEM_H_
#define ASYMBOLLAYERITEM_H_

#include "APointLayerItem.h"

class ASymbolLayerItem : public APointLayerItem{
public:
	enum { Type = 5 };
	int type() const { return Type; }
	ASymbolLayerItem(LayerType t) : APointLayerItem(t) {
		_classtype = ClassSymbol;
		_symbol    = QString("");
	};
	ASymbolLayerItem &operator= (ASymbolLayerItem &tmp) {
		//this->clear();
	   //for(int i=0;i<_list.count();i++){
		//   const ALayerId* newLayerId = tmp.getLayerId(i);
		//   this->appendLayerId(newLayerId);
	   // }
	   return *this;
	}
	void draw(QPainter* painter);
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
	{
		draw(painter);
	}
	void setSymbol(const QString& file) { _symbol = file; }
	void setSymbolDir(const QString& dir) { _symboldir = dir; }
	QString symbol() const { return _symbol; }
	QString symbolDir() const { return _symboldir; }
	QString symbolFullName() const { return QString("%1/%2").arg(_symboldir).arg(_symbol); }

	ASymbolLayerItem* clone() {
		ASymbolLayerItem* newSymbolLayer = new ASymbolLayerItem(_layertype);
      *newSymbolLayer = *this;
      newSymbolLayer->clear();
      newSymbolLayer->setSymbol(_symbol);
      newSymbolLayer->setSymbolDir(_symboldir);
      newSymbolLayer->_lp = this->_lp;
      for (int i=0; i<_list.count(); i++) {
		   const ALayerId* newLayerId = this->getLayerId(i);
		   newSymbolLayer->appendLayerId(newLayerId);
        }

      return newSymbolLayer;
    }

private:
	QString _symboldir;
	QString _symbol;		// filename을 의미
};

#endif /* ASYMBOLLAYERITEM_H_ */
