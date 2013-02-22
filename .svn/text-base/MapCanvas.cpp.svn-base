/*
 * MapCanvas.cpp
 *
 *  Created on: 2012. 1. 16.
 *      Author: HIST002
 */
#include <iostream>
#include "MapCanvas.h"
#include "./lib/CalcAir.h"
#include "./lib/ConfigParser.h"

//#ifndef QT_NO_CONCURRENT

using namespace QtConcurrent;

MapCanvas::MapCanvas(QWidget *parent):QWidget(parent) {
	// TODO Auto-generated constructor stub
	dbmanager = NULL;
	isUserDefinedMap = false;

	QString logfileName = ConfigParser::getInstance().logFileName();
	log = new Log424(logfileName);
	log->setEnable(ConfigParser::getInstance().logEnable());
	log->setEnable(true);  //-- debug
	air = new AirDraw(&vp, log);

	// map data read
	map = new AMap(*log, air);
#ifndef QT_NO_DEBUG
	log->print("map class created....");
#endif

	//generateMap(MapFileParser::getInstance().getMapFile());

	QString mapfile = ConfigParser::getInstance().mapFile();
#ifndef QT_NO_DEBUG
	log->print(QString("mapfile %1 open").arg(mapfile));
#endif

	map->read(mapfile);
#ifndef QT_NO_DEBUG
	log->print(QString("mapfile %1 read ok").arg(mapfile));
#endif

	ConfigParser::getInstance().setBgcolor(map->bgcolor());		// background color

	ConfigParser::getInstance().setWonJum(map->defaultWonjum());
	symboldir = QString("%1/images").arg(ConfigParser::getInstance().envMapDir());
#ifndef QT_NO_DEBUG
	log->print("symboldir::" + symboldir);
#endif
	map->setSymboldir(symboldir);

	QString layerVisible = ConfigParser::getInstance().layerVisible();
#ifndef QT_NO_DEBUG
	log->print("LayerVisible : " + layerVisible);
#endif
	for (int i=0; i<layerVisible.length(); i++) {
		drawFlag[i] = (layerVisible[i] == QChar('1') ? Visible : Unvisible);
	}

	// ViewPort 생성
	double north    = ConfigParser::getInstance().lat();
	double greenich = ConfigParser::getInstance().lon();
	double mpp      = ConfigParser::getInstance().mpp();	// default : 2000

	vp.setWonjumNorthGreenich(QPointF(north, greenich));
	vp.setMeterPerPixel(mpp);

	view = new GenerateView(this);
	qDebug() << "View bgcolor set";
	//view->setBackgroundBrush(mapconf.bg_color());

	screenRect    = QRect(0, 0, view->width(), view->height());

	vp.setScreenRect(screenRect);
	vp.setScreen00(screenRect.center());
#ifndef QT_NO_DEBUG
	log->print("Viewport setting >>");
	log->print(vp.toString());
#endif

	main = new QGraphicsScene(screenRect);
	qDebug() << "Scene bgcolor set";
	main->setBackgroundBrush(ConfigParser::getInstance().bgcolor());

	qDebug() << "MapCanvas bgcolor : " << mapconf.bg_color();



	view->setScene(main);
	view->setLog(log);
	view->setScreenConvertClass(&vp);

	//view->show();
	QVBoxLayout *layout = new QVBoxLayout;
	layout->addWidget(view);

	this->setLayout(layout);

	this->setAutoFillBackground(true);
	//log->print(QString("MapCanvas constructor width : %1 height : %2").arg(width()).arg(height()));

	connect(view, SIGNAL(changeMousePos(QString)),      this, SLOT(catchMousePos(QString)));
	connect(view, SIGNAL(changeLatLonPos(QString)),     this, SLOT(catchLatLonPos(QString)));
	connect(view, SIGNAL(changeStatusMessage(QString)), this, SLOT(catchStatusMessage(QString)));
	connect(view, SIGNAL(setChangeZoom(double)),        this, SLOT(changeZoom(double)));
	textvisible = false;

	// User Layer에 대해서 setSymbolDir 을 설정
	//userlayer->setSymbolDir(symboldir);

	// LayerList register
	// config에 따라서 layer의 visible을 셋팅
	for (int i=0; i<layerVisible.length(); i++) {
		ALayer* layer = map->findLayer((LayerType)lyrdef.layerType(i));
		if (layer != NULL) {
			layer->setLayerVisible(layerVisible[i] == QChar('1'));

			// Layer가 Symbol dir이면
			if (layer->classType() == ClassSymbol) {
				ASymbolLayerItem* symbollayer = (ASymbolLayerItem *)layer;
				symbollayer->setSymbolDir(symboldir);
			}
			main->addItem(layer);
		}
	}
	map->userLayer()->setLayerVisible(layerVisible[(int)(Layer_User)] == QChar('1'));
#ifndef QT_NO_DEBUG
	log->print("Layer visible setting with config file done..");
#endif

	for (int i=0; i<map->userLayer()->layerCount(); i++) {
		main->addItem(map->userLayer()->getUserList()[i]);	// User map layer
	}


	// User define Map List
	for (int i=0; i<map->udmListCount(); i++) {
		AUserDefinedMap* udm = map->getUDMap(i);
		udm->setVisible(true);
		if (udm != NULL) {
			for (int j=0; j<udm->LayerCount(); j++) {
				AUserDefinedLayer* udlayer = udm->layer(j);
				QString layername = udlayer->getId();
				ALayer* realLayer = udlayer->getLayer();  // map->findLayer(layername);
				realLayer->setAirdraw(air);
				//realLayer->setVisible(false);
				realLayer->setLayerVisible(false);
				// Layer가 Symbol dir이면
				if (realLayer->classType() == ClassSymbol) {
					ASymbolLayerItem* symbollayer = (ASymbolLayerItem *)realLayer;
					symbollayer->setSymbolDir(symboldir);
				}
				if (realLayer == NULL) {
					qDebug() << "NULL...layer...";
				}else {
					//qDebug() << "AUserDEfinedMap add item..." << realLayer->toString();
					main->addItem(realLayer);
				}
			}
		}
	}


	// UserDraw
	ud = new UserDrawItem(this);
	ud->setAirDraw(air);
	main->addItem(ud);

	view->setUserDrawItem(ud);
	connect(view, SIGNAL(userFinishedDrawCall()), this, SLOT(finishedDraw()));
	connect(view, SIGNAL(leftPanelWidgetChange()), this, SLOT(leftChangedToReload()));
	inputusertextDialog = NULL;


	isBearingCircle = true;
	isLatlonItem    = true;

	// 사용자 거리 / 방위각 item
	distbear = new DirBearing;
	distbear->setScreenConvertClass(&vp);
	main->addItem(distbear);
	view->setUserDistBearing(distbear);

	// Bearing circle item painting
	bearingCircleItem = new BearingCircleItem;
	bearingCircleItem->setScreenConvertClass(&vp);
	main->addItem(bearingCircleItem);

	// 위도, 경도 painting
	latlonItem = new LatLonItem;
	latlonItem->setScreenConvertClass(&vp);
	latlonItem->setVisible(true);			// default
	main->addItem(latlonItem);

	// 맵 상단 원점을 출력한다.
	viewPortItem = new ViewPortItem;
	viewPortItem->setScreenConvertClass(&vp);
	viewPortItem->setAirDraw(air);
	main->addItem(viewPortItem);

	ctr       = NULL;       // CreateTrackReport class
	trackView = NULL;       // TrackViewSelection class
	preview   = NULL;       // TrackPreview class
	option    = NULL;			// TrackReportOption class
	reportOption = new ReportOption;
}

MapCanvas::~MapCanvas()
{
	if (ctr       != NULL) delete ctr;
	if (trackView != NULL) delete trackView;
	if (preview   != NULL) delete preview;
	if (option    != NULL) delete option;
	delete reportOption;
}

void MapCanvas::resizeEvent(QResizeEvent *event)
{
	screenRect = QRect(0, 0, view->width(), view->height());
	vp.setScreenRect(screenRect);
	vp.setScreen00(screenRect.center());

	main->setSceneRect(screenRect);		// 중심점 크기 이동

	view->resize(screenRect.size());
}

