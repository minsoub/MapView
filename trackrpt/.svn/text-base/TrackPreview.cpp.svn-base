/*
 * TrackPreview.cpp
 *
 *  Created on: 2012. 5. 03.
 *      Author: JMS
 *  Description : Preview Track Data report
 */
#include "TrackPreview.h"

TrackPreview::TrackPreview(QWidget *parent)
    : QWidget(parent)
{
	setupUi(this);

	connect(btnPrint, SIGNAL(clicked()), this, SLOT(trackPrint()));
	connect(btnClose, SIGNAL(clicked()), this, SLOT(previewClose()));

}

TrackPreview::~TrackPreview()
{

}

/**
 * set Scene size.
 */
void TrackPreview::setSceneSize(QRectF rect) {
	scene = new QGraphicsScene(QRect(0, 0, (int)rect.width()+250, (int)rect.height()));
	graphicsView->setScene(scene);
}

/**
 * Track Preview 데이터를 프린트한다.
 */
void TrackPreview::trackPrint()
{
	 QPainter *pngPainter = new QPainter();
	 QPixmap *image = new QPixmap(scene->sceneRect().size().toSize());
	 pngPainter->begin(image);
	 scene->render(pngPainter);
	 pngPainter->end();

	 QPrinter printer(QPrinter::HighResolution);
	 printer.setPageSize(QPrinter::A4);
	 printer.setOrientation(QPrinter::Landscape);

	 QPrintDialog printDialog(&printer, this);

	 if (printDialog.exec()) {
		 QPainter painter(&printer);
		 QRect rect = painter.viewport();
		 QSize size = image->size();
		 size.scale(rect.size(), Qt::KeepAspectRatio);
		 painter.setViewport(rect.x(), rect.y(), size.width(), size.height());
		 painter.setWindow(image->rect());
		 painter.drawPixmap(0, 0, *image);

		 // print, fitting the viewport contents into a full page
		//	 view->render(&painter);
	 }
}

/**
 * Preview Close
 */
void TrackPreview::previewClose()
{
	close();
}
/**
 * QPixmap 으로 넘어온 Track 데이터를 scaled 시켜 화면에 출력시킨다.
 */
void TrackPreview::setScene(QVector<TrackDataModel> data, QPixmap *image)
{

	scene->clear();
	//QPixmap pixmap = image;			// QPixmap::fromImage(*image);
	QPixmap tmp = image->scaled(QSize((int)scene->sceneRect().width()-250,
									(int)scene->sceneRect().height()), Qt::KeepAspectRatio);  // Qt::IgnoreAspectRatio);

	scene->addPixmap(tmp);

	// 범례 추가
	item = new LegendItem(tmp.size().width(), scene->sceneRect());
	item->setTrackData(data);

	scene->addItem(item);

	scene->update();

}
