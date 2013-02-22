/*
 * TrackViewSelection.cpp
 *
 *  Created on: 2012. 4. 27.
 *      Author: JMS
 *  Description : 생성된 트렉 데이터를 현시할 수 있는 옵션창을 보여준다.
 *                     데이터베이스에서 트렉 데이터를 그룹화해서 그리드 화면에 뿌려준다.
 */
#include "TrackViewSelection.h"
#include "../lib/GlobalColor.h"

TrackViewSelection::TrackViewSelection(QWidget *parent)
    : QWidget(parent)
{
	setupUi(this);

	//setWindowFlags(Qt::WindowCloseButtonHint | Qt::WindowStaysOnTopHint
	//		| Qt::X11BypassWindowManagerHint | Qt::WindowSystemMenuHint);


	connect(btnSelectAll,    SIGNAL(clicked()), this, SLOT(selectAll()));
	connect(btnUnselectAll,  SIGNAL(clicked()), this, SLOT(unSelectAll()));
	connect(btnTrackReport,  SIGNAL(clicked()), this, SLOT(trackReport()));
	connect(btnVerticalView, SIGNAL(clicked()), this, SLOT(verticalView()));
	connect(btnADSB,         SIGNAL(clicked()), this, SLOT(viewADSB()));
	connect(btnDataBlock,    SIGNAL(clicked()), this, SLOT(viewDataBlock()));
	connect(btnClose,        SIGNAL(clicked()), this, SLOT(closeTrackData()));
	connect(btnReport,       SIGNAL(clicked()), this, SLOT(reportExcel()));
	//connect(this,            SLOT(close()),     this, SLOT(closeTrackData()));

	tableView->setAlternatingRowColors(true);
	tableView->setSelectionMode(QAbstractItemView::SingleSelection);
	tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
	tableView->resizeColumnsToContents();
	tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	tableView->setSortingEnabled(true);

	//connect(tableView, SIGNAL(clicked(const QModelIndex&)), this, SLOT(test()));

	dbManager = NULL;
	view      = NULL;
	//model = new TrackViewQueryModel;
	model.clear();
	xmlModel.clear();
	dataBlockCheck = 0;			// Data Block print (0 = not print)
	xmlCheck       = 0;			// Not xml data
}

TrackViewSelection::~TrackViewSelection()
{
	if (dbManager != NULL) {
		delete dbManager;
	}

	if (view != NULL) {
		delete view;
	}
}

void TrackViewSelection::closeEvent(QCloseEvent *event)
{
	qDebug() << "closeEvent called...";

	emit clearTrackData();
}
/**
 * XML 데이터를 읽어서 그리드 화면에 출력한다.
 */