void MapCanvas::catchMousePos(const QString& msg)
{
	emit changeMousePos(msg);
}

void MapCanvas::catchLatLonPos(const QString& msg)
{
	//std::cout << "MapCanvas catchLatLonPos called........\n";
	emit changeLatLonPos(msg);
}

void MapCanvas::catchStatusMessage(const QString& msg)
{
	emit changeStatusMessage(msg);
}

/**
 * 사용자가 User Define Map 탭을 선택했을 때 또는 해제 했을 때 호출된다.
 * isUserDefinedMap boolean 변수에 값을 설정하고 이 값에 따라서 User Defined Map과
 * 관계된 데이터를 출력할 수 있도록 한다.
 * mapview.cpp 에서 setObjectPanelVisibleChild 메소드에서 호출된다.
 */
void MapCanvas::setIsUserDefinedMap(bool b, AUserDefinedMap* udm)
{
	isUserDefinedMap = b;
	setUserDefinedMap(udm);
}


void MapCanvas::setUserDefinedMap(AUserDefinedMap* udm)
{
	udMap = udm;

	if (udMap != NULL) udMap->setSymboldir(symboldir);
}

void MapCanvas::open(const QString& fileName)
{
    map->clear();
    // map item clear
	 QList<QGraphicsItem *> items = view->items();

	 for (int i=0; i<items.size(); i++) {
		if (items[i]->type() == 1 || items[i]->type() == 999 || items[i]->type() == 1000
				|| items[i]->type() == 2 || items[i]->type() == 3 || items[i]->type() == 4
				|| items[i]->type() == 5 || items[i]->type() == 998 || items[i]->type() == 1002
				|| items[i]->type() == 1001 || items[i]->type() == 10) {

			delete items[i];
		}
	 }

    map->clearMapconf(); //이전 mapfile 정보 삭제

    map->initMap(*log);
    map->read(fileName);
    setUidListToObjectPanel();
    //map Layer
    QString layerVisible = ConfigParser::getInstance().layerVisible();
    for(int i=0;i<layerVisible.length();i++){
        drawFlag[i] = (layerVisible[i] == QChar('1') ? Visible : Unvisible);
     }

	// LayerList register
	// config에 따라서 layer의 visible을 셋팅
	for (int i=0; i<layerVisible.length(); i++) {
		ALayer* layer = map->findLayer((LayerType)lyrdef.layerType(i));
		if (layer != NULL) {
			layer->setLayerVisible(layerVisible[i] == QChar('1'));

			// Layer가 Symbol dir이면
			if (layer->classType() == ClassSymbol) {
				ASymbolLayerItem* symbollayer = (ASymbolLayerItem *)layer;
				symbollayer->setSymbolDir(symboldir);
			}
			main->addItem(layer);
		}
	}
	map->userLayer()->setLayerVisible(layerVisible[(int)(Layer_User)] == QChar('1'));
#ifndef QT_NO_DEBUG
	log->print("Layer visible setting with config file done..");
#endif

	for (int i=0; i<map->userLayer()->layerCount(); i++) {
		main->addItem(map->userLayer()->getUserList()[i]);	// User map layer
	}

	// User define Map List
	for (int i=0; i<map->udmListCount(); i++) {
		AUserDefinedMap* udm = map->getUDMap(i);
		udm->setVisible(true);
		if (udm != NULL) {
			for (int j=0; j<udm->LayerCount(); j++) {
				AUserDefinedLayer* udlayer = udm->layer(j);
				QString layername = udlayer->getId();

				ALayer* realLayer = udlayer->getLayer();  // map->findLayer(layername);
				realLayer->setAirdraw(air);
				realLayer->setLayerVisible(false);
				// Layer가 Symbol dir이면
				if (realLayer->classType() == ClassSymbol) {
					ASymbolLayerItem* symbollayer = (ASymbolLayerItem *)realLayer;
					symbollayer->setSymbolDir(symboldir);
				}
				if (realLayer == NULL) {
					qDebug() << "NULL...layer...";
				}else {
					//qDebug() << "AUserDEfinedMap add item..." << realLayer->toString();
					main->addItem(realLayer);
				}
			}
		}
	}
	// UserDraw
	ud = new UserDrawItem(this);
	ud->setAirDraw(air);
	main->addItem(ud);

	view->setUserDrawItem(ud);

//    for(int i=0;i<s.length();i++){
//        ALayer* layer = map->findLayer((LayerType)lyrdef.layerType(i));
//        if(layer != NULL){
//             layer->setLayerVisible(s[i] == QChar('1'));
//           }
//     }
//    map->userLayer()->setLayerVisible(s[(int)(Layer_User)] == QChar('1'));

    //leftpanel checkbox 재생성
    leftpanel->setTab(0);
    leftpanel->setMap(getMap());
    leftpanel->displayParentCheckBoxList(getMap());
    leftpanel->setLayerVisible(layerVisible);
    leftpanel->changeLastSelectLayer(Layer_Coast);
    leftpanel->displayDetails(Layer_Coast);

    leftpanel->displayUDMCheckBoxList(getMap()); //UserDefinedMap Checkbox 생성
    //leftpanel->setLayerVisible_UD();

    //TODO: udmListCount
    if(map->udmListCount()==0) leftpanel->setUserDefinedTabEnabled(false);
    else leftpanel->setUserDefinedTabEnabled(true);

     //맵에서읽은 원점으로 바꾼다
    ConfigParser::getInstance().setWonJum(map->defaultWonjum());

    moveWonJum(MV_HOME);
    //refreshPixmap();
    ConfigParser::getInstance().setMapfile(fileName);
    log->print(QString("open map file : %1").arg(fileName));
    catchStatusMessage(QString("read map file from [%1]").arg(fileName));

    //refreshPixmap();
}

/**
 * 맵 에디터에 출력된 맵 화면을 이미지로 저장한다.
 */
void MapCanvas::savePixmap(const QString& fileName)
{
	QGraphicsScene *scene = this->getScene();

	QPainter *pngPainter = new QPainter();
	QPixmap *image = new QPixmap(scene->sceneRect().size().toSize());

	pngPainter->begin(image);
	scene->render(pngPainter);
	pngPainter->end();

	image->save(fileName);
	delete pngPainter;
	delete image;

	catchStatusMessage(QString("map image saved to %1").arg(fileName));

}

/**
 * Map 데이터를 저장한다.
 */
void MapCanvas::save()
{
    QString mapfile = ConfigParser::getInstance().mapFile();
    map->write(mapfile);
    catchStatusMessage(QString("saved map file to [%1]").arg(mapfile));
    log->print(QString("saved  map file : %1").arg(mapfile));
}

/**
 * 데이터베이스에 데이터를 저장하다.
 */
void MapCanvas::saveultodb()
{

    QMessageBox::StandardButton reply;
    QString message;
    message = QString("if you press 'Yes', all user data on Database will be deleted \n"
    "and will be saved with this editor's user layer \n Do you want save?");
    reply = QMessageBox::question(this, tr("Save user layer confirm?"),message,
                                      QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
    }else{
        return;
    }
    if(dbmanager == NULL){
        dbmanager = new DbManager();
        dbmanager->setLog(log);
        QString mapfile = ConfigParser::getInstance().mapFile();
    }
    //sleep(300);
    setCursor(Qt::WaitCursor);
    bool b = dbmanager->setDb(ConfigParser::getInstance().driver(),
           ConfigParser::getInstance().host(),
           ConfigParser::getInstance().db(),
           ConfigParser::getInstance().user(),
           ConfigParser::getInstance().password(),
           ConfigParser::getInstance().port());

    if(b == false){
        QString errmsg = dbmanager->error();
        QMessageBox::critical(this,"Db Connection Error",errmsg);
        unsetCursor();
        return;
    }
    QString dbname = dbmanager->dbName();
    if(map->userLayer()->updateDB(dbname)){
        QMessageBox::information(this,"Db Load OK","OK :saved user layer to db ");
        catchStatusMessage("load user map to db OK");
    }else{
        QString msg = map->userLayer()->lasterror();
        QMessageBox::critical(this,"Db Load Fail",msg);
    }
    unsetCursor();
    return;
}

