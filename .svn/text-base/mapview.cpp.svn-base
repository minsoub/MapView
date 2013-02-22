#include <iostream>
#include "mapview.h"
#include "./lib/ConfigParser.h"


MapView::MapView(QWidget *parent)
    : QMainWindow(parent)
{
	// MainWindow create


	leftPanel  = new LeftPanel(this);
	rightPanel = new RightPanel(this);

	leftDockWidget = new QDockWidget(tr("Map Layer"));
	leftDockWidget->setWidget(leftPanel);
	leftDockWidget->setAllowedAreas(Qt::LeftDockWidgetArea);
	leftDockWidget->setMinimumWidth(240);

	rightDockWidget = new QDockWidget(tr("Object Panel"));
	rightDockWidget->setWidget(rightPanel);
	rightDockWidget->setAllowedAreas(Qt::RightDockWidgetArea);
	rightDockWidget->setMinimumWidth(240);

	addDockWidget(Qt::LeftDockWidgetArea,  leftDockWidget);
	addDockWidget(Qt::RightDockWidgetArea, rightDockWidget);

	main = new MapCanvas();

	//std::cout << "m width : " << width() << ", m height : " << height() << "\n";
	//main->resize(width()-leftDockWidget->width()-rightDockWidget->width(), height());
	setCentralWidget(main);

	// left panel define
	QString visible = ConfigParser::getInstance().layerVisible();
	leftPanel->setMap(main->getMap());
	leftPanel->displayParentCheckBoxList(main->getMap());		// 상단 체크박스 생성
	leftPanel->setLayerVisible(visible);
	leftPanel->displayDetails(Layer_Coast);
	connect(leftPanel,  SIGNAL(signalTabChanged(int)), this, SLOT(setObjectPanelVisibleChild(int)));  // Tab 선택 변경
	connect(leftPanel,  SIGNAL(signalUDMapVisibleChanged_UD()), this, SLOT(setUserDefinedMap()));
	leftPanel->displayUDMCheckBoxList(main->getMap());			// UserDefineMap checkbox 생성

	connect(leftPanel, SIGNAL(changed(QString)), main, SLOT(setLayerVisible(QString)));
	connect(leftPanel, SIGNAL(emitlayerdetailclicked(int, QString, LayerVisible, bool)), main,
			SLOT(setDrawIdFlag(int, QString, LayerVisible, bool)));
	connect(leftPanel, SIGNAL(emitlayerdetailclicked_UD(int, QString, LayerVisible, bool)),
			main, SLOT(setDrawIdFlag(int, QString, LayerVisible, bool)));

	// Object 판넬(RightPanel)에서 그리기 종류가 선택되었을 때의 Signal/Slot
	connect(rightPanel, SIGNAL(changedDrawtype(DrawType)), main, SLOT(setDrawType(DrawType)));
	connect(rightPanel, SIGNAL(changedSelectedUid(QString)), main, SLOT(findUidAndSetProperty(QString)));
	connect(rightPanel, SIGNAL(changedLayerProperty()),      main, SLOT(changeUidProperty()));
	connect(rightPanel, SIGNAL(deletedUid(QString)),         main, SLOT(deleteUid(QString)));
	connect(rightPanel, SIGNAL(changedUidName(QString, QString)), main, SLOT(changeUidName(QString, QString)));
	connect(rightPanel, SIGNAL(changeZoom(double)),    main,   SLOT(changeZoom(double)));
	connect(main,       SIGNAL(setChangeZoom(double)), rightPanel, SLOT(setChangeZoom(double)));
	connect(main,       SIGNAL(changeObjectDrawTypeButton(DrawType)), rightPanel, SLOT(setDown(DrawType)));

	main->setFocusPolicy(Qt::StrongFocus);
	rightPanel->setChangeZoom(ConfigParser::getInstance().mpp());

	// 역ㄱ끼
	main->setObjectPanel(rightPanel);
	main->setLeftPanel(leftPanel);

	// create action
	createActions();

	// create menu
	createMenus();

	// create toolbars
	createToolBars();

	// create statusbar
	createStatusBar();

	// title set
	setWindowTitle(tr("Map Editor - SMEU"));

	// window icon set

	// signal / slots

	// QDockWidget의 floting 변화가 있을 때 MapView의 크기를 resize 한다.
	connect(main, SIGNAL(changeMousePos(QString)),       this, SLOT(changeMousePos(QString)));
	connect(main, SIGNAL(changeLatLonPos(QString)),      this, SLOT(changeLatLonPos(QString)));
	connect(main, SIGNAL(changeStatusMessage(QString)),  this, SLOT(changeStatusMessage(QString)));

}

