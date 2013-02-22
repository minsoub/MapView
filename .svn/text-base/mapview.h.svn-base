#ifndef MAPVIEW_H
#define MAPVIEW_H

#include <QtGui>
#include "MapCanvas.h"
#include "leftlayout/LeftPanel.h"
#include "rightlayout/RightPanel.h"

class MapView : public QMainWindow
{
    Q_OBJECT

public:
    MapView(QWidget *parent = 0);
    ~MapView();
protected:
    void closeEvent(QCloseEvent *event);
private:
   MapCanvas   *main;
	LeftPanel   *leftPanel;
	RightPanel  *rightPanel;
	QDockWidget *leftDockWidget;
	QDockWidget *rightDockWidget;

	QLabel      *mousePosLabel;
	QLabel      *mapPosLabel;
	QLabel      *msgLabel;

	QMenu* fileMenu;
	QMenu* viewMenu;
	QMenu* helpMenu;
	QMenu* toolsMenu;
	QMenu* trackMenu;

	QToolBar* fileToolBar;
	QToolBar* mapToolBar;
	QToolBar* drawToolBar;
	QToolBar* appToolBar;

	QAction* newAction;
	QAction* openAction;
	QAction* saveAllAction;
	QAction* saveFileAction;
	QAction* saveAsAction;
	QAction* GetUserLayerFromDbAction;
	QAction* LoadUserLayerToDbAction;
	QAction* makeMapFromDBAction;

	// Panel Action
	QAction* leftpanelVisibleAction;
	QAction* objectpanelVisibleAction;

	// map control Action
	QAction* zoomInAction;
	QAction* zoomOutAction;
	QAction* moveHomeAction;
	QAction* moveLeftAction;
	QAction* moveRightAction;
	QAction* moveDownAction;
	QAction* moveUpAction;

	QAction* drawCrossAction;
	QAction* drawLatlonAction;
	QAction* drawLayerIdAction;
	QAction* savePixmapAction;
	QAction* exitAction;
	QAction* pointdistanceAction;		// point and distance direction

	QAction* trackCreateAction;
	QAction* trackOpenAction;
	QAction* trackOptionAction;
	QAction* trackClTableAction;
	QAction* trackClPanelAction;
	QAction* trackPrintAction;
	QAction* trackSaveAction;

	void createActions();
	void createMenus();
	void createToolBars();
	void createStatusBar();
	void setTitle(const QString& title);
private slots:
	void changeMousePos(const QString& xy);
	void changeLatLonPos(const QString& xy);
	void changeStatusMessage(const QString& msg);

	void moveUp()   { main->mapControl(MapCanvas::MoveUp); }
	void moveDown() { main->mapControl(MapCanvas::MoveDown); }
	void moveLeft() { main->mapControl(MapCanvas::MoveLeft); }
	void moveRight(){ main->mapControl(MapCanvas::MoveRight); }
	void moveHome() { main->mapControl(MapCanvas::MoveHome); }
	void zoomIn()   { main->mapControl(MapCanvas::ZoomIn); }
	void zoomOut()  { main->mapControl(MapCanvas::ZoomOut); }

	void setSymbolEditor();
	void open();
	void saveall();
	void saveas();
	void savePixmap();
	void about();

public slots:
	void setLeftPanelVisible();
	void setObjectPanelVisible();
	void setObjectPanelVisibleChild(int idx);
	void setUserDefinedMap();
};

#endif // MAPVIEW_H