/**
 * Map 파일을 재저장한다.
 */
void MapCanvas::saveas(const QString& fileName)
{
    map->write(fileName);
    catchStatusMessage(QString("saved map file to [%1]").arg(fileName));
}

void MapCanvas::getulfromdb()
{
    QMessageBox::StandardButton reply;
    QString message;
    message = QString("if you press 'Yes', all user data will be deleted and downloaded from Database \n"
    "and will be loaded as this editor's user layer \n Do you want to download?");
    reply = QMessageBox::question(this, tr("Load user layer from db confirm?"),message,
                                      QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
    }else{
        return;
    }
    if(dbmanager == NULL){
        dbmanager = new DbManager();
        dbmanager->setLog(log);
        QString mapfile = ConfigParser::getInstance().mapFile();

        bool b = dbmanager->setDb(ConfigParser::getInstance().driver(),
               ConfigParser::getInstance().host(),
               ConfigParser::getInstance().db(),
               ConfigParser::getInstance().user(),
               ConfigParser::getInstance().password(),
               ConfigParser::getInstance().port());

        if(b == false){
            QString errmsg = dbmanager->error();
            QMessageBox::critical(this,"Db Error",errmsg);
            return;
        }
    }
    setCursor(Qt::WaitCursor);
    QString dbname = dbmanager->dbName();

    map->userLayer()->clear(); //기존 데이터를 모두 지운다
    if(map->userLayer()->query(dbname)){
    	  catchStatusMessage("get user map from db OK");
        log->print("get user map from db OK");


    }else{
        QMessageBox::critical(this,"Get User Data from Db Fail!",dbmanager->error());
        log->print("error:when retrieve user map data from db, occurred some error ");
    }
    unsetCursor();
    leftpanel->changeLastSelectLayer(Layer_User); //User layer refresh
        map->userLayer()->setLayerVisible(true);
        map->userLayer()->setAllIdVisible(true);
    setUidListToObjectPanel(); //object list를 갱신
        leftpanel->emitmaplayerchanged();
    //refreshPixmap();
    return;

}
/**
 * mapview.cpp에 정의되어 있으며 LeftPanel 클래스에서 changed(QString) 시그널이 발생될 때
 * 호출되는 메소드이다.
 */
void MapCanvas::setLayerVisible(const QString& layerVisible)
{

	//qDebug() << "udmList Count : " << map->udmListCount();
	//qDebug() << "setLayerVisible called..." << layerVisible;


	for (int i=0; i<layerVisible.length(); i++) {
		drawFlag[i] = (layerVisible[i] == QChar('0') ? Unvisible : Visible);
		if (isUserDefinedMap) {
			if (udMap != NULL) {
				if (udMap->LayerCount() > 0) {
					if (drawFlag[i] == 2) {
						qDebug() << lyrdef.fullName((LayerType)lyrdef.layerType(i)) << " visible : " << drawFlag[i];

					}
					udMap->setLayerVisible((LayerType)lyrdef.layerType(i), drawFlag[i]);
				}
			}
		}else {
			map->setLayerVisible((LayerType)lyrdef.layerType(i), drawFlag[i]);
		}
	}
	refreshPixmap();
}

/**
 * mapview.cpp에 정의되어 있으며 LeftPanel 클래스에서 emitlayerdetailclicked 시그널이 발생될 때
 * 호출되는 메소드이다.
 */
void MapCanvas::setDrawIdFlag(int t, const QString& id, LayerVisible layervisible, bool visible)
{
	if (map == NULL) return;
	if (t == GroupLayer_Airport) {
		drawFlag[lyrdef.layerNo(Layer_Ad_Civil)] = layervisible;
		drawFlag[lyrdef.layerNo(Layer_Ad_Mil)]   = layervisible;
		drawFlag[lyrdef.layerNo(Layer_Ad_Joint)] = layervisible;
	}else if(t == GroupLayer_Waypoint) {
		drawFlag[lyrdef.layerNo(Layer_Rep_Fix)]  = layervisible;
		drawFlag[lyrdef.layerNo(Layer_Fix)]      = layervisible;
		drawFlag[lyrdef.layerNo(Layer_T_Fix)]    = layervisible;
	}else if(t == GroupLayer_Navaids) {
		drawFlag[lyrdef.layerNo(Layer_Vortac)]   = layervisible;
		drawFlag[lyrdef.layerNo(Layer_Vordme)]   = layervisible;
		drawFlag[lyrdef.layerNo(Layer_Ndb)]      = layervisible;
	}else {
		drawFlag[lyrdef.layerNo((LayerType)t)]   = layervisible;
	}

	qDebug() << "isUserDefinedMap : " << isUserDefinedMap;
	if (isUserDefinedMap) {

		if (udMap != NULL) {
			qDebug() << "udMap : " << t << id << visible;
			if (udMap->LayerCount() > 0) {
				udMap->setIdVisible(t, id, visible);
			}
		}
	}else {
		map->setIdVisible(t, id, visible);
	}

	refreshPixmap();  // 다시 그린다.
}

/**
 * 화면을 다시 그린다.
 */
void MapCanvas::refreshPixmap()
{
	onPainting = true;
	//airplanetext->setPos(QPoint(airplane->getCurrentPoint().x()-100, airplane->getCurrentPoint().y()));

	view->refreshPixmap();

	//link->trackNodes();
	//map->draw(NULL, NULL);
	onPainting = false;
}
/**
 * 위도 경도 라인을 출력한다.
 */
void MapCanvas::showLatLon(bool b)
{
	latlonItem->setVisible(b);
	latlonItem->update();
}
/**
 * Bearing Circle 라인을 출력한다.
 */
void MapCanvas::showBearingCircle(bool b)
{
	bearingCircleItem->setVisible(b);
	bearingCircleItem->update();
}

/**
 * 맵에 레이블을 표시한다.
 */
void MapCanvas::onoffLayerIdText(bool b)
{
	map->setTextVisible(b);
	refreshPixmap();
}

/**
 * ZoomIn, ZoomOut을 실제 처리한다.
 * mpp를 설정하고 다시 화면을 그린다.
 */
void MapCanvas::changeZoom(double zoom)
{
	vp.setMeterPerPixel(zoom);
	emit setChangeZoom(zoom);
	refreshPixmap();
}

/**
 * 거리 방향 표시(Distance and Direction)을 클릭했을 때 호출되는 Slot
 */
void MapCanvas::onoffDistancBearing(bool b)
{
	if (b) {
		view->mode = DistanceBearing;
		view->setDragMode(QGraphicsView::NoDrag);
	}else {
		view->mode = Normal;
		view->setDragMode(QGraphicsView::RubberBandDrag);
	}
}

/**
 * 오브젝트 판넬에서 사용자가 Select를 선택하면 다시 RubberBandDrag를 활성화 시킨다.
 * 오브젝트를 선택해서 그리기를 수행하려고 하면 RubberBandDrag를 비활성화 시켜서 그릴 수 있도록 한다.
 */
