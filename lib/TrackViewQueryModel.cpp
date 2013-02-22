/*
 * TrackViewQueryModel.cpp
 *
 *  Created on: 2012. 4. 27.
 *      Author: JMS
 *  Description : TrackViewSelection 클래스에서 사용하는 QSqlQueryModel를 재정의한다.
 */

#include "TrackViewQueryModel.h"

TrackViewQueryModel::TrackViewQueryModel(QObject* parent) : QSqlQueryModel(parent) {
	// TODO Auto-generated constructor stub

}

TrackViewQueryModel::~TrackViewQueryModel() {
	// TODO Auto-generated destructor stub
}

QVariant TrackViewQueryModel::data(const QModelIndex &item, int role) const
{
	QString header = (item.model()->headerData(item.column(), Qt::Horizontal, Qt::DisplayRole)).toString();

	if ( (role == Qt::DecorationRole) && item.column() == 0 && header == "Select") {
		QString data = item.data(Qt::DisplayRole).toString();

		qDebug() << "data called select...: " << data;
		if (data == "Y") {
			return Qt::Checked;
		}else {
			return Qt::Unchecked;
		}
	}else	if (role == Qt::TextAlignmentRole)
	{
	   return int(Qt::AlignCenter | Qt::AlignVCenter);
	}else {
		return QSqlQueryModel::data(item, role);
	}
}
//bool TrackViewQueryModel::setData( const QModelIndex & index, const QVariant & value, int role = Qt::EditRole )
//{
//	if(!index.isValid())
//	return false;
//
//	if (index.column() == 0) {
//		QVariant data = "Y";
//		return QSqlQueryModel::setData(index,data,Qt::DisplayRole);
//	}else {
//		return QSqlQueryModel::setData(index, value, role);
//	}
//}