void TrackViewSelection::trackXmlRead(QXmlStreamReader* xml)
{
	model.clear();
	xmlModel.clear();
	while (xml->readNextStartElement()) {
		if (xml->name() == "DataBlockInfo") {
			while (xml->readNextStartElement()) {
				if (xml->name() == "TrackNum") {
					if (xml->readElementText() == "True") {
						reportOption->trackNumber = true;
					}else {
						reportOption->trackNumber = false;
					}
				}else if(xml->name() == "AssignedFL") {
					if (xml->readElementText() == "True") {
						reportOption->assignedFL = true;
					}else {
						reportOption->assignedFL = false;
					}
				}else if(xml->name() == "Warning") {
					if (xml->readElementText() == "True") {
						reportOption->warning = true;
					}else {
						reportOption->warning = false;
					}
				}else if(xml->name() == "SSR") {
					if (xml->readElementText() == "True") {
						reportOption->ssr = true;
					}else {
						reportOption->ssr = false;
					}
				}else if(xml->name() == "Callsign") {
					if (xml->readElementText() == "True") {
						reportOption->callsing = true;
					}else {
						reportOption->callsing = false;
					}
				}else if(xml->name() == "ModeC") {
					if (xml->readElementText() == "True") {
						reportOption->modec = true;
					}else {
						reportOption->modec = false;
					}
				}else if(xml->name() == "Velocity") {
					if (xml->readElementText() == "True") {
						reportOption->velocity = true;
					}else {
						reportOption->velocity = false;
					}
				}else if(xml->name() == "BlockCount") {
					reportOption->blockCount = xml->readElementText().toInt();
				}else {
					xml->skipCurrentElement();
				}
			}
		}else if(xml->name() == "TrackList") {
			while (xml->readNextStartElement()) {
				if (xml->name() == "TrackInfo") {			// loop data
					TrackDataModel data;
					QVector<TrackData> mo;
					while (xml->readNextStartElement()) {
						if (xml->name() == "SSR") {
							data.ssr = xml->readElementText();
						}else if(xml->name() == "Callsign") {
							data.callsign = xml->readElementText();
						}else if(xml->name() == "TrackNo") {
							data.trackNo = xml->readElementText();
						}else if(xml->name() == "Alert") {
							data.alert = xml->readElementText();
						}else if(xml->name() == "Symbol") {
							data.symbol = xml->readElementText();
						}else if(xml->name() == "Color") {
							data.colorName = xml->readElementText();
							data.selectedColor = userRGBColor[getColorIndex(data.colorName)];
						}else if(xml->name() == "Track") {
							TrackData td;

							while (xml->readNextStartElement()) {
								if (xml->name() == "OCCUR_DT") {
									td.occur_dt = xml->readElementText();
								}else if(xml->name() == "LAT") {
									td.lat = xml->readElementText().toDouble();
								}else if(xml->name() == "LON") {
									td.lon = xml->readElementText().toDouble();
								}else if(xml->name() == "SPD") {
									td.spd = xml->readElementText().toDouble();
								}else if(xml->name() == "PREV_SPD") {
									td.prev_spd = xml->readElementText().toDouble();
								}else if(xml->name() == "HEADING") {
									td.heading = xml->readElementText().toDouble();
								}else if(xml->name() == "MLT_ALT") {
									td.mlt_alt = xml->readElementText().toInt();
								}else if(xml->name() == "ALT") {
									td.alt = xml->readElementText().toInt();
								}else if(xml->name() == "PREV_ALT") {
									td.prev_alt = xml->readElementText().toInt();
								}else if(xml->name() == "QNH") {
									td.qnh = xml->readElementText();
								}else if(xml->name() == "CLIMB") {
									td.climb = xml->readElementText().toInt();
								}else if(xml->name() == "SPI") {
									td.spi = xml->readElementText();
								}else if(xml->name() == "MRH") {
									td.mrh = xml->readElementText();
								}else if(xml->name() == "CNF") {
									td.cnf = xml->readElementText();
								}else if(xml->name() == "SIM") {
									td.sim = xml->readElementText();
								}else if(xml->name() == "TSE") {
									td.tse = xml->readElementText();
								}else if(xml->name() == "FPC") {
									td.fpc = xml->readElementText();
								}else if(xml->name() == "CST") {
									td.cst = xml->readElementText();
								}else if(xml->name() == "PSR") {
									td.psr = xml->readElementText();
								}else if(xml->name() == "SSR") {
									td.ssr = xml->readElementText();
								}else if(xml->name() == "MDS") {
									td.mds = xml->readElementText();
								}else if(xml->name() == "ADS") {
									td.ads = xml->readElementText();
								//}else if(xml->name() == "FL_TYPE") {
								//	td.fl_type = xml->readElementText();
								}else if(xml->name() == "FLT_RULE") {
									td.flt_rule = xml->readElementText();
								}else if(xml->name() == "RVSM") {
									td.rvsm = xml->readElementText();
								//}else if(xml->name() == "HPR") {
								//	td.hpr = xml->readElementText();
								}else if(xml->name() == "ACTP") {
									td.actp = xml->readElementText();
								}else if(xml->name() == "WT_TYPE") {
									td.wt_type = xml->readElementText();
								}else if(xml->name() == "DEP_AD") {
									td.dep_ad = xml->readElementText();
								}else if(xml->name() == "ARR_AD") {
									td.arr_ad = xml->readElementText();
								}else if(xml->name() == "RWAY_NO") {
									td.rway_no = xml->readElementText();
								}else if(xml->name() == "CFL") {
									td.cfl = xml->readElementText().toInt();
								}else if(xml->name() == "CENTER_ID") {
									td.center_id = xml->readElementText();
								}else if(xml->name() == "POS") {
									td.pos = xml->readElementText();
								}else if(xml->name() == "TYPE") {
									td.type = xml->readElementText().toInt();
								}else if(xml->name() == "ALERT") {
									td.alert = xml->readElementText();
								}else {
									xml->skipCurrentElement();
								}
							}
							mo.append(td);

						}else {
							xml->skipCurrentElement();
						}
					}
					data.dataModel = mo;
					xmlModel.append(data);
				}else {
					xml->skipCurrentElement();
				}
			}
		}else {
			xml->skipCurrentElement();
		}
	}

	xmlCheck = 1;
	makeGridView();
}

/**
 * Track 데이터를 조회해서 그리드 화면에 출력한다.
 */