void MapCanvas::setDrawType(DrawType dt)
{
	// 오브젝트 판넬에서 사용자가 Select를 선택하면 다시 RubberBandDrag를 활성화 시킨다.
	// 오브젝트를 선택해서 그리기를 수행하려고 하면 RubberBandDrag를 비활성화 시켜서 그릴 수 있도록 한다.
	if (dt == Select) {
		// QGraphicsView의 drag_mode를 설정한다.
		view->setDragMode(QGraphicsView::RubberBandDrag);
	}else {
		view->setDragMode(QGraphicsView::NoDrag);
	}

	ud->setDrawType(dt);
	ud->initialize();
	ud->setProperty(objectpanel->getProperty());

	if (dt == Text) {
		if (inputusertextDialog == NULL) {
			inputusertextDialog = new InputUserText(this);
			inputusertextDialog->setTitle("Draw Object");
		}
		inputusertextDialog->setText(QString(""));
		int r = inputusertextDialog->exec();

		if (r == 1) {
			QString text1 = inputusertextDialog->getText();
			ud->setText(text1);
		}else {
			setDrawType(Select);
			emit changeObjectDrawTypeButton(Select);
		}
	}else if(dt == Symbol) {
		std::cout << "XpmPickerDialog create symboldir : " << symboldir.toStdString() << "\n";
		log->print(QString("Symbol : %1").arg(symboldir));
		XpmPickerDialog* xpmpickerdialog = new XpmPickerDialog(symboldir);
		int i = xpmpickerdialog->exec();
		if (i > 0) {
			QString fileName = xpmpickerdialog->selectedSymbol();
			ud->setSymbol(QString("%1/%2").arg(symboldir).arg(fileName));
			delete xpmpickerdialog;
		}else {
			setDrawType(Select);
			emit changeObjectDrawTypeButton(Select);
		}
	}else if(dt == Manual) {
		if (manualedit == NULL) {
			manualedit = new ManualCoordEdit;
			manualedit->setWindowModality(Qt::WindowModal);
			connect(manualedit, SIGNAL(manualeditdone()), this, SLOT(manualEditDone()));
			connect(manualedit, SIGNAL(manualeditchanged()), this, SLOT(manualEditChanged()));
			manualedit->move(0, 0);
			if (manualedit->exec()) {
				manualEditDone();
			}else {
				manualEditCanceled();
			}
		}else {
			manualedit->hide();
			manualedit->clearAll();
			manualedit->move(0, 0);
			if (manualedit->exec()) {
				manualEditDone();
			}else {
				manualEditCanceled();
			}
		}
	}
}

/**
 * GenerateView 클래스에서 사용자 그리기 마우스 이벤트 발생 완료 후 호출되는 슬롯 메소드
 * 사용자가 그린 레이어를 실제 맵 레이어에 추가한다.
 */
void MapCanvas::finishedDraw()
{
	log->print("MapCanvas finishedDraw called....");
	// UserDraw의 내용을 사용자 맵에 추가
	QString uid = map->userLayer()->nextIdName();
	QChar dt = ud->drawTypeChar();
	QString attr = ud->layerString();
	QString text = ud->getText();
	QString symbolfilename = QString("");

	log->print(QString("Layer attr : %1").arg(attr));
	AUserLayerId* um = new AUserLayerId;
	um->id = uid;
	um->drawtype = dt;
	um->visible = true;

#ifndef QT_NO_DEBUG
	log->print(QString("symbol finished : type : %1").arg(um->id));
#endif

	if (dt == QChar('T')) {
		um->attr = QString("%1%2").arg(attr).arg(text);
		ud->setText(QString(""));
	}else if(dt == QChar('S')) {
		QFileInfo fi(ud->getSymbol());
		um->attr = QString("%1%2").arg(attr).arg(fi.fileName());
		ud->setSymbol(QString(""));
	}else {
		um->attr = attr;
	}

	if (dt == QChar('L') || dt == QChar('R') || dt == QChar('E') || dt == QChar('T')) {
		AUserbndry* bndry1 = new AUserbndry;
		AUserbndry* bndry2 = new AUserbndry;
		QPoint p1 = ud->getRect().topLeft();
		QPoint p2 = ud->getRect().bottomRight();
		QString s1 = vp.screenToLatLon(p1);
		QString s2 = vp.screenToLatLon(p2);

		bndry1->latlon.lat = s1.left(9);
		bndry1->latlon.lon = s1.right(10);
		bndry1->latlon.p = vp.screenToDecimal(p1.x(), p1.y());
		bndry1->bndry_via = QChar('G');
		um->bndrylist.append(bndry1);

		bndry2->latlon.lat = s2.left(9);
		bndry2->latlon.lon = s2.right(10);
		bndry2->latlon.p = vp.screenToDecimal(p2.x(), p2.y());
		bndry2->bndry_via = QChar('G');
		um->bndrylist.append(bndry2);
	}else if(dt == QChar('C')) {
		AUserbndry* bndry1 = new AUserbndry;
		QPoint centerPoint = ud->getRect().center();
		QString centerLatLon = vp.screenToLatLon(centerPoint);		// center
		// 지름을 넣는다.
		double d_meter_radius = vp.pixelToMeter(ud->getRect().width());
		double d_haeri = UnitChange::meterToHaeri(d_meter_radius);

		bndry1->latlon.lat = centerLatLon.left(9);
		bndry1->latlon.lon = centerLatLon.right(10);
		bndry1->latlon.p = vp.screenToDecimal(centerPoint.x(), centerPoint.y());
		bndry1->arc_center_latlon.lat = centerLatLon.left(9);
		bndry1->arc_center_latlon.lon = centerLatLon.right(10);
		bndry1->arc_center_latlon.p = vp.screenToDecimal(centerPoint.x(), centerPoint.y());
		bndry1->arc_dist = d_haeri;
		bndry1->bndry_via = QChar('C');

		um->bndrylist.append(bndry1);
	}else if(dt == QChar('P') || dt == QChar('G')) {
		QVector<QPoint>* pList = ud->getPointList();

		for (int i=0; i<pList->count(); i++) {
			AUserbndry* bndry = new AUserbndry;
			QPoint p = pList->at(i);
			QString s = vp.screenToLatLon(p);
			bndry->latlon.lat = s.left(9);
			bndry->latlon.lon = s.right(10);
			bndry->latlon.p = vp.screenToDecimal(p.x(), p.y());
			bndry->bndry_via = QChar('G');
			um->bndrylist.append(bndry);
		}
	}else if(dt == QChar('S')) {	// symbol
		QPoint p1 = ud->getRect().center();
		QString s1 = vp.screenToLatLon(p1);

		AUserbndry* bndry1 = new AUserbndry;
		bndry1->latlon.lat = s1.left(9);
		bndry1->latlon.lon = s1.right(10);
		bndry1->latlon.p = vp.screenToDecimal(p1.x(), p1.y());
		bndry1->bndry_via = QChar('S');
		um->bndrylist.append(bndry1);

#ifndef QT_NO_DEBUG
		log->print(QString("symbol finished : %1").arg(bndry1->bndry_via));
#endif
	}else if(dt == QChar('A')) {		// Arc
		QVector<QPoint>* pList = ud->getPointList();
		for (int i=0; i<pList->count(); i++) {
			AUserbndry* bndry = new AUserbndry;
			QPoint p = pList->at(i);
			QString s = vp.screenToLatLon(p);
			bndry->latlon.lat = s.left(9);
			bndry->latlon.lon = s.right(10);
			bndry->latlon.p = vp.screenToDecimal(p.x(), p.y());
			bndry->arc_center_latlon.lat = s.left(9);
			bndry->arc_center_latlon.lon = s.right(10);
			bndry->arc_center_latlon.p = vp.screenToDecimal(p.x(), p.y());
			bndry->bndry_via = QChar('A');
			bndry->arc_bearing = ud->getStartAngle();
			bndry->arc_dist = ud->getEndAngle();
			um->bndrylist.append(bndry);
			if (i == 1) break;
		}
	}

	AUserLayerItem* item = map->userLayer()->append(um);
	item->setSymboldir(symboldir);
	item->setTextVisible(map->getTextVisible());
	main->addItem(item);

	objectpanel->addUid(QString("%1:%2").arg(uid).arg(dt));

	ud->initialize();		// 그린 후 사용자 레이어 맵을 초기화 한다.

	refreshPixmap();

	setDrawType(Select);

	emit changeObjectDrawTypeButton(Select);

}
/**
 * 왼쪽 레이어 판넬에서 사용자가 그린 오브젝트를 reload 한다.
 * 사용자 오브젝트를 그린 후 호출된다.
 * 이 slot은 GenerateView 클래스에서 시그널이 발생되어 호출된다.
 */
void MapCanvas::leftChangedToReload()
{
	// left panel control
	leftpanel->displayDetails(Layer_User);
	leftpanel->detailsCheckAllIdState();
	leftpanel->emitlayerdetailclicked();
}

void MapCanvas::findUidAndSetProperty(const QString& uid)
{
	QString attr = map->userLayer()->attr(uid);
	QString drawtype = map->userLayer()->drawType(uid);
	if (attr.length() > 0) {
		objectpanel->setSelectFlag(false);
		objectpanel->setProperty(QString("LAYER:%1:%2").arg(uid).arg(attr));
		objectpanel->setSelectFlag(true);
		selectedUid = uid;
		objectpanel->setUidListCurrentRow(QString("%1:%2").arg(uid).arg(drawtype));
		refreshPixmap();	// update
	}
}

