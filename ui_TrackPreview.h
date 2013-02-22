/********************************************************************************
** Form generated from reading UI file 'TrackPreview.ui'
**
** Created: Fri Feb 1 10:10:55 2013
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRACKPREVIEW_H
#define UI_TRACKPREVIEW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGraphicsView>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TrackPreviewClass
{
public:
    QVBoxLayout *verticalLayout;
    QGraphicsView *graphicsView;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnPrint;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *btnClose;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *TrackPreviewClass)
    {
        if (TrackPreviewClass->objectName().isEmpty())
            TrackPreviewClass->setObjectName(QString::fromUtf8("TrackPreviewClass"));
        TrackPreviewClass->resize(1113, 861);
        verticalLayout = new QVBoxLayout(TrackPreviewClass);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        graphicsView = new QGraphicsView(TrackPreviewClass);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));

        verticalLayout->addWidget(graphicsView);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btnPrint = new QPushButton(TrackPreviewClass);
        btnPrint->setObjectName(QString::fromUtf8("btnPrint"));

        horizontalLayout->addWidget(btnPrint);

        horizontalSpacer_3 = new QSpacerItem(18, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        btnClose = new QPushButton(TrackPreviewClass);
        btnClose->setObjectName(QString::fromUtf8("btnClose"));

        horizontalLayout->addWidget(btnClose);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(TrackPreviewClass);

        QMetaObject::connectSlotsByName(TrackPreviewClass);
    } // setupUi

    void retranslateUi(QWidget *TrackPreviewClass)
    {
        TrackPreviewClass->setWindowTitle(QApplication::translate("TrackPreviewClass", "TrackPreview", 0, QApplication::UnicodeUTF8));
        btnPrint->setText(QApplication::translate("TrackPreviewClass", "Print", 0, QApplication::UnicodeUTF8));
        btnClose->setText(QApplication::translate("TrackPreviewClass", "Close", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class TrackPreviewClass: public Ui_TrackPreviewClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRACKPREVIEW_H