void TrackViewSelection::trackDataSearch()
{
	qDebug() << "trackDataSearch called...";
	if (dbManager == NULL) {
		dbManager = new DbManager();
		dbManager->setLog(log);
	}
	xmlCheck = 0;
	bool b = dbManager->setDb(ConfigParser::getInstance().driver(),
			ConfigParser::getInstance().host(),
			ConfigParser::getInstance().db(),
			ConfigParser::getInstance().user(),
			ConfigParser::getInstance().password(),
			ConfigParser::getInstance().port());
	if (!b) {
		QString errmsg = dbManager->error();
		//QMessageBox::critical(this, "DB Connection Error", errmsg);
		qDebug() << errmsg;
		return;
	}
	removeAll();

	QStringList labels;
	labels << tr("Select") << tr("SSR") << tr("Callsign") << tr("Track No") << tr("Alert") << tr("Symbol") << tr("Color") << tr("Counter Track");
	tableView->horizontalHeader()->setDefaultSectionSize(90);
	tableView->setColumnCount(8);
	tableView->setHorizontalHeaderLabels(labels);
	tableView->horizontalHeader()->setResizeMode(0, QHeaderView::Fixed);
	tableView->verticalHeader()->hide();
	tableView->setSelectionMode(QAbstractItemView::NoSelection);
	tableView->setItemDelegate(new CustomItemDelegate(this));

	QString sql;
	sql  = " SELECT 'N', SSR, CALLSIGN, TO_CHAR(TRK_NO),                ";
	sql += "        (SELECT TO_CHAR(SAFETY_MSG_TP) FROM TB_TRK WHERE TRK_NO=A.TRK_NO AND ROWNUM=1),   ";
	sql += "        '', '', '' ";
	sql += "   FROM TB_TRK A                                            ";
	sql += "  GROUP BY SSR, CALLSIGN, TRK_NO                            ";
	sql += " UNION                                                      ";
	sql += " SELECT 'N', '' AS SSR, CALLSIGN, '' AS TRK_NO, '', '', '', ''  ";
	sql += "   FROM TB_ADSB                                             ";
	sql += "  GROUP BY CALLSIGN                                         ";


	QSqlQuery* query = new QSqlQuery(QSqlDatabase::database(dbManager->dbName()));

	query->prepare(sql);
	query->exec();

	if (query->lastError().type() != QSqlError::NoError) {
		delete query;
		QMessageBox::critical(this, "SQL Error", query->lastError().text());
		return;
	}
	while(query->next()) {
		int row = tableView->rowCount();
		tableView->setRowCount(row + 1);

		QTableWidgetItem *item0 = new QTableWidgetItem();
		item0->setData(Qt::UserRole, "N");
		//item0->setFlags(item0->flags() & ~Qt::ItemIsEditable);
		item0->setFlags(Qt::ItemIsEnabled|Qt::ItemIsUserCheckable);

		QTableWidgetItem *item1 = new QTableWidgetItem(query->value(1).toString());
		QTableWidgetItem *item2 = new QTableWidgetItem(query->value(2).toString());
		QTableWidgetItem *item3 = new QTableWidgetItem(query->value(3).toString());
		QTableWidgetItem *item4 = new QTableWidgetItem(query->value(4).toString());
		QTableWidgetItem *item5 = new QTableWidgetItem(query->value(5).toString());
		QTableWidgetItem *item6 = new QTableWidgetItem(query->value(6).toString());
		QTableWidgetItem *item7 = new QTableWidgetItem(query->value(7).toString());		// 비교할 트랙 No 필드

		tableView->setItem(row, 0, item0);
		tableView->setItem(row, 1, item1);
		tableView->setItem(row, 2, item2);
		tableView->setItem(row, 3, item3);
		tableView->setItem(row, 4, item4);
		tableView->setItem(row, 5, item5);
		tableView->setItem(row, 6, item6);
		tableView->setItem(row, 7, item7);

		//tableView->openPersistentEditor(item0);
		tableView->openPersistentEditor(item5);
		tableView->openPersistentEditor(item6);
		tableView->openPersistentEditor(item7);		// 트랙번호를 입력할 수 있도록 한다
		item0->setCheckState(Qt::Unchecked);
	}
	query->finish();

	delete query;
}

/**
 * XML 모델 데이터를 가지고 그리드 화면을 구성한다.
 */