void MapCanvas::changeUidProperty()
{
	QString uid = objectpanel->getUid();
	if (uid.isEmpty()) return;

	LayerProperty* p = objectpanel->getProperty();
	QString attr = p->layerString();
	map->userLayer()->setAttr(uid, attr);
	refreshPixmap();
}

/**
 * User Layer delete
 * RightPanel에서 사용자가  User Layer 삭제를 클릭했을 때 호출된다.
 * 여러개 체크 박스를 선택했을 경우 ; 으로 구분해서 데이터가 넘어온다.
 */
void MapCanvas::deleteUid(const QString& uid)
{
	QStringList tmp = uid.split(";");
	for (int j=0; j<tmp.count(); j++) {
		map->userLayer()->deleteId(tmp[j]);		// User Layer를 관리하는 클래스에 삭제 아이디를 넘겨주어 삭제한다.

		QList<QGraphicsItem *> items = view->items();

		for (int i=0; i<items.size(); i++) {
			if (items[i]->type() == 998) {
				AUserLayerItem* item = (AUserLayerItem*)items[i];
				if (item->getUserLayer()->id == tmp[j]) {
					//qDebug() << "found delete layer : " << tmp[j];
					delete item;
				}
			}
		}
	}
	refreshPixmap();
}

void MapCanvas::changeUidName(const QString& oldid, const QString& newid)
{
	map->changeUidName(oldid, newid);
	setUidListToObjectPanel();

	leftpanel->displayDetails(Layer_User);
	leftpanel->detailsCheckAllIdState();
	leftpanel->emitlayerdetailclicked();
}

void MapCanvas::manualEditDone()
{
	// map에 추가하기 위해서 AUsermap을 하나 만든다.
	AUserLayerId* drawed_usermap = manualedit->getUsermap();

	if (drawed_usermap->bndrylist.count() < 1) return;

	// layerid를 만들어서 담는다.
	AUserLayerId* layerid = new AUserLayerId;

	layerid->id = drawed_usermap->id;
	layerid->drawtype = drawed_usermap->drawtype;
	layerid->attr = drawed_usermap->attr;
	layerid->msb = drawed_usermap->msb;
	layerid->visible = drawed_usermap->visible;

	for (int i=0; i<drawed_usermap->bndrylist.count(); i++) {
		AUserbndry* bndry = new AUserbndry;
		AUserbndry* drawed_bndry = drawed_usermap->bndrylist[i];

		bndry->bndry_idx = drawed_bndry->bndry_idx;
		bndry->bndry_via = drawed_bndry->bndry_via;
		bndry->latlon = drawed_bndry->latlon;
		bndry->arc_center_latlon = drawed_bndry->arc_center_latlon;
		bndry->arc_bearing = drawed_bndry->arc_bearing;
		bndry->arc_dist = drawed_bndry->arc_dist;
		layerid->bndrylist.append(bndry);
	}

	// 맵에 추가한다.
	AUserLayerItem* item = map->userLayer()->append(layerid);
	main->addItem(item);

	QString uid = layerid->id;
	QChar dt = layerid->drawtype;
	objectpanel->addUid(QString("%1:%2").arg(uid).arg(dt));

	// object type을 Select로 세팅한다.
	setDrawType(Select);
	emit changeObjectDrawTypeButton(Select);

	// Left 판넬을 refresh
	leftpanel->displayDetails(Layer_User);
	leftpanel->detailsCheckAllIdState();
	leftpanel->emitlayerdetailclicked();

	// 화면을 다시 그린다.
	refreshPixmap();
}

void MapCanvas::manualEditChanged()
{
	QVector<CartesianXY>* dataxy;
	dataxy = air->getDataXY();		// 사용자 편집 데이터
	LatLonBound bound;

	if (manualedit == NULL) return;

	LayerProperty* property = objectpanel->getProperty();
	AUserLayerId* layerid = manualedit->getUsermap();

	// data no
	if (layerid->bndrylist.size() < 1) return;
	air->setAUserDrawtype(layerid->drawtype);

	dataxy->clear();
	bound.initialize();
	layerid->id = map->userLayer()->nextIdName();	// 새로운 ID를 부여 받는다.
	layerid->attr = property->layerString();

	for (int j=0; j<layerid->bndrylist.size(); j++) {
		AUserbndry* bndry = layerid->bndrylist[j];
		CartesianXY cxy;
		cxy.bndry_via = bndry->bndry_via;
		QPoint visualpoint = vp.latlonToScreen(bndry->latlon.p);
		cxy.mxy = visualpoint;
		cxy.xyz = vp.cartesian();
		bound.setPosition(cxy.mxy);
		cxy.lat = bndry->latlon.p.x();
		cxy.lon = bndry->latlon.p.y();

		if (bndry->bndry_via == QChar('C')) {
			visualpoint = vp.latlonToScreen(bndry->arc_center_latlon.p);
			cxy.arc_centerxy = visualpoint;
			cxy.arc_dist = bndry->arc_dist;
		}else if(bndry->bndry_via == QChar('L') || bndry->bndry_via == QChar('R')) {
			cxy.arc_centerxy = vp.latlonToScreen(bndry->arc_center_latlon.p);
			cxy.arc_dist = bndry->arc_dist;
			cxy.arc_bearing = bndry->arc_bearing;
			bound.setPosition(cxy.arc_centerxy);
		}else if(bndry->bndry_via == QChar('S')) {
			QString attr = layerid->attr;
			QString symbolFile = manualedit->getSymbol();
			QFileInfo fi(symbolFile);		// 파일명만.
			layerid->attr = QString("%1%2").arg(attr).arg(fi.fileName());
		}
		dataxy->append(cxy);
	}

	if (bound.inRect(vp.srcRect()) && dataxy->size() > 0) {
		refreshPixmap();		// update()
	}
}

/**
 * 취소시 Select로 돌린다.
 */
void MapCanvas::manualEditCanceled()
{
	setDrawType(Select);
	emit changeObjectDrawTypeButton(Select);
	refreshPixmap();
}

void MapCanvas::setUidListToObjectPanel()
{
	if (objectpanel == NULL || map == NULL) return;
	objectpanel->clearUid();
	QStringList list;
	map->userLayer()->fillIdType(list);

	for (int i=0; i<list.count(); i++) {
		objectpanel->addUid(list[i]);
	}
}

void MapCanvas::mapControl(MapControlType mapcontroltype)
{
	switch(mapcontroltype)
	{
	case ZoomIn:
		view->zoomIn();
		break;
	case ZoomOut:
		view->zoomOut();
		break;
	case MoveHome:
		moveWonJum(MV_HOME);
		break;
	case MoveLeft:
		moveWonJum(MV_LEFT);
		break;
	case MoveRight:
		moveWonJum(MV_RIGHT);
		break;
	case MoveUp:
		moveWonJum(MV_UP);
		break;
	case MoveDown:
		moveWonJum(MV_DOWN);
		break;
	default:
		break;
	}
}

/**
 * 메인의 툴바 버튼을 통한 이동을 제어한다.
 * MoveLeft, MoveRight, MoveUp, MoveDown, MoveHome
 */
void MapCanvas::moveWonJum(DIRECT cmd)
{
	QPointF w;
	double mpp = vp.mpp();
	int deltax = vp.srcWidth()/8;
	int deltay = vp.srcHeight()/8;

	double x_do = deltax * mpp / 111195;
	double y_do = deltay * mpp / 111195;

	if (y_do > 10) {
		y_do = 10;
		x_do = 10;
	}
	double d;

	switch(cmd) {
	case MV_LEFT:
		d = vp.greenich() - x_do;
		if (d < 0) d = 360 - fabs(d);
		vp.moveGreenichPoint(d);
		break;
	case MV_RIGHT:
		d = vp.greenich() + x_do;
		d = fmod(d, 360);
		vp.moveGreenichPoint(d);
		break;
	case MV_DOWN:
		d = vp.north() - y_do;
		if (d < 0) d = 360 - fabs(d);
		vp.moveNorthPoint(d);
		break;
	case MV_UP:
		d = vp.north() + y_do;
		d = fmod(d, 360);
		vp.moveNorthPoint(d);
		break;
	case MV_HOME:
	{
		vp.moveNorthPoint(ConfigParser::getInstance().lat());
		vp.moveGreenichPoint(ConfigParser::getInstance().lon());
		double mpp = ConfigParser::getInstance().mpp();
		vp.setMeterPerPixel((int)floor(mpp));
		emit setChangeZoom(vp.mpp());
	}
		break;
	case MV_PGUP:
	case MV_PGDN:
		break;
	}
	refreshPixmap();
}