MapView::~MapView()
{

}

void MapView::closeEvent(QCloseEvent *event)
{
	event->accept();
}


void MapView::createStatusBar()
{
	mousePosLabel = new QLabel("W9999999");
	mousePosLabel->setAlignment(Qt::AlignCenter);
	mousePosLabel->setMinimumSize(mousePosLabel->sizeHint());

	mapPosLabel = new QLabel("N1239999xE1239999");
	mapPosLabel->setAlignment(Qt::AlignCenter);
	mapPosLabel->setMinimumSize(mapPosLabel->sizeHint());

	msgLabel = new QLabel();
	msgLabel->setAlignment(Qt::AlignLeft);
	msgLabel->setIndent(3);

	statusBar()->addWidget(mousePosLabel);
	statusBar()->addWidget(mapPosLabel);
	statusBar()->addWidget(msgLabel, 1);
}

// Action create
void MapView::createActions()
{
	openAction = new QAction(tr("&Open"),this);
	openAction->setIcon(QIcon(":/images/open.png"));
	openAction->setShortcut(QKeySequence::Open);
	openAction->setStatusTip(tr("Open a map file"));
	connect(openAction,SIGNAL(triggered()),this,SLOT(open()));

	saveAllAction = new QAction(tr("&Save All"),this);
	saveAllAction->setIcon(QIcon(":/images/save.png"));
	saveAllAction->setShortcut(QKeySequence::Save);
	saveAllAction->setStatusTip(tr("Save map and user layer to disk and database"));
	connect(saveAllAction,SIGNAL(triggered()),this,SLOT(saveall()));

	//file save
	saveFileAction = new QAction(tr("Save &File"),this);
	saveFileAction->setIcon(QIcon(":/images/save.png"));
	saveFileAction->setShortcut(tr("Ctrl+Shift+S"));
	saveFileAction->setStatusTip(tr("Save map to disk including user layer"));
	connect(saveFileAction,SIGNAL(triggered()),main,   SLOT(save()));

	//save as
	saveAsAction = new QAction(tr("Save &As"),this);
	saveAsAction->setIcon(QIcon(":/images/saveas.png"));
	saveAsAction->setShortcut(tr("Ctrl+A"));
	saveAsAction->setStatusTip(tr("Save map to disk with new file name including user layer"));
	connect(saveAsAction,SIGNAL(triggered()),this,SLOT(saveas()));

	//load ul from db
	GetUserLayerFromDbAction=new QAction(tr("Load U&L from Db"),this);
	GetUserLayerFromDbAction->setIcon(QIcon(":/images/fromdb.png"));
	GetUserLayerFromDbAction->setStatusTip(tr("Get user layer from database"));
	connect(GetUserLayerFromDbAction,SIGNAL(triggered()),main,SLOT(getulfromdb()));

	//save ul to db
	LoadUserLayerToDbAction =new QAction(tr("Save UL to &Db"),this);
	LoadUserLayerToDbAction->setIcon(QIcon(":/images/todb.png"));
	LoadUserLayerToDbAction->setStatusTip(tr("Save user layer to database"));
	connect(LoadUserLayerToDbAction,SIGNAL(triggered()),main,SLOT(saveultodb()));

	makeMapFromDBAction = new QAction(tr("Make map file from Db"), this);
	//makeMapFromDBAction->setIcon(QIcon(":/images/todb.png"));
	makeMapFromDBAction->setStatusTip(tr("Create Map file from database"));
	connect(makeMapFromDBAction,SIGNAL(triggered()),main,SLOT(makeMapFromDb()));

	//panel
	leftpanelVisibleAction = new QAction(tr("&Layer Panel Hide"),this);
	leftpanelVisibleAction->setIcon(QIcon(":/images/layer_blue.png"));
	leftpanelVisibleAction->setShortcut(tr("Ctrl+L"));
	leftpanelVisibleAction->setStatusTip(tr("hide show layer panel (Ctrl+L)"));
	connect(leftpanelVisibleAction,SIGNAL(triggered()),this,SLOT(setLeftPanelVisible()));

	objectpanelVisibleAction = new QAction(tr("&Object Panel Hide"),this);
	objectpanelVisibleAction->setIcon(QIcon(":/images/panel_blue.png"));
	objectpanelVisibleAction->setShortcut(tr("Ctrl+P"));
	objectpanelVisibleAction->setStatusTip(tr("hide or show object panel (Ctrl+P)"));
	connect(objectpanelVisibleAction,SIGNAL(triggered()),this,SLOT(setObjectPanelVisible()));

	//map control
	zoomInAction = new QAction(tr("zoom &in"),this);
	zoomInAction->setIcon(QIcon(":/images/zoomin.png"));
	zoomInAction->setStatusTip(tr("Zoom in map, short key : + "));
	connect(zoomInAction,SIGNAL(triggered()),this,SLOT(zoomIn()));

	zoomOutAction = new QAction(tr("zoom &out"),this);
	zoomOutAction->setIcon(QIcon(":/images/zoomout.png"));
	zoomOutAction->setStatusTip(tr("Zoom out map, short key : - "));
	connect(zoomOutAction,SIGNAL(triggered()),this,SLOT(zoomOut()));

	moveHomeAction = new QAction(tr("se&t Init"),this);
	moveHomeAction->setIcon(QIcon(":/images/sethome.png"));
	moveHomeAction->setStatusTip(tr("move to initiali zoom and postion"));
	connect(moveHomeAction,SIGNAL(triggered()),this,SLOT(moveHome()));

	moveLeftAction = new QAction(tr("move &Left"),this);
	moveLeftAction->setIcon(QIcon(":/images/arrow_left.png"));
	moveLeftAction->setStatusTip(tr("move map to left , short key : arrow left "));
	connect(moveLeftAction,SIGNAL(triggered()),this,SLOT(moveLeft()));

	moveRightAction = new QAction(tr("move &Right"),this);
	moveRightAction->setIcon(QIcon(":/images/arrow_right.png"));
	moveRightAction->setStatusTip(tr("move map to right, short key : arrow right"));
	connect(moveRightAction,SIGNAL(triggered()),this,SLOT(moveRight()));

	moveUpAction = new QAction(tr("move &Up"),this);
	moveUpAction->setIcon(QIcon(":/images/arrow_up.png"));
	moveUpAction->setStatusTip(tr("move map to upper , short key : arrow up"));
	connect(moveUpAction,SIGNAL(triggered()),this,SLOT(moveUp()));

	moveDownAction = new QAction(tr("move &Down"),this);
	moveDownAction->setIcon(QIcon(":/images/arrow_down.png"));
	moveDownAction->setStatusTip(tr("move map to down , short key : arrow down"));
	connect(moveDownAction,SIGNAL(triggered()),this,SLOT(moveDown()));

	//compass
	drawCrossAction = new QAction(tr("show &Compass"),this);
	drawCrossAction->setIcon(QIcon(":/images/cross.png"));
	drawCrossAction->setStatusTip(tr("show compass "));
	drawCrossAction->setCheckable(true);
	drawCrossAction->setChecked(false);
	connect(drawCrossAction,SIGNAL(triggered(bool)),main,SLOT(showBearingCircle(bool)));

	//경위도
	drawLatlonAction = new QAction(tr("show &Lat lon"),this);
	drawLatlonAction->setIcon(QIcon(":/images/latlon.png"));
	drawLatlonAction->setStatusTip(tr("show latitude and longitude"));
	drawLatlonAction->setCheckable(true);
	drawLatlonAction->setChecked(true);
	connect(drawLatlonAction,SIGNAL(triggered(bool)),main,SLOT(showLatLon(bool)));

	//id text 표시여부
	drawLayerIdAction = new QAction(tr("show Layer &Id"),this);
	drawLayerIdAction->setIcon(QIcon(":/images/idvisible.png"));
	drawLayerIdAction->setStatusTip(tr("show  id text on map"));
	drawLayerIdAction->setCheckable(true);
	drawLayerIdAction->setChecked(false);
	//connect(drawLayerIdAction,SIGNAL(triggered()),this,SLOT(drawLayerId()));
	connect(drawLayerIdAction,SIGNAL(triggered(bool)),main,SLOT(onoffLayerIdText(bool)));

	savePixmapAction = new QAction(tr("save map &image"),this);
	savePixmapAction->setStatusTip(tr("save map to file"));
	connect(savePixmapAction,SIGNAL(triggered()),this,SLOT(savePixmap()));

	exitAction = new QAction(tr("E&xit"),this);
	exitAction->setIcon(QIcon(":/images/quit.png"));
	exitAction->setShortcut(tr("Ctrl+Q"));
	exitAction->setStatusTip(tr("Exit the application"));
	connect(exitAction,SIGNAL(triggered()),this,SLOT(close()));

	//거리와 방향을 표시
	pointdistanceAction = new QAction(tr("Distance and Direction"),this);
	pointdistanceAction->setIcon(QIcon(":/images/pointdistance.png"));
	pointdistanceAction->setStatusTip(tr("display distance and direction from a point"));
	pointdistanceAction->setCheckable(true);
	connect(pointdistanceAction,SIGNAL(triggered(bool)),main,SLOT(onoffDistancBearing(bool)));

	// Track Report Menu
	trackCreateAction = new QAction(tr("Create"), this);
	trackCreateAction->setStatusTip(tr("Track Report Create"));
	connect(trackCreateAction, SIGNAL(triggered()), main, SLOT(trackCreate()));

	trackSaveAction = new QAction(tr("Save"), this);
	trackSaveAction->setStatusTip(tr("Track Report Save"));
	connect(trackSaveAction, SIGNAL(triggered()), main, SLOT(trackSave()));

	trackOpenAction = new QAction(tr("Open"), this);
	trackOpenAction->setStatusTip(tr("Track Report Open"));
	connect(trackOpenAction, SIGNAL(triggered()), main, SLOT(trackOpen()));

	trackOptionAction = new QAction(tr("Options"), this);
	trackOptionAction->setStatusTip(tr("Track Report Options select"));
	connect(trackOptionAction, SIGNAL(triggered()), main, SLOT(trackOption()));

	trackClTableAction = new QAction(tr("Clear Table"), this);
	trackClTableAction->setStatusTip(tr("Track Report Clear Table"));
	connect(trackClTableAction, SIGNAL(triggered()), main, SLOT(trackClTable()));

	trackClPanelAction = new QAction(tr("Clear Panel"), this);
	trackClPanelAction->setStatusTip(tr("Track Report Clear Panel"));
	connect(trackClPanelAction, SIGNAL(triggered()), main, SLOT(trackClPanel()));

	trackPrintAction = new QAction(tr("Print"), this);
	trackPrintAction->setStatusTip(tr("Track Report Print"));
	connect(trackPrintAction, SIGNAL(triggered()), main, SLOT(trackPrint()));
}