void TrackViewSelection::makeGridView()
{
	QStringList labels;

	removeAll();

	labels << tr("Select") << tr("SSR") << tr("Callsign") << tr("Track No") << tr("Alert") << tr("Symbol") << tr("Color") << tr("Counter Track");
	tableView->horizontalHeader()->setDefaultSectionSize(90);
	tableView->setColumnCount(8);
	tableView->setHorizontalHeaderLabels(labels);
	tableView->horizontalHeader()->setResizeMode(0, QHeaderView::Fixed);
	tableView->verticalHeader()->hide();
	tableView->setSelectionMode(QAbstractItemView::NoSelection);
	tableView->setItemDelegate(new CustomItemDelegate(this));


	for (int i=0; i<xmlModel.size(); i++) {
		TrackDataModel td = xmlModel.at(i);

		int row = tableView->rowCount();
		tableView->setRowCount(row + 1);

		QTableWidgetItem *item0 = new QTableWidgetItem();
		item0->setData(Qt::UserRole, "Y");
		//item0->setFlags(item0->flags() & ~Qt::ItemIsEditable);
		item0->setFlags(Qt::ItemIsEnabled|Qt::ItemIsUserCheckable);

		QTableWidgetItem *item1 = new QTableWidgetItem(td.ssr);
		QTableWidgetItem *item2 = new QTableWidgetItem(td.callsign);
		QTableWidgetItem *item3 = new QTableWidgetItem(td.trackNo);
		QTableWidgetItem *item4 = new QTableWidgetItem(td.alert);
		QTableWidgetItem *item5 = new QTableWidgetItem;  //(td.symbol);
		item5->setData(Qt::UserRole, td.symbol);

		QTableWidgetItem *item6 = new QTableWidgetItem;
		item6->setData(Qt::UserRole, td.colorName);
		item6->setData(Qt::EditRole, getColorIndex(td.colorName));

		QTableWidgetItem *item7 = new QTableWidgetItem(td.disTrack);

		tableView->setItem(row, 0, item0);
		tableView->setItem(row, 1, item1);
		tableView->setItem(row, 2, item2);
		tableView->setItem(row, 3, item3);
		tableView->setItem(row, 4, item4);
		tableView->setItem(row, 5, item5);
		tableView->setItem(row, 6, item6);
		tableView->setItem(row, 7, item7);


		//tableView->openPersistentEditor(item0);
		tableView->openPersistentEditor(item5);
		tableView->openPersistentEditor(item6);
		tableView->openPersistentEditor(item7);
	}

	selectAll();
}

/**
 * CheckBox select all set
 */
void TrackViewSelection::selectAll()
{
	//qDebug() << "selectAll called....";

	for (int i=0; i<tableView->rowCount(); i++) {
		QTableWidgetItem* item = tableView->item(i, 0);
		item->setCheckState(Qt::Checked);
	}
}
/**
 * CheckBox unselect all set
 */
void TrackViewSelection::unSelectAll()
{
	for (int i=0; i<tableView->rowCount(); i++) {
		QTableWidgetItem* item = tableView->item(i, 0);
		item->setCheckState(Qt::Unchecked);
	}
}

/**
 * 선택한 항적을 지정된 Symbol과 Color를 사용하여 Map Editor Panel에 출력한다.
 */
void TrackViewSelection::trackReport()
{
	model.clear();

	for (int i=0; i<tableView->rowCount(); i++) {
		QTableWidgetItem* item  = tableView->item(i, 0);
		QTableWidgetItem* item3 = tableView->item(i, 3);	// Track No
		QTableWidgetItem* item7 = tableView->item(i, 7);	// Distance Track

		if (!item7->text().isEmpty() && item7->text().length() > 0) {
			int found = -1;
			for (int j=0; j<tableView->rowCount(); j++) {
				QTableWidgetItem* t1 = tableView->item(j, 0);
				QTableWidgetItem* t2 = tableView->item(j, 3);	// Track No
				QTableWidgetItem* t3 = tableView->item(j, 7);	// Distance Track

				if (t2->text() == item7->text()) {
					found = 1;
					t1->setCheckState(Qt::Checked);
					break;
				}
			}

			if (found == -1) {
				QMessageBox::warning(this, tr("No Track Number"), tr("Track Number not exists.."));
				return;
			}
		}else {
			continue;
		}
	}

	for (int i=0; i<tableView->rowCount(); i++) {
		QTableWidgetItem* item = tableView->item(i, 0);
		if (item->checkState() == Qt::Checked) {
			QTableWidgetItem* item1 = tableView->item(i, 1);	// SSR
			QTableWidgetItem* item2 = tableView->item(i, 2);	// Callsign
			QTableWidgetItem* item3 = tableView->item(i, 3);	// Track No
			QTableWidgetItem* item4 = tableView->item(i, 4);	// Alert
			QTableWidgetItem* item5 = tableView->item(i, 5);	// Symbol
			QTableWidgetItem* item6 = tableView->item(i, 6);	// Color
			QTableWidgetItem* item7 = tableView->item(i, 7);	// Distance Track

			//qDebug() << "trackReport : " << item5->data(Qt::UserRole).toString();
			//qDebug() << "trackReport : " << item5->data(Qt::DisplayRole).toString();

			if (item5->data(Qt::UserRole).toString().isEmpty()) {
				QMessageBox::warning(this, tr("Symbol Icon Not Select"), tr("The symbol icon is not selected."));
				return;
			}

			TrackDataModel data;
			data.ssr       = item1->text();
			data.callsign  = item2->text();
			data.trackNo   = item3->text();
			data.alert     = item4->text();
			//data.symbolIdx = item5->text().toInt();
			data.selectedColor  = userRGBColor[item6->text().toInt()];
			data.colorName = userColor[item6->text().toInt()];
			QString fileName = item5->data(Qt::UserRole).toString();
			data.symbol = fileName;
			data.disTrack  = item7->text();

			// Track Data
			if (xmlCheck == 0) {
				data.dataModel = getTrackDetailInfo(data.ssr, data.callsign, data.trackNo);
			}else {
				for (int i=0; i<xmlModel.size(); i++) {
					TrackDataModel t = xmlModel.at(i);

					if (t.ssr == data.ssr && t.callsign == data.callsign && t.trackNo == data.trackNo) {
						data.dataModel = t.dataModel;
						break;
					}
				}
			}

			model.push_back(data);
		}
	}

	if (model.count() > 0) {
		emit trackReport(model);
	}else {
		QMessageBox::warning(this, "Track Report Error", tr("After it select the checkbox, press the track report button."));
		return;
	}
}

