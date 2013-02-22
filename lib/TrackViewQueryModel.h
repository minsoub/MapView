/*
 * TrackViewQueryModel.h
 *
 *  Created on: 2012. 4. 27.
 *      Author: JMS
 *  Description : TrackViewSelection 클래스에서 사용하는 QSqlQueryModel를 재정의한다.
 */

#ifndef TRACKVIEWQUERYMODEL_H_
#define TRACKVIEWQUERYMODEL_H_
#include <QtGui>
#include <QSqlQueryModel>

class TrackViewQueryModel : public QSqlQueryModel {
	Q_OBJECT
public:
	TrackViewQueryModel(QObject* parent = 0);
	virtual ~TrackViewQueryModel();
	virtual QVariant data(const QModelIndex &item, int role) const;
	//virtual bool setData( const QModelIndex & index, const QVariant & value, int role = Qt::EditRole );
};

#endif /* TRACKVIEWQUERYMODEL_H_ */