void MapView::createMenus()
{
	fileMenu = menuBar()->addMenu(tr("&File"));
	fileMenu->addAction(openAction);
	fileMenu->addSeparator();
	fileMenu->addAction(saveAllAction);
	fileMenu->addAction(saveFileAction);
	fileMenu->addAction(saveAsAction);
	fileMenu->addSeparator();
	fileMenu->addAction(LoadUserLayerToDbAction);
	fileMenu->addAction(GetUserLayerFromDbAction);
	fileMenu->addAction(makeMapFromDBAction);
	fileMenu->addSeparator();
	fileMenu->addAction(exitAction);

	viewMenu = menuBar()->addMenu(QObject::tr("&View"));
    viewMenu->addAction(leftpanelVisibleAction);
    viewMenu->addAction(objectpanelVisibleAction);
    viewMenu->addSeparator();
    viewMenu->addAction(drawCrossAction);
    viewMenu->addAction(drawLatlonAction);
    viewMenu->addAction(drawLayerIdAction);
    viewMenu->addSeparator();
    viewMenu->addAction(savePixmapAction);

    toolsMenu = menuBar()->addMenu(QObject::tr("&Tools"));
    toolsMenu->addAction(QObject::tr("Symbol Editor"), this, SLOT(setSymbolEditor()));

	helpMenu = menuBar()->addMenu(QObject::tr("&Help"));
    helpMenu->addAction(QObject::tr("About"), this, SLOT(about()));
    helpMenu->addAction(QObject::tr("About Qt"), qApp, SLOT(aboutQt()));

    trackMenu = menuBar()->addMenu(QObject::tr("Track &Report"));
    trackMenu->addAction(trackCreateAction);
    trackMenu->addAction(trackSaveAction);
    trackMenu->addAction(trackOpenAction);
    trackMenu->addAction(trackOptionAction);
    trackMenu->addAction(trackClTableAction);
    trackMenu->addAction(trackClPanelAction);
    trackMenu->addAction(trackPrintAction);

}

