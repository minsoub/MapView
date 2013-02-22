/********************************************************************************
** Form generated from reading UI file 'TrackViewSelection.ui'
**
** Created: Fri Feb 1 10:10:55 2013
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRACKVIEWSELECTION_H
#define UI_TRACKVIEWSELECTION_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTableWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TrackViewSelectionClass
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_10;
    QLabel *label;
    QSpacerItem *horizontalSpacer_11;
    QTableWidget *tableView;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_8;
    QPushButton *btnSelectAll;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnUnselectAll;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *btnTrackReport;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *btnVerticalView;
    QSpacerItem *horizontalSpacer_7;
    QPushButton *btnReport;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *btnADSB;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *btnDataBlock;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *btnClose;
    QSpacerItem *horizontalSpacer_9;

    void setupUi(QWidget *TrackViewSelectionClass)
    {
        if (TrackViewSelectionClass->objectName().isEmpty())
            TrackViewSelectionClass->setObjectName(QString::fromUtf8("TrackViewSelectionClass"));
        TrackViewSelectionClass->resize(902, 479);
        verticalLayout = new QVBoxLayout(TrackViewSelectionClass);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_10);

        label = new QLabel(TrackViewSelectionClass);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);

        horizontalLayout_2->addWidget(label);

        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_11);


        verticalLayout->addLayout(horizontalLayout_2);

        tableView = new QTableWidget(TrackViewSelectionClass);
        tableView->setObjectName(QString::fromUtf8("tableView"));

        verticalLayout->addWidget(tableView);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_8);

        btnSelectAll = new QPushButton(TrackViewSelectionClass);
        btnSelectAll->setObjectName(QString::fromUtf8("btnSelectAll"));

        horizontalLayout->addWidget(btnSelectAll);

        horizontalSpacer = new QSpacerItem(18, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btnUnselectAll = new QPushButton(TrackViewSelectionClass);
        btnUnselectAll->setObjectName(QString::fromUtf8("btnUnselectAll"));

        horizontalLayout->addWidget(btnUnselectAll);

        horizontalSpacer_2 = new QSpacerItem(18, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        btnTrackReport = new QPushButton(TrackViewSelectionClass);
        btnTrackReport->setObjectName(QString::fromUtf8("btnTrackReport"));

        horizontalLayout->addWidget(btnTrackReport);

        horizontalSpacer_3 = new QSpacerItem(18, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        btnVerticalView = new QPushButton(TrackViewSelectionClass);
        btnVerticalView->setObjectName(QString::fromUtf8("btnVerticalView"));

        horizontalLayout->addWidget(btnVerticalView);

        horizontalSpacer_7 = new QSpacerItem(18, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_7);

        btnReport = new QPushButton(TrackViewSelectionClass);
        btnReport->setObjectName(QString::fromUtf8("btnReport"));

        horizontalLayout->addWidget(btnReport);

        horizontalSpacer_4 = new QSpacerItem(18, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);

        btnADSB = new QPushButton(TrackViewSelectionClass);
        btnADSB->setObjectName(QString::fromUtf8("btnADSB"));

        horizontalLayout->addWidget(btnADSB);

        horizontalSpacer_5 = new QSpacerItem(18, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_5);

        btnDataBlock = new QPushButton(TrackViewSelectionClass);
        btnDataBlock->setObjectName(QString::fromUtf8("btnDataBlock"));

        horizontalLayout->addWidget(btnDataBlock);

        horizontalSpacer_6 = new QSpacerItem(18, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_6);

        btnClose = new QPushButton(TrackViewSelectionClass);
        btnClose->setObjectName(QString::fromUtf8("btnClose"));

        horizontalLayout->addWidget(btnClose);

        horizontalSpacer_9 = new QSpacerItem(28, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_9);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(TrackViewSelectionClass);

        QMetaObject::connectSlotsByName(TrackViewSelectionClass);
    } // setupUi

    void retranslateUi(QWidget *TrackViewSelectionClass)
    {
        TrackViewSelectionClass->setWindowTitle(QApplication::translate("TrackViewSelectionClass", "TrackViewSelection", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("TrackViewSelectionClass", "Track / View Selection", 0, QApplication::UnicodeUTF8));
        btnSelectAll->setText(QApplication::translate("TrackViewSelectionClass", "&Select All", 0, QApplication::UnicodeUTF8));
        btnUnselectAll->setText(QApplication::translate("TrackViewSelectionClass", "&Unselect All", 0, QApplication::UnicodeUTF8));
        btnTrackReport->setText(QApplication::translate("TrackViewSelectionClass", "&Track Report", 0, QApplication::UnicodeUTF8));
        btnVerticalView->setText(QApplication::translate("TrackViewSelectionClass", "&Vertical View", 0, QApplication::UnicodeUTF8));
        btnReport->setText(QApplication::translate("TrackViewSelectionClass", "&Report", 0, QApplication::UnicodeUTF8));
        btnADSB->setText(QApplication::translate("TrackViewSelectionClass", "&ADS B/A", 0, QApplication::UnicodeUTF8));
        btnDataBlock->setText(QApplication::translate("TrackViewSelectionClass", "&Data Block", 0, QApplication::UnicodeUTF8));
        btnClose->setText(QApplication::translate("TrackViewSelectionClass", "&Close", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class TrackViewSelectionClass: public Ui_TrackViewSelectionClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRACKVIEWSELECTION_H
