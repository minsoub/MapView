/*
 * LayerDefine.h
 *
 *  Created on: 2012. 1. 27.
 *      Author: HIST002
 *  Description : 레이어 이름과 순서등을 일괄되게 유지하기 위해서 작성
 */

#ifndef LAYERDEFINE_H_
#define LAYERDEFINE_H_

#include <QList>
#include "MapDefine.h"

class LayerDefine {
public:
	LayerDefine();
	~LayerDefine();
	int layerNo(LayerType t);
	int layerType(int no);
	int layerType(const QString& shortname);
	QString shortName(int no) const;
	QString shortName(LayerType t) const;
	QString fullName(int no) const;
	QString fullName(LayerType t) const;
	int count();
	QVector<LayerType>* getGroupMembers(int t);   // not implementation
private:
	QVector<LayerItem*> list;
	QVector<LayerType> groups;
	void add(LayerType t, const QString& sn, const QString& fn, GroupLayerType gt);
};

#endif /* LAYERDEFINE_H_ */