void MapView::createToolBars()
{

	fileToolBar = addToolBar(tr("&File"));
	fileToolBar->addAction(openAction);
	fileToolBar->addAction(saveAllAction);

	mapToolBar = addToolBar(tr("&Map"));
	mapToolBar->addAction(zoomInAction);
	mapToolBar->addAction(zoomOutAction);
	mapToolBar->addAction(moveHomeAction);
	mapToolBar->addAction(moveLeftAction);
	mapToolBar->addAction(moveRightAction);
	mapToolBar->addAction(moveUpAction);
	mapToolBar->addAction(moveDownAction);

	drawToolBar = addToolBar(tr("&Draw"));
	drawToolBar->addAction(leftpanelVisibleAction);
	drawToolBar->addAction(objectpanelVisibleAction);
	drawToolBar->addAction(drawCrossAction);
	drawToolBar->addAction(drawLatlonAction);
	drawToolBar->addAction(drawLayerIdAction);

	appToolBar = addToolBar(tr("&App"));
	appToolBar->addAction(pointdistanceAction);
}

void MapView::changeMousePos(const QString& xy)
{
	//std::cout << "changeMousePos called..........\n";

	mousePosLabel->setText(xy);
}
void MapView::changeLatLonPos(const QString& xy)
{
	mapPosLabel->setText(xy);
}
void MapView::changeStatusMessage(const QString& msg)
{
	msgLabel->setText(msg);
}