/**
 * Vertical View Display
 */
void TrackViewSelection::verticalView()
{
	if (model.size() > 0) {
		if (view == NULL) {
			view = new VerticalView;
			view->setReportOption(reportOption);
		}
		view->setTrackModel(model);
		view->makeDisplay();
		view->show();
	}else {
		//QMessageBox::warning(this, "Track Report Error", tr("After it select the checkbox, press the Vertical View button."));
	}
}

/**
 * Print ADS-B
 */
void TrackViewSelection::viewADSB()
{
	model.clear();

	for (int i=0; i<tableView->rowCount(); i++) {
		QTableWidgetItem* item = tableView->item(i, 0);
		if (item->checkState() == Qt::Checked) {
			QTableWidgetItem* item1 = tableView->item(i, 1);	// SSR
			QTableWidgetItem* item2 = tableView->item(i, 2);	// Callsign
			QTableWidgetItem* item3 = tableView->item(i, 3);	// Track No
			QTableWidgetItem* item4 = tableView->item(i, 4);	// Alert
			QTableWidgetItem* item5 = tableView->item(i, 5);	// Symbol
			QTableWidgetItem* item6 = tableView->item(i, 6);	// Color
			QTableWidgetItem* item7 = tableView->item(i, 7);   // Dis.Track

			//qDebug() << "trackReport : " << item5->data(Qt::UserRole).toString();
			if (item5->data(Qt::UserRole).toString().isEmpty()) {
				QMessageBox::warning(this, tr("Symbol Icon Not Select"), tr("The symbol icon is not selected."));
				return;
			}

			TrackDataModel data;
			data.ssr       = item1->text();
			data.callsign  = item2->text();
			data.trackNo   = item3->text();
			data.alert     = item4->text();
			//data.symbolIdx = item5->text().toInt();
			data.selectedColor  = userRGBColor[item6->text().toInt()];
			data.colorName = userColor[item6->text().toInt()];
			QString fileName = item5->data(Qt::UserRole).toString();
			data.symbol = fileName;
			data.disTrack  = item7->text();
			// Track Data
			if (xmlCheck == 0) {
				data.dataModel = getADSBDetailInfo(data.ssr, data.callsign, data.trackNo);
			}else {
				for (int i=0; i<xmlModel.size(); i++) {
					TrackDataModel t = xmlModel.at(i);

					if (t.ssr == data.ssr && t.callsign == data.callsign && t.trackNo == data.trackNo) {
						data.dataModel = t.dataModel;
						break;
					}
				}
			}

			model.push_back(data);
		}
	}

	if (model.count() > 0) {
		emit trackReport(model);
	}else {
		QMessageBox::warning(this, "Track Report Error", tr("After it select the checkbox, press the track report button."));
		return;
	}
}

/**
 * Data Block Print / Not Print
 */
void TrackViewSelection::viewDataBlock()
{
	qDebug() << dataBlockCheck;
	if (dataBlockCheck == 0) {
		dataBlockCheck = 1;		// print
	}else {
		dataBlockCheck = 0;		// not print
	}

	emit dataBlockPrint(dataBlockCheck);
}

