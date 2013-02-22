/*
 * VerticalView.cpp
 *
 *  Created on: 2012. 5. 04.
 *      Author: JMS
 *  Description : Vertical View display.
 */
#include "VerticalView.h"

VerticalView::VerticalView(QWidget *parent)
    : QWidget(parent)
{
	this->setWindowTitle("Vertical View");
	setupUi(this);

   //graphicsView = new QGraphicsView(VerticalViewClass);
   //graphicsView->setObjectName(QString::fromUtf8("graphicsView"));

   //verticalLayout->addWidget(graphicsView);

	connect(btnZoomIn,  SIGNAL(clicked()), this, SLOT(ZoomIn()));
	connect(btnZoomOut, SIGNAL(clicked()), this, SLOT(ZoomOut()));
	connect(btnClose,   SIGNAL(clicked()), this, SLOT(close()));

	scene = new QGraphicsScene(QRect(0, 0, 1133, 700));
	graphicsView->setScene(scene);

	this->resize(QSize(1240, 830));

	cboSelect->addItem("Altitude Vertical View");
	cboSelect->addItem("Speed Vertical View");

	cboSelect->setCurrentIndex(0);

	connect(cboSelect, SIGNAL(currentIndexChanged(int)), this,  SLOT(selectedChange()));

}
void VerticalView::setupUi(QWidget *VerticalViewClass)
{
    if (VerticalViewClass->objectName().isEmpty())
        VerticalViewClass->setObjectName(QString::fromUtf8("VerticalViewClass"));
    VerticalViewClass->resize(1051, 733);
    verticalLayout = new QVBoxLayout(VerticalViewClass);
    verticalLayout->setSpacing(6);
    verticalLayout->setContentsMargins(11, 11, 11, 11);
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    horizontalLayout_2 = new QHBoxLayout();
    horizontalLayout_2->setSpacing(6);
    horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
    horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout_2->addItem(horizontalSpacer_5);

    label = new QLabel(VerticalViewClass);
    label->setObjectName(QString::fromUtf8("label"));

    QFont font;
    font.setPointSize(25);
    font.setBold(true);
    font.setWeight(75);
    label->setFont(font);

    horizontalLayout_2->addWidget(label);
    horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    horizontalLayout_2->addItem(horizontalSpacer_6);


    verticalLayout->addLayout(horizontalLayout_2);

    line = new QFrame(VerticalViewClass);
    line->setObjectName(QString::fromUtf8("line"));
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);

    verticalLayout->addWidget(line);

    horizontalLayout_3 = new QHBoxLayout();
    horizontalLayout_3->setSpacing(6);
    horizontalSpacer_7 = new QSpacerItem(38, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    horizontalLayout_3->addItem(horizontalSpacer_7);
    cboSelect = new QComboBox;
    cboSelect->setMinimumSize(QSize(200,25));

    horizontalLayout_3->addWidget(cboSelect);
    verticalLayout->addLayout(horizontalLayout_3);


    graphicsView = new VerticalViewControl(VerticalViewClass);
    graphicsView->setObjectName(QString::fromUtf8("graphicsView"));

    verticalLayout->addWidget(graphicsView);

    horizontalLayout = new QHBoxLayout();
    horizontalLayout->setSpacing(6);
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
    horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout->addItem(horizontalSpacer_3);

    btnZoomIn = new QPushButton(VerticalViewClass);
    btnZoomIn->setObjectName(QString::fromUtf8("btnZoomIn"));

    horizontalLayout->addWidget(btnZoomIn);

    horizontalSpacer = new QSpacerItem(28, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

    horizontalLayout->addItem(horizontalSpacer);

    btnZoomOut = new QPushButton(VerticalViewClass);
    btnZoomOut->setObjectName(QString::fromUtf8("btnZoomOut"));

    horizontalLayout->addWidget(btnZoomOut);

    horizontalSpacer_2 = new QSpacerItem(28, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

    horizontalLayout->addItem(horizontalSpacer_2);

    btnClose = new QPushButton(VerticalViewClass);
    btnClose->setObjectName(QString::fromUtf8("btnClose"));

    horizontalLayout->addWidget(btnClose);

    horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout->addItem(horizontalSpacer_4);


    verticalLayout->addLayout(horizontalLayout);

    label->setText(QApplication::translate("VerticalViewClass", "Vertical View", 0, QApplication::UnicodeUTF8));
    btnZoomIn->setText(QApplication::translate("VerticalViewClass", "Zoom-&In", 0, QApplication::UnicodeUTF8));
    btnZoomOut->setText(QApplication::translate("VerticalViewClass", "Zoom-&Out", 0, QApplication::UnicodeUTF8));
    btnClose->setText(QApplication::translate("VerticalViewClass", "&Close", 0, QApplication::UnicodeUTF8));
    //retranslateUi(VerticalViewClass);

    QMetaObject::connectSlotsByName(VerticalViewClass);
} // setupUi

VerticalView::~VerticalView()
{

}

/**
 * Vertical View combobox change method
 */
void VerticalView::selectedChange()
{
	if (cboSelect->currentIndex() == 0) {
		item->setMode(0);
	}else if(cboSelect->currentIndex() == 1) {
		item->setMode(1);
	}
	scene->update();
}
/**
 * Zoom In
 */
void VerticalView::ZoomIn()
{
	graphicsView->zoomIn();
}

/**
 * Zoom Out
 */
void VerticalView::ZoomOut()
{
	graphicsView->zoomOut();
}

/**
 * Set track data model
 */
void VerticalView::setTrackModel(QVector<TrackDataModel> m)
{
	model.clear();
	model = m;
}

/**
 * create Vertical View data item
 * This function delete the registered Item in QGraphicsScene, create new Item.
 */
void VerticalView::makeDisplay()
{
	qDebug() << "VerticalView makeDisplay called...";
	QList<QGraphicsItem *> items = scene->items();
	for (int i=0; i<items.size(); i++) {
		scene->removeItem(items[i]);
		delete items[i];
	}

	qDebug() << "VerticalViewItem create...";
	//scene->clear();

	item = new VerticalViewItem(model);
	item->setReportOption(option);
	item->setMode(cboSelect->currentIndex());
	scene->addItem(item);

	scene->update();

}