void MapView::setLeftPanelVisible()
{
	//leftPanel->setVisible(b);
	if (leftDockWidget->isHidden()) {
		leftDockWidget->setVisible(true);
		leftpanelVisibleAction->setText("&Layer Panel Hide");
	}else {
		leftDockWidget->setVisible(false);
		leftpanelVisibleAction->setText("&Layer Panel Show");
	}
}

void MapView::setObjectPanelVisible()
{
	if (rightDockWidget->isHidden()) {
		rightDockWidget->setVisible(true);
		objectpanelVisibleAction->setText("&Object Panel Hide");
	}else {
		rightDockWidget->setVisible(false);
		objectpanelVisibleAction->setText("&Object Panel Show");
	}
}

/**
 * Layer Map <-> User Defined Map => Tab 선택 변경
 * MapCanvas 클래스의 setIsUserDefinedMap 메소드를 호출한다.
 */
void MapView::setObjectPanelVisibleChild(int idx)
{
	bool isUserDefinedMap = false;
	if (idx == 1) {
		isUserDefinedMap = true;
	}
	main->setIsUserDefinedMap(isUserDefinedMap, leftPanel->getUserDefinedMap());
}

/**
 * UserDefinedMap 변경됨 => MapCanvas에 맵 전달
 */
void MapView::setUserDefinedMap()
{
	main->setIsUserDefinedMap(true, leftPanel->getUserDefinedMap());
}