/**
 * Report Excel make call
 */
void TrackViewSelection::reportExcel()
{
	model.clear();

	for (int i=0; i<tableView->rowCount(); i++) {
		QTableWidgetItem* item = tableView->item(i, 0);
		//if (item->checkState() == Qt::Checked) {
			QTableWidgetItem* item1 = tableView->item(i, 1);	// SSR
			QTableWidgetItem* item2 = tableView->item(i, 2);	// Callsign
			QTableWidgetItem* item3 = tableView->item(i, 3);	// Track No
			QTableWidgetItem* item4 = tableView->item(i, 4);	// Alert
			QTableWidgetItem* item5 = tableView->item(i, 5);	// Symbol
			QTableWidgetItem* item6 = tableView->item(i, 6);	// Color
			QTableWidgetItem* item7 = tableView->item(i, 7);   // Distance Track
			//qDebug() << "trackReport : " << item5->data(Qt::UserRole).toString();
//			if (item5->data(Qt::UserRole).toString().isEmpty()) {
//				QMessageBox::warning(this, tr("Symbol Icon Not Select"), tr("The symbol icon is not selected."));
//				return;
//			}

			TrackDataModel data;
			data.ssr       = item1->text();
			data.callsign  = item2->text();
			data.trackNo   = item3->text();
			data.alert     = item4->text();
			//data.symbolIdx = item5->text().toInt();
			data.selectedColor  = userRGBColor[item6->text().toInt()];
			data.colorName = userColor[item6->text().toInt()];
			QString fileName = item5->data(Qt::UserRole).toString();
			data.symbol = fileName;
			data.disTrack  = item7->text();
			// Track Data
			if (xmlCheck == 0) {
				data.dataModel = getTrackDetailInfo(data.ssr, data.callsign, data.trackNo);
			}else {
				for (int i=0; i<xmlModel.size(); i++) {
					TrackDataModel t = xmlModel.at(i);

					if (t.ssr == data.ssr && t.callsign == data.callsign && t.trackNo == data.trackNo) {
						data.dataModel = t.dataModel;
						break;
					}
				}
			}

			model.push_back(data);
		//}
	}

	if (model.count() > 0) {
		// File name get
		QString fileName = QString("%1/TrackReport-%2-%3.xls").arg(ConfigParser::getInstance().envMapDir()).arg(QDate::currentDate().toString("yyyyMMdd")).arg(QDateTime::currentDateTime().toString("hhmmss"));


		// Text file make
		QFile data("track_tmp.txt");
 	   if (data.open(QFile::WriteOnly | QFile::Truncate)) {
 		   QTextStream out(&data);
 		   QString trackData;
 		   for (int i=0; i<model.count(); i++) {
 			   if (i == 0) {
 				   // header make
 				   QString header = "SSR,CALLSIGN,TRACK NO,TYPE,ALERT,OCCUR DATE,LAT,LON,SPEED,HEADING,ALT,CST,PSR,SSR\n";
 				   out << header;
 			   }
 			   TrackDataModel data = model.at(i);

 			   QVector<TrackData> track = data.dataModel;
 			   for (int j=0; j<track.size(); j++) {
 				   //if (j != 0) out << "\n";
 				   TrackData td = track.at(j);
 				   int psr = 0;
 				   int ssr = 0;

 				   if (td.psr == "0" && td.ssr == "1") {   // psr only
 					   psr = 1;
 					   ssr = 0;
 				   }else if(td.psr == "1" && td.ssr == "0") {	// ssr only
 					   psr = 0;
 					   ssr = 1;
 				    }

 				   trackData = QString("%1,%2,%3,%4,%5,%6,%7,%8,%9,%10,%11,%12,%13,%14\n")
						.arg(QString(" %1").arg(data.ssr)).arg(data.callsign).arg(data.trackNo)
						.arg(td.type).arg(td.alert).arg(td.occur_dt).arg(td.lat).arg(td.lon)
						.arg(td.spd).arg(td.heading).arg(td.alt).arg(td.cst)
						.arg(psr).arg(ssr);
 				   out << trackData;
 				   //qDebug() << trackData;
 			   }
 		   }
 	   }
 		// perl module execute
		QProcess builder;
		QString  msg;
		builder.setProcessChannelMode(QProcess::MergedChannels);
		builder.start("perl", QStringList() << "track_data_to_excel.pl" << "track_tmp.txt" << fileName);

		if (!builder.waitForFinished()) {
		    qDebug() << "Make failed:" << builder.errorString();
		    QMessageBox::warning(this, tr("Excel File Make Error"), tr("Can't Make Excel File."));
		    return;
		} else {
			msg = QString(builder.readAll());
		}
		qDebug() << msg;

		if (msg != "-1") {
			QString str = QString("%1 was generated").arg(fileName);
			QMessageBox::information(this, "Track Report Success", tr("%1").arg(str));
		}
	}else {
		QMessageBox::warning(this, "Track Report Error", tr("The track data not found..."));
		return;
	}
	model.clear();
}
/**
 * Data Block delete
 */