/**
 * Track Report 를 출력한다.
 * TrackViewSelection 클래스에서 Track Report 버튼 클릭시 호출되는 메소드
 */
void MapCanvas::trackReport(QVector<TrackDataModel> data)
{
	QString sql;
	airplanModel.clear();
	trackData.clear();

	// 기존 Track에 대해서 삭제한다.
	QList<QGraphicsItem *> items = main->items();
	for (int i=0; i<items.size(); i++) {
		if (items[i]->type() == 999 || items[i]->type() == 1000 || items[i]->type() == 1001 || items[i]->type() == 1002) {
			main->removeItem(items[i]);
			delete items[i];
		}
	}
	trackData = data;

	// 비행 데이터가 여러개이면 여러개를 그린다.
	for (int i=0; i<trackData.size(); i++) {

		TrackDataModel model = trackData.at(i);
		model.setLog(log);

		QVector<TrackData> tData = model.getTrackData();
		QVector<AirPlaneModel*> airModel;
		for (int j=0; j<tData.size(); j++) {
			TrackData trData = tData.at(j);

			AirPlaneItem* airplane = new AirPlaneItem;
			airplane->setNumber(j+1);
			airplane->setScreenConvertClass(&vp);
			airplane->setLog(log);
			airplane->setReportOption(reportOption);
			airplane->setTrackData(trData);
			airplane->setSymbol(model.symbol);
			airplane->setLoad();
			airplane->setVisible(true);

			AirPlaneTextItem* airplanetext = new AirPlaneTextItem;
			airplanetext->setNumber(j+1);
			airplanetext->setLog(log);
			airplanetext->setScreenConvertClass(&vp);
			airplanetext->setVisible(false);
			airplanetext->setAirplanePlace(airplane);
			airplanetext->setSSR(model.ssr);
			airplanetext->setCallsign(model.callsign);
			airplanetext->setTrackNo(model.trackNo);
			airplanetext->setAlert(model.alert);
			airplanetext->setColor(model.selectedColor);

			LinkItem* link = new LinkItem(airplane, airplanetext);
			link->setVisible(false);
			link->setLog(log);

			main->addItem(airplane);
			main->addItem(airplanetext);
			main->addItem(link);

			AirPlaneModel* model = new AirPlaneModel;		// track one
			model->setItem1(airplane);
			model->setItem2(airplanetext);
			model->setItem3(link);

			airplanModel.push_back(model);
			airModel.push_back(model);
		}

		model.trackModel = airModel;
		trackData.replace(i, model);
	}

	for (int i=0; i<trackData.size(); i++) {

		TrackDataModel model = trackData.at(i);

		if (!model.disTrack.isEmpty() && model.disTrack.length() > 0) {

			for (int j=0; j<trackData.size(); j++) {
				if (i == j) continue;
				TrackDataModel mo = trackData.at(j);

				if (model.disTrack == mo.trackNo) {
					if (model.trackModel.size() > mo.trackModel.size()) {
						for (int k=0; k<mo.trackModel.size(); k++) {
							AirPlaneModel *model1 = model.trackModel.at(k);
							AirPlaneModel *model2 = mo.trackModel.at(k);
							DistanceLinkItem* dist = new DistanceLinkItem(model1->getItem1(), model2->getItem1());
							dist->setVisible(true);
							dist->setLog(log);
							main->addItem(dist);
						}
					}else {
						for (int k=0; k<model.trackModel.size(); k++) {
							AirPlaneModel *model1 = model.trackModel.at(k);
							AirPlaneModel *model2 = mo.trackModel.at(k);
							DistanceLinkItem* dist = new DistanceLinkItem(model1->getItem1(), model2->getItem1());
							dist->setVisible(true);
							dist->setLog(log);
							main->addItem(dist);
						}
					}
				}
			}


		}
	}


	// 기준점을 마지막 데이터를 기준으로 한다.
	if (airplanModel.size() > 0) {

		for (int i=0; i<airplanModel.size(); i++) {
			AirPlaneModel* ap = airplanModel.at(i);
			TrackData data = ap->getItem1()->getTrackData();
			APoint latlon;
			QString lat = _ca.LatDecimalToDMS(data.lat);
			QString lon = _ca.LonDecimalToDMS(data.lon);

			latlon.lat = lat;
			latlon.lon = lon;
			latlon.p = QPointF(data.lat, data.lon);
			if (data.lat == 0) continue;
		//qDebug() << data.lat;
		//qDebug() << data.lon;

			// 원점 이동
			QPointF p = latlon.p;   // vp->screenToDecimal(event->pos());
			vp.moveNorthPoint(p.x());
			vp.moveGreenichPoint(p.y());

			// mpp increase
			vp.setMeterPerPixel(50);

			refreshPixmap();
			break;
		}
	}
}

/**
 * Data block 표시 여부를 설정한다.
 */
void MapCanvas::dataBlockPrint(int view)
{
	bool b;

	if (view == 0) b = false;
	else b = true;
	QList<QGraphicsItem *> items = main->items();
	for (int i=0; i<items.size(); i++) {
		//qDebug() << items[i]->type();
		if (items[i]->type() == 1000) {
			AirPlaneTextItem* item = (AirPlaneTextItem*)items[i];
			item->setVisible(b);
		}else if(items[i]->type() == 1001 ) {
			LinkItem* item = (LinkItem*)items[i];
			item->setVisible(b);
		}
	}

	refreshPixmap();
}

/**
 * Clear Track Data
 */
void MapCanvas::clearTrackData()
{
	QList<QGraphicsItem *> items = main->items();
	for (int i=0; i<items.size(); i++) {
		if (items[i]->type() == 999 || items[i]->type() == 1000 || items[i]->type() == 1001 || items[i]->type() == 1002) {
			main->removeItem(items[i]);
			delete items[i];
		}
	}

	airplanModel.clear();

	if (trackView != NULL) {
		delete trackView;
		trackView = NULL;
	}

	refreshPixmap();

}

/**
 * Track Report Create 폼에서 넘어온 데이터를 보관한다.
 * from, to 날짜 데이터를 받는다.
 */
void MapCanvas::setCreateTrackReport(QString& from, QString& to)
{
	qDebug() << from << to;

	fromDt = from;
	toDt   = to;

}

/**
 * Thread 에서 값이 넘어오기 때문에 처리한 값에 대한 1만 계속적으로
 * 보낼 수 있도록 한다. 따라서 넘어온 1값을 가지고 현재의 값과 더해서 프로그래스를 증가시킨다.
 */
void MapCanvas::setProgressValue(int value)
{
	//int num = progress->value();

	//qDebug() << value;
	progress->setValue(value);

}

/**
 * Track Report option 변경으로 인해서 맵을 다시 그린다.
 */
void MapCanvas::setReportOption()
{
	refreshPixmap();
}
/**
 * Track Report 데이터를 생성한다.
 * DRS 시스템으로 부터 로그 데이터를 가져올 수 있는 폼을 보여준다.
 */
