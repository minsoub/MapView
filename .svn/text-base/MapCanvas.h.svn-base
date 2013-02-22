/*
 * MapCanvas.h
 *
 *  Created on: 2012. 1. 16.
 *      Author: HIST002
 */

#ifndef MAPCANVAS_H_
#define MAPCANVAS_H_

#include <QtGui>
#include <QGraphicsScene>
//#include "../lib/MapConvertFunc.h"
#include "GenerateView.h"
#include "item/LatLonItem.h"
#include "item/BearingCircleItem.h"

#include "item/ALinesLayerItem.h"
#include "item/AreaLayerItem.h"
#include "item/ASymbolLayerItem.h"
#include "item/AUserLayerItem.h"
#include "item/AUserLayerItemMng.h"
#include "item/ViewPortItem.h"
#include "item/UserDrawItem.h"
#include "item/AirPlaneItem.h"
#include "item/AirPlaneTextItem.h"
#include "item/LinkItem.h"
#include "item/DistanceLinkItem.h"

#include "item/DirBearing.h"
//#include "lib_layer/ALayer.h"

//#include "lib/CenterCoord.h"
//#include "lib/LatLonConvert.h"
//#include "lib/NorthGreenichPoint.h"
#include "lib/MapUtil.h"
#include "lib/ManualCoordEdit.h"
#include "lib/XpmPickerDialog.h"
#include "lib/AirPlaneModel.h"
#include "lib/DbManager.h"
#include "lib/GlobalColor.h"
#include "AMap.h"

#include "leftlayout/LeftPanel.h"
#include "rightlayout/RightPanel.h"

#include "trackrpt/TrackData.h"
#include "trackrpt/createtrackreport.h"
#include "trackrpt/CreateTrackProcess.h"
#include "trackrpt/TrackViewSelection.h"
#include "trackrpt/TrackDataModel.h"
#include "trackrpt/TrackPreview.h"
#include "trackrpt/TrackReportOption.h"
#include "trackrpt/ReportOption.h"

//#include "GeoData.h"


class MapCanvas : public QWidget {
	Q_OBJECT
public:
	enum MapControlType { ZoomIn, ZoomOut, MoveHome, MoveLeft, MoveRight, MoveUp, MoveDown };
	enum DIRECT { MV_LEFT, MV_RIGHT, MV_DOWN, MV_UP, MV_HOME, MV_PGUP, MV_PGDN };
	enum ModeType { Normal, DistanceBearing };

	MapCanvas(QWidget *parent=0);
	~MapCanvas();
	AMap* getMap() { return map; }
	void setObjectPanel(RightPanel* p) { objectpanel = p; setUidListToObjectPanel(); }
	void setLeftPanel(LeftPanel* p) { leftpanel = p; }
	void setIsUserDefinedMap(bool b, AUserDefinedMap* udm);
	void setUserDefinedMap(AUserDefinedMap* udm);

	double       meterPerPixel;		             // meter per 1 pixel
	QPointF      wonJum;
	CenterCoord  centerCoord;

   void write(const QString& fileName);
   void print(QTextStream& out);
   void clear();
   void mapControl(MapControlType mapcontroltype);
   void moveWonJum(DIRECT cmd);
   void open(const QString& fileName);
   void savePixmap(const QString& fileName);
   UserDrawItem* ud;
   Log424* getLog() { return log; }
   QGraphicsScene* getScene() { return main; }
   LatLonConvert* getConvert() { return &vp; };
   QVector<AirPlaneModel*> getTrackData() { return airplanModel; }
protected:
	void resizeEvent(QResizeEvent *event);
private:
	enum { Margin = 50 };
	bool onPainting;
	LayerDefine lyrdef;

	QGraphicsScene *main;
    GenerateView   *view;
    //CoastItem      *coast;			        // Coast map data
    LatLonItem     *latlonItem;             // 위도/ 경도 data Item
    BearingCircleItem *bearingCircleItem;   // BearingCircle Item
    ViewPortItem*      viewPortItem;		  // 맵상단 원점 출력 Item