void TrackViewSelection::closeTrackData()
{
	close();
}

/**
 * Track 상세 정보를 조회해서 QVector 넣어 리턴한다.
 */
QVector<TrackData> TrackViewSelection::getTrackDetailInfo(QString ssr, QString callsign, QString trackNum)
{
	QString sql;
	QVector<TrackData> mo;
	mo.clear();

	QSqlQuery* query = new QSqlQuery(QSqlDatabase::database(dbManager->dbName()));

	sql  = "SELECT TO_CHAR(OCCUR_DT, 'yyyy-MM-dd HH24:MI:SS') occur_dt,      ";
	sql += "       LAT, LON, SPD, HEADING, MLT_ALT, ALT, QNH, CLIMB_DESCENT, ";
	sql += "       SPI_CHK, MRH_CHK, CNF_CHK, SIM_CHK, TSE_CHK, FPC_CHK,     ";
	sql += "       CST_CHK, PSR_CHK, SSR_CHK, MDS_CHK, ADS_CHK,              ";
	sql += "       FLT_RULE, RVSM, ACTP, WT, DEP_AD,                    ";
	sql += "       ARR_AD,  RWAY_NO, CFL, CENTER_ID, POS, 0 AS TYPE, SAFETY_MSG_TP          ";
	sql += "  FROM TB_TRK                                                    ";
	sql += " WHERE                                                           ";
	sql += "       1 = 1                                                     ";

	if (!ssr.isEmpty())
		sql += "   AND SSR = ?                                                ";
	else
		sql += "   AND SSR IS NULL ";
	if (!trackNum.isEmpty())
		sql += "   AND TRK_NO = ?                                             ";
	if (!callsign.isEmpty())
		sql += "   AND CALLSIGN = ?                                           ";
	else
		sql += "   AND CALLSIGN IS NULL ";

	sql += " ORDER BY OCCUR_DT                                               ";
	query->prepare(sql);
	if (!ssr.isEmpty())
		query->addBindValue(ssr);
	if (!trackNum.isEmpty())
		query->addBindValue(trackNum);
	if (!callsign.isEmpty())
		query->addBindValue(callsign);

	query->exec();

	if (query->lastError().type() != QSqlError::NoError) {
		qDebug() << query->lastError().text();
		query->finish();
		delete query;
		return mo;
	}
	double prev_spd = 0.0;
	int    prev_alt = 0;

	while(query->next()) {
		TrackData data;

		if (mo.size() == 0) {
			data.prev_spd = 0.0;
			data.prev_alt = -1;			// first data
		}else {
			TrackData t = mo.at(mo.size()-1);		// 이전 데이터를 가져와서 Speed, alt를 현재 트랙에 저장한다.
			data.prev_spd = t.spd;
			data.prev_alt = t.alt;
		}
		data.occur_dt = query->value(0).toString();
		data.lat      = query->value(1).toDouble();
		data.lon      = query->value(2).toDouble();
		data.spd      = query->value(3).toDouble();
		data.heading  = query->value(4).toDouble();
		data.mlt_alt  = query->value(5).toInt();
		data.alt      = query->value(6).toInt();
		data.qnh      = query->value(7).toString();
		data.climb    = query->value(8).toInt();
		data.spi      = query->value(9).toString();
		data.mrh      = query->value(10).toString();
		data.cnf      = query->value(11).toString();
		data.sim      = query->value(12).toString();
		data.tse      = query->value(13).toString();
		data.fpc      = query->value(14).toString();
		data.cst      = query->value(15).toString();
		data.psr      = query->value(16).toString();
		data.ssr      = query->value(17).toString();
		data.mds      = query->value(18).toString();
		data.ads      = query->value(19).toString();
		data.flt_rule = query->value(20).toString();
		data.rvsm     = query->value(21).toString();
		data.actp     = query->value(22).toString();
		data.wt_type  = query->value(23).toString();
		data.dep_ad   = query->value(24).toString();
		data.arr_ad   = query->value(25).toString();
		data.rway_no  = query->value(26).toString();
		data.cfl      = query->value(27).toInt();
		data.center_id    = query->value(28).toString();
		data.pos      = query->value(29).toString();
		data.type     = query->value(30).toInt();
		data.alert    = query->value(31).toString();

		mo.push_back(data);
	}

	query->finish();
	delete query;

	return mo;
}