void MapCanvas::trackCreate()
{
	if (ctr == NULL) {
		// Track report
		ctr = new CreateTrackReport(this);
		ctr->setModal(true);
		connect(ctr, SIGNAL(setCreateTrackReport(QString&, QString&)), this, SLOT(setCreateTrackReport(QString&, QString&)));
	}
	int result = ctr->exec();

	if (result == QDialog::Accepted) {
		// DRS 데이터베이스에 접속해서 해당 데이터를 가져온다.
		if (fromDt.isEmpty() && toDt.isEmpty()) {
			QMessageBox::warning(this, tr("Create Track Report Error Message"), tr("Select the track creation date."));
			return;
		}
		qDebug() << "trackCreate : " << fromDt << toDt;

		CreateTrackProcess *proc = new CreateTrackProcess;

		proc->setLog(this->getLog());
		proc->setDate(fromDt, toDt);
		if (!proc->dbSMSDOpen()) {
			QMessageBox::warning(this, tr("Create Track Report Error Message"), tr("Cannot open database(smsd)"));
			delete proc;
			return;
		}

		int numData = proc->getCount();		// 총 개수를 조회한다.

		qDebug() << "totalCount : " << numData;

		progress = new QProgressDialog("Track report is reading...", "Abort Read", 0, numData, this);
		progress->setWindowModality(Qt::WindowModal);
		progress->resize(QSize(600, 200));
		connect(proc, SIGNAL(valueChanged(int)), this, SLOT(setProgressValue(int)), Qt::AutoConnection);

		// Create a QFutureWatcher and connect signals and slots.
		QFutureWatcher<bool> futureWatcher;
		QObject::connect(&futureWatcher, SIGNAL(finished()), progress,       SLOT(reset()));
		QObject::connect(progress,       SIGNAL(canceled()), proc,           SLOT(threadStop()));
		QObject::connect(progress,       SIGNAL(canceled()), &futureWatcher, SLOT(cancel()));
		//QObject::connect(progress,       SIGNAL(finished()),    &futureWatcher, SLOT(finished()));
		//QObject::connect(&futureWatcher, SIGNAL(progressRangeChanged(int,int)), progress, SLOT(setRange(int,int)));
		//QObject::connect(&futureWatcher, SIGNAL(progressValueChanged(int)), progress, SLOT(setValue(int)));

		// Start the computation.
		QFuture<bool> future = QtConcurrent::run(proc, &CreateTrackProcess::trackProcess);

		futureWatcher.setFuture(future);
		// Display the dialog and start the event loop.
		progress->exec();
		futureWatcher.waitForFinished();

		bool num = false;

		if (futureWatcher.future().isCanceled()) {
			qDebug() << "futureWather canceled....";
		}else {
			 num = future.result();   // proc.trackProcess();
		}
		delete proc;
		progress->setValue(numData);
		delete progress;

		if (!num) {
			QMessageBox::warning(this, tr("Track report create error"), tr("Track report creation occured error."));
			trackCreate();
			return;
		}else {

			qDebug() << "trackViewSelection call...........";
			if (trackView == NULL) {
				trackView = new TrackViewSelection;
				trackView->setLog(this->getLog());
				trackView->setReportOption(reportOption);
				trackView->setWindowFlags(Qt::WindowStaysOnTopHint);
				//trackView->setAttribute(Qt::WA_TranslucentBackground);
				trackView->show();
				trackView->trackDataSearch();

				connect(trackView, SIGNAL(trackReport(QVector<TrackDataModel>)), this, SLOT(trackReport(QVector<TrackDataModel>)));
				connect(trackView, SIGNAL(dataBlockPrint(int)), this, SLOT(dataBlockPrint(int)));
				connect(trackView, SIGNAL(clearTrackData()),    this, SLOT(clearTrackData()));
				//connect(trackView, SIGNAL(reportExcel()),       this, SLOT(reportExcel()));
			}else {
				trackView->show();
				trackView->trackDataSearch();
			}
		}
	}
}

/**
 * save Track Report data
 * Track Report data saved XML data.
 */
void MapCanvas::trackSave()
{
	if (airplanModel.size() == 0) {
		QMessageBox::warning(this, "Track Report save error", "Track Report data not exists.");
		return;
	}
	QString fileName = QFileDialog::getSaveFileName(this, tr("Save Track Report File"),
	                            NULL,
	                            tr("XML (*.xml)"));

	if (fileName.isEmpty()) return;

	QString ext = fileName.right(3);

	if (ext.toLower() != "xml") {
		fileName = fileName + ".xml";
	}

	// QIODevice open
	QFile file(fileName);
	if (!file.open(QFile::WriteOnly | QFile::Text)) {
	     QMessageBox::warning(this, tr("Track Report save error"),
	                  tr("Cannot write file %1:\n%2.")
	                  .arg(fileName)
	                  .arg(file.errorString()));
	     return;
	}


	QXmlStreamWriter xml;
	xml.setAutoFormatting(true);

	xml.setDevice(&file);

	xml.writeStartDocument();
	xml.writeStartElement("TrackConf");

	////////////////////////////////////////////////////////////////////////////////////////////////
	// Data Block Info
	xml.writeStartElement("DataBlockInfo");

	xml.writeTextElement("TrackNum",   reportOption->trackNumberText());
	xml.writeTextElement("AssignedFL", reportOption->assignedFLText());
	xml.writeTextElement("Warning",    reportOption->warningText());
	xml.writeTextElement("SSR",        reportOption->ssrText());
	xml.writeTextElement("Callsign",   reportOption->callsingText());
	xml.writeTextElement("ModeC",      reportOption->modecText());
	xml.writeTextElement("Velocity",   reportOption->velocityText());
	xml.writeTextElement("BlockCount", QString("%1").arg(reportOption->getBlockCount()));
	xml.writeEndElement();
	/////////////////////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////////////////////
	// Track Info
	xml.writeStartElement("TrackList");

	for (int i=0; i<trackData.size(); i++) {
		TrackDataModel model = trackData.at(i);

		xml.writeStartElement("TrackInfo");

		xml.writeTextElement("SSR",      model.ssr);
		xml.writeTextElement("Callsign", model.callsign);
		xml.writeTextElement("TrackNo",  model.trackNo);
		xml.writeTextElement("Alert",    model.alert);
		xml.writeTextElement("Symbol",   model.symbol);
		xml.writeTextElement("Color",    model.colorName);

		for (int j=0; j<model.dataModel.size(); j++) {
			TrackData track = model.dataModel.at(j);

			xml.writeStartElement("Track");

			xml.writeTextElement("OCCUR_DT", track.occur_dt);
			xml.writeTextElement("LAT",      QString("%1").arg(track.lat));
			xml.writeTextElement("LON",      QString("%1").arg(track.lon));
			xml.writeTextElement("SPD",      QString("%1").arg(track.spd));
			xml.writeTextElement("PREV_SPD", QString("%1").arg(track.prev_spd));
			xml.writeTextElement("HEADING",  QString("%1").arg(track.heading));
			xml.writeTextElement("MLT_ALT",  QString("%1").arg(track.mlt_alt));
			xml.writeTextElement("ALT",      QString("%1").arg(track.alt));
			xml.writeTextElement("PREV_ALT", QString("%1").arg(track.prev_alt));
			xml.writeTextElement("QNH",      track.qnh);
			xml.writeTextElement("CLIMB",    QString("%1").arg(track.climb));
			xml.writeTextElement("SPI",      track.spi);
			xml.writeTextElement("MRH",      track.mrh);
			xml.writeTextElement("CNF",      track.cnf);
			xml.writeTextElement("SIM",      track.sim);
			xml.writeTextElement("TSE",      track.tse);
			xml.writeTextElement("FPC",      track.fpc);
			xml.writeTextElement("CST",      track.cst);
			xml.writeTextElement("PSR",      track.psr);
			xml.writeTextElement("SSR",      track.ssr);
			xml.writeTextElement("MDS",      track.mds);
			xml.writeTextElement("ADS",      track.ads);
			//xml.writeTextElement("FL_TYPE",  track.fl_type);
			xml.writeTextElement("FLT_RULE", track.flt_rule);
			xml.writeTextElement("RVSM",     track.rvsm);
			//xml.writeTextElement("HPR",      track.hpr);
			xml.writeTextElement("ACTP",     track.actp);
			xml.writeTextElement("WT_TYPE",  track.wt_type);
			xml.writeTextElement("DEP_AD",   track.dep_ad);
			xml.writeTextElement("ARR_AD",   track.arr_ad);
			xml.writeTextElement("RWAY_NO",  track.rway_no);
			xml.writeTextElement("CFL",      QString("%1").arg(track.cfl));
			xml.writeTextElement("CENTER_ID",track.center_id);
			xml.writeTextElement("POS",      track.pos);
			xml.writeTextElement("TYPE",     QString("%1").arg(track.type));
			xml.writeTextElement("ALERT",    QString("%1").arg(track.alert));
			xml.writeEndElement();
		}
		xml.writeEndElement();
	}
	xml.writeEndElement();
	///////////////////////////////////////////////////////////////////////////////////////////

	xml.writeEndElement();
	xml.writeEndDocument();

	QMessageBox::information(this, tr("Track Report"), tr("Track Report data is saved."));
}

