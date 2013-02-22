/*
 * AHoldLayerItem.h
 *
 *  Created on: 2012. 2. 29.
 *      Author: HIST002
 */

#ifndef AHOLDLAYERITEM_H_
#define AHOLDLAYERITEM_H_

#include "ALinesLayerItem.h"

class AHoldLayerItem : public ALinesLayerItem {
public:
	enum { Type = 1 };
	int type() const { return Type; }
	AHoldLayerItem(LayerType t) : ALinesLayerItem(t)
	{
		_classtype = ClassHold;
	};
	AHoldLayerItem &operator= (AHoldLayerItem &tmp) {

	    return *this;
	}
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
   virtual AHoldLayerItem* clone () {
    	AHoldLayerItem* newHoldLayer = new AHoldLayerItem(_layertype);
      *newHoldLayer = *this;
      newHoldLayer->clear();
      newHoldLayer->_lp = this->_lp;
 	   for (int i=0; i<_list.count(); i++) {
 		   const ALayerId* newLayerId = this->getLayerId(i);
 		   newHoldLayer->appendLayerId(newLayerId);
 	    }
      return newHoldLayer;
    }

};

#endif /* AHOLDLAYERITEM_H_ */