    QVector<AirPlaneModel*> airplanModel;	  // 비행 데이터를 저장하는 모델1
    QVector<TrackDataModel> trackData;
    //AirPlaneItem*  airplane;				     // 비행 데이터
    //AirPlaneTextItem* airplanetext;         // 비행 데이터 테스트
    //LinkItem*         link;                 // 비행 데이터와 비행 데이터 테스트 연결

    int	airIndex;
    DirBearing*    distbear;                // 사용자 거리/방위각 Item

    Cartesian      cartesian;
    QRect          screenRect;
    LatLonConvert  vp;
    NorthGreenichPoint *northGreenich;

    AirDraw* air;
	 Log424*  log;
	 AMap*    map;
	 AUserDefinedMap* udMap;
	 AMsb     msb;							// struct
	 AMapconf mapconf;						// Map configuration info
    bool textvisible;
    QString symboldir;
    CalcAir  _ca;
    LeftPanel* leftpanel;
    RightPanel* objectpanel;


    InputUserText* inputusertextDialog;

    QString selectedUid;

    ManualCoordEdit* manualedit;
    LayerVisible drawFlag[MaxLayerCount];
    DbManager* dbmanager;

	CreateTrackReport  *ctr;
	TrackViewSelection *trackView;
	TrackPreview       *preview;
	QProgressDialog    *progress;
	TrackReportOption  *option;
	ReportOption       *reportOption;
	QString     fromDt;				// Track Create from date
	QString     toDt;				   // Track Creete to date

    bool isUserDefinedMap;
    bool isBearingCircle;
    bool isLatlonItem;

    void refreshPixmap();
    void setUidListToObjectPanel();
private slots:
	void catchMousePos(const QString& msg);
	void catchLatLonPos(const QString& msg);
	void catchStatusMessage(const QString& msg);
	// GenerateView에서 사용자 Object를 그린 후 왼쪽 판넬에 적용시키기 위해서 호출되는 메소드
	void leftChangedToReload();
	void trackCreate();
	void trackSave();
	void trackOpen();
	void trackOption();
	void trackClTable();
	void trackClPanel();
	void trackPrint();
	void setCreateTrackReport(QString& from, QString& to);
	void setReportOption();
public slots:
	// mapview.cpp에 정의되어 있으며 LeftPanel 클래스에서 changed(QString) 시그널이 발생될 때
	// 호출되는 메소드이다.
	void setLayerVisible(const QString& layerVisible);
	void setDrawIdFlag(int t, const QString& id, LayerVisible layervisible, bool visible);

	// Mapview 클래스에서 발생한 Signal/Slot
	void changeZoom(double zoom);
	void setDrawType(DrawType dt);
	void finishedDraw();
	void findUidAndSetProperty(const QString& uid);
	void changeUidProperty();
	void deleteUid(const QString& uid);
	void changeUidName(const QString& oldid, const QString& newid);


	void showLatLon(bool b);
	void showBearingCircle(bool b);
	void onoffLayerIdText(bool b);
	void onoffDistancBearing(bool b);
	// ManualEdit
	void manualEditDone();
	void manualEditChanged();
	void manualEditCanceled();

	void trackReport(QVector<TrackDataModel>);		// Track Report print
	void dataBlockPrint(int);								// Data Block print/not print
	void clearTrackData();									// Clear Track Report
	void setProgressValue(int);

   void save();
   void saveultodb();
   void saveas(const QString& fileName);
   void getulfromdb();
   void makeMapFromDb();
signals:
   void changeObjectDrawTypeButton(DrawType dt);
	void changeMousePos(const QString& msg);
	void changeLatLonPos(const QString& msg);
	void changeStatusMessage(const QString& msg);
	void setChangeZoom(double zoom);			// MapCanvas에서 발생한 시그널을 RightPanel에 보낸다. - MapView에 정의
};

#endif /* MAPCANVAS_H_ */