/**
 * open XML track data, display Track View Selection.
 */
void MapCanvas::trackOpen()
{
	QString fileName;

	fileName = QFileDialog::getOpenFileName(this,
	     tr("Track Report Data"), NULL, tr("XML Files (*.xml)"));

	if (!fileName.isEmpty()) {
		// QIODevice open
		QFile file(fileName);
		if (!file.open(QFile::ReadOnly | QFile::Text)) {
		     QMessageBox::warning(this, tr("Track Report read error"),
		                  tr("Cannot read file %1:\n%2.")
		                  .arg(fileName)
		                  .arg(file.errorString()));
		     return;
		}

		QXmlStreamReader xml;
		xml.setDevice(&file);

		if (xml.readNextStartElement()) {
			if (xml.name() != "TrackConf") {
				QMessageBox::critical(this, tr("Track Report read error"), tr("The file is not Track Report XML data"));
				return;
			}else {
				if (trackView == NULL) {
					trackView = new TrackViewSelection;
					trackView->setWindowFlags(Qt::WindowStaysOnTopHint);
					trackView->setLog(this->getLog());
					trackView->setReportOption(reportOption);
					trackView->trackXmlRead(&xml);
					trackView->show();
					connect(trackView, SIGNAL(trackReport(QVector<TrackDataModel>)), this, SLOT(trackReport(QVector<TrackDataModel>)));
					connect(trackView, SIGNAL(dataBlockPrint(int)), this, SLOT(dataBlockPrint(int)));
					connect(trackView, SIGNAL(clearTrackData()),    this, SLOT(clearTrackData()));
				}else {

					trackView->trackXmlRead(&xml);
					trackView->show();
				}
			}
		}else {
			QMessageBox::critical(this, tr("Track Report read error"), tr("The file is not Track Report XML data"));
		}
	}
}

/**
 * Display the track report option
 * If the track report option is changed, map repaint.
 */
void MapCanvas::trackOption()
{
	if (option == NULL) {
		option = new TrackReportOption;
		option->show();
		option->refreshList(reportOption);

		connect(option, SIGNAL(setReportOption()), this, SLOT(setReportOption()));
	}else {
		option->show();
		option->refreshList(reportOption);
	}
}

/**
 * 항적 추적도 관련된 테이블의 모든 데이터를 삭제한다.
 */
void MapCanvas::trackClTable()
{
	if (trackView != NULL) {
		if (QMessageBox::Cancel == QMessageBox::question(this, tr("Confirm Dialog"), tr("Do the Track view selection close?"),
						QMessageBox::Ok | QMessageBox::Cancel)) {
				return;
		}else {
			trackView->close();
			delete trackView;

			trackView = NULL;
		}
	}

	if (dbmanager == NULL) {
		dbmanager = new DbManager();
		dbmanager->setLog(log);
	}

	bool b = dbmanager->setDb(ConfigParser::getInstance().driver(),
			ConfigParser::getInstance().host(),
			ConfigParser::getInstance().db(),
			ConfigParser::getInstance().user(),
			ConfigParser::getInstance().password(),
			ConfigParser::getInstance().port());
	if (!b) {
		QString errmsg = dbmanager->error();
		QMessageBox::critical(this, "DB Connection Error", errmsg);
		qDebug() << errmsg;
		return;
	}

	QSqlQuery* query = new QSqlQuery(QSqlDatabase::database(dbmanager->dbName()));

	QString sql;
	sql  = " DELETE FROM TB_TRK  ";

	query->prepare(sql);
	query->exec();

	if (query->lastError().type() != QSqlError::NoError) {
		delete query;
		QMessageBox::critical(this, "SQL Error", query->lastError().text());
		return;
	}
	query->finish();

	sql  = " DELETE FROM TB_MINIPLN  ";

	query->prepare(sql);
	query->exec();

	if (query->lastError().type() != QSqlError::NoError) {
		delete query;
		QMessageBox::critical(this, "SQL Error", query->lastError().text());
		return;
	}
	query->finish();
	delete query;

	clearTrackData();

	QMessageBox::information(this, "Track Report Data", "Track Report Data is deleted.");
}

/**
 * Map Editor Panel에 표시되어 있는 항적을 삭제한다.
 */
void MapCanvas::trackClPanel()
{
	// clearTrackData();
	QList<QGraphicsItem *> items = main->items();
	for (int i=0; i<items.size(); i++) {
		if (items[i]->type() == 999 || items[i]->type() == 1000 || items[i]->type() == 1001 || items[i]->type() == 1002) {
			main->removeItem(items[i]);
			delete items[i];
		}
	}

	airplanModel.clear();

	refreshPixmap();
}

/**
 * Track Print - Preview
 */
void MapCanvas::trackPrint()
{

	if (trackData.size() == 0) return;
//	GenerateView   *view = new GenerateView(this);
//	view->setScene(main->getScene());
//	view->setLog(main->getLog());
//	view->setScreenConvertClass(main->getConvert());

//	QGraphicsView *view = new QGraphicsView(this);
	QGraphicsScene *scene = this->getScene();

//	scene->addText("GraphicsView rotated clockwise");
//	view->setScene(scene);

//	layout->addWidget(view);
//
//	test->setLayout(layout);
//
//	test->showMaximized();
	//test->resize(800, 800);



//	 QPrinter printer(QPrinter::HighResolution);
//	 printer.setPageSize(QPrinter::A4);
//
//	 QPrintDialog printDialog(&printer, this);
//
//	 if (printDialog.exec()) {
//		 QPainter painter(&printer);
//
//		 // print, fitting the viewport contents into a full page
//		 view->render(&painter);
//	 }


	 QString fileName("test.jpg");
	 QPainter *pngPainter = new QPainter();
	 //QImage *image = new QImage(scene->sceneRect().size().toSize(), QImage::Format_ARGB32);
	 QPixmap *image = new QPixmap(scene->sceneRect().size().toSize());

	 // Resolution of the image is 600 dpi by default
	 //image->setDotsPerMeterX(600*254);
	 //image->setDotsPerMeterY(600*254);

	 pngPainter->begin(image);
	 scene->render(pngPainter);
	 pngPainter->end();

	 //image->save(fileName);
	 delete pngPainter;
	 //delete image;

	 if (preview == NULL) {
		 preview = new TrackPreview();
		 preview->setSceneSize(this->getScene()->sceneRect());
	 }
	 //QVector<AirPlaneModel*> data = this->getTrackData();

	 preview->setScene(trackData, image);

	 preview->resize(QSize(this->getScene()->sceneRect().size().width()+274,
			 this->getScene()->sceneRect().size().height()+74
	 ));

	 preview->show();

}

/**
 * 데이터베이스로 데이터를 조회해서 map data 파일을 생성한다.
 */
void MapCanvas::makeMapFromDb()
{
    if(dbmanager == NULL){
        dbmanager = new DbManager();
        dbmanager->setLog(log);
        QString mapfile = ConfigParser::getInstance().mapFile();

        bool b = dbmanager->setDb(ConfigParser::getInstance().driver(),
               ConfigParser::getInstance().host(),
               ConfigParser::getInstance().db(),
               ConfigParser::getInstance().user(),
               ConfigParser::getInstance().password(),
               ConfigParser::getInstance().port());

        if(b == false){
            QString errmsg = dbmanager->error();
            QMessageBox::critical(this,"Db Error",errmsg);
            return;
        }
    }

	QString mapFileName = QString("%1/ams.map").arg(ConfigParser::getInstance().envMapDir());
	map->getDataFromDb(QSqlDatabase::database("amsdb"));
	map->write(mapFileName);

	QMessageBox::information(this, tr("Success Message"), tr("done. plz,check %1").arg(mapFileName));
}