/**
 * Execute Symbol Editor Program
 */
void MapView::setSymbolEditor()
{
	QString program = "/root/workspace/Trunk/Trunk";
	QProcess *process = new QProcess(this);
	process->start(program);
}

/**
 * Map data open
 */
void MapView::open()
{
    QString mapdir = ConfigParser::getInstance().envMapDir();
    QString fileName = QFileDialog::getOpenFileName(this,
                                tr("Open Map File"),
                                mapdir,
                                tr("Map Files (*.map);;All Files (*)"),
                                0,0
                                );
    if (!fileName.isEmpty()){
		 main->open(fileName);
       ConfigParser::getInstance().setMapfile(fileName);
       setTitle(fileName);
    }
}

/**
 * Map data save
 */
void MapView::saveall()
{
    main->save();
    main->saveultodb();

}

/**
 * 현재 화면에 현시된 맵 출력물을 맵 데이터로 생성해서 다른 이름으로 저장한다.
 */
void MapView::saveas()
{
    QString mapdir = ConfigParser::getInstance().envMapDir();
    QString fileName = QFileDialog::getSaveFileName(this,
                                tr("Savs As map data"),
                                mapdir,
                                tr("Map Files (*.map);;All Files (*)"),
                                0,0
                                );
    if (!fileName.isEmpty()){

       QRegExp rx("\\.[^\\/]*$");
       if (rx.indexIn(fileName) == -1)
       {
         fileName += ".map";
       }

       if (QFile::exists(fileName)) {
           int r = QMessageBox::warning(this, tr("Map file save as"),
                           tr("File %1 already exists.\n"
                              "Do you want to overwrite it?")
                           .arg(QDir::toNativeSeparators(fileName)),
                           QMessageBox::Yes | QMessageBox::No);
           if (r == QMessageBox::No) return ;
       }
       main->saveas(fileName);
       ConfigParser::getInstance().setMapfile(fileName);
       setTitle(fileName);
   }

}

/**
 * 맵 에디터에 출력된 맵 데이터를 이미지로 저장한다.
 */
void MapView::savePixmap()
{
   QString fileName = QFileDialog::getSaveFileName(this,
                                tr("Savs As map image"),
                                QDir::currentPath(),
                                tr("png file format (*.png);;jpeg file format (*.jpg)"),
                                0,0
                                );
   if (!fileName.isEmpty()){
       main->savePixmap(fileName);
    }

}

/**
 * About
 */
void MapView::about()
{
     QMessageBox::about(this, tr("AMS Map Edit"),
     tr("draw and edit user layer<br>"
        "from Air Transportation Advancement Program(ATAP)"));
}

/**
 * MainWindow의 타이틀을 설정한다.
 */
void MapView::setTitle(const QString& title)
{
    setWindowTitle(QString("smeu - %1").arg(title));
}