/**
 * ADS-B 상세 정보를 조회해서 QVector 넣어 리턴한다.
 */
QVector<TrackData> TrackViewSelection::getADSBDetailInfo(QString ssr, QString callsign, QString trackNum)
{
	QString sql;
	QVector<TrackData> mo;
	mo.clear();

	QSqlQuery* query = new QSqlQuery(QSqlDatabase::database(dbManager->dbName()));

	sql  = "SELECT TO_CHAR(OCCUR_DT, 'yyyy-MM-dd HH24:MI:SS') occur_dt,      ";
	sql += "       LAT, LON, SPD, HEADING, 0 AS MLT_ALT, ALT, '' AS QNH, 0 AS CLIMB_DESCENT, ";
	sql += "       '' AS SPI_CHK, '' AS MRH_CHK, '' AS CNF_CHK, '' AS SIM_CHK, '' AS TSE_CHK, '' AS FPC_CHK,     ";
	sql += "       '' AS CST_CHK, '' AS PSR_CHK, '' AS SSR_CHK, '' AS MDS_CHK, '' AS ADS_CHK,              ";
	sql += "       '' AS FLT_RULE, '' AS RVSM, '' AS ACTP, '' AS WT_TYPE, '' AS DEP_AD,                    ";
	sql += "       '' AS ARR_AD,  '' AS RWAY_NO, '' AS CFL, '' AS CENTER_ID, '' AS POS, 1 AS TYPE          ";		// type : 1 - ADSB
	sql += "  FROM TB_ADSB                                                    ";
	sql += " WHERE                                                           ";
	sql += "       1 = 1                                                     ";

	sql += "   AND CALLSIGN = ?                                              ";
	sql += " ORDER BY OCCUR_DT                                               ";
	query->prepare(sql);
	query->addBindValue(callsign);
	query->exec();

	if (query->lastError().type() != QSqlError::NoError) {
		qDebug() << query->lastError().text();
		query->finish();
		delete query;
		return mo;
	}
	double prev_spd = 0.0;
	int    prev_alt = 0;

	while(query->next()) {
		TrackData data;

		if (mo.size() == 0) {
			data.prev_spd = 0.0;
			data.prev_alt = -1;			// first data
		}else {
			TrackData t = mo.at(mo.size()-1);		// 이전 데이터를 가져와서 Speed, alt를 현재 트랙에 저장한다.
			data.prev_spd = t.spd;
			data.prev_alt = t.alt;
		}
		data.occur_dt = query->value(0).toString();
		data.lat      = query->value(1).toDouble();
		data.lon      = query->value(2).toDouble();
		data.spd      = query->value(3).toDouble();
		data.heading  = query->value(4).toDouble();
		data.mlt_alt  = query->value(5).toInt();
		data.alt      = query->value(6).toInt();
		data.qnh      = query->value(7).toString();
		data.climb    = query->value(8).toInt();
		data.spi      = query->value(9).toString();
		data.mrh      = query->value(10).toString();
		data.cnf      = query->value(11).toString();
		data.sim      = query->value(12).toString();
		data.tse      = query->value(13).toString();
		data.fpc      = query->value(14).toString();
		data.cst      = query->value(15).toString();
		data.psr      = query->value(16).toString();
		data.ssr      = query->value(17).toString();
		data.mds      = query->value(18).toString();
		data.ads      = query->value(19).toString();
		data.flt_rule = query->value(20).toString();
		data.rvsm     = query->value(21).toString();
		data.actp     = query->value(22).toString();
		data.wt_type  = query->value(23).toString();
		data.dep_ad   = query->value(24).toString();
		data.arr_ad   = query->value(25).toString();
		data.rway_no  = query->value(26).toString();
		data.cfl      = query->value(27).toInt();
		data.center_id    = query->value(28).toString();
		data.pos      = query->value(29).toString();
		data.type     = query->value(30).toInt();
		data.alert    = "";
		mo.push_back(data);
	}

	query->finish();
	delete query;

	return mo;
}

/**
 * return Color index
 */
int TrackViewSelection::getColorIndex(QString colorName)
{
	for (int i=0; i<(int)sizeof(userColor); i++) {
		if (colorName == userColor[i]) {
			return i;
		}
	}
	return -1;
}

void TrackViewSelection::removeAll() {
	int row = tableView->rowCount();
	for (int i=row-1; i >= 0; i--) {
		tableView->removeRow(i);
	}
}
