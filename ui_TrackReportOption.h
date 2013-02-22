/********************************************************************************
** Form generated from reading UI file 'TrackReportOption.ui'
**
** Created: Fri Feb 1 10:10:55 2013
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRACKREPORTOPTION_H
#define UI_TRACKREPORTOPTION_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QFrame>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TrackReportOptionClass
{
public:
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_5;
    QLabel *label;
    QSpacerItem *horizontalSpacer_6;
    QFrame *line;
    QSpacerItem *verticalSpacer_2;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_7;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *horizontalSpacer_11;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_7;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout_8;
    QListWidget *listDataBlock;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_4;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *btnLeft;
    QSpacerItem *horizontalSpacer_10;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_8;
    QPushButton *btnRight;
    QSpacerItem *horizontalSpacer_9;
    QSpacerItem *verticalSpacer_5;
    QListWidget *listSelectDataBlock;
    QSpacerItem *verticalSpacer_6;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_9;
    QComboBox *cboBlock;
    QLabel *label_4;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnDone;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *TrackReportOptionClass)
    {
        if (TrackReportOptionClass->objectName().isEmpty())
            TrackReportOptionClass->setObjectName(QString::fromUtf8("TrackReportOptionClass"));
        TrackReportOptionClass->resize(754, 533);
        verticalLayout_4 = new QVBoxLayout(TrackReportOptionClass);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_5);

        label = new QLabel(TrackReportOptionClass);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setPointSize(20);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);

        horizontalLayout_2->addWidget(label);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_6);


        verticalLayout_4->addLayout(horizontalLayout_2);

        line = new QFrame(TrackReportOptionClass);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_4->addWidget(line);

        verticalSpacer_2 = new QSpacerItem(20, 15, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_4->addItem(verticalSpacer_2);

        groupBox = new QGroupBox(TrackReportOptionClass);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setAutoFillBackground(true);
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_3->addWidget(label_2);

        horizontalSpacer_4 = new QSpacerItem(198, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);


        horizontalLayout_7->addLayout(horizontalLayout_3);

        horizontalSpacer_11 = new QSpacerItem(88, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_11);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalSpacer_7 = new QSpacerItem(138, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_7);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_4->addWidget(label_3);


        horizontalLayout_7->addLayout(horizontalLayout_4);


        verticalLayout_2->addLayout(horizontalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        listDataBlock = new QListWidget(groupBox);
        listDataBlock->setObjectName(QString::fromUtf8("listDataBlock"));
        listDataBlock->setSelectionMode(QAbstractItemView::MultiSelection);

        horizontalLayout_8->addWidget(listDataBlock);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalSpacer_4 = new QSpacerItem(20, 78, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalSpacer_3 = new QSpacerItem(13, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_3);

        btnLeft = new QPushButton(groupBox);
        btnLeft->setObjectName(QString::fromUtf8("btnLeft"));
        btnLeft->setMaximumSize(QSize(60, 16777215));

        horizontalLayout_5->addWidget(btnLeft);

        horizontalSpacer_10 = new QSpacerItem(13, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_10);


        verticalLayout->addLayout(horizontalLayout_5);

        verticalSpacer_3 = new QSpacerItem(20, 18, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_3);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalSpacer_8 = new QSpacerItem(13, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_8);

        btnRight = new QPushButton(groupBox);
        btnRight->setObjectName(QString::fromUtf8("btnRight"));
        btnRight->setMaximumSize(QSize(60, 16777215));

        horizontalLayout_6->addWidget(btnRight);

        horizontalSpacer_9 = new QSpacerItem(13, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_9);


        verticalLayout->addLayout(horizontalLayout_6);

        verticalSpacer_5 = new QSpacerItem(20, 78, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_5);


        horizontalLayout_8->addLayout(verticalLayout);

        listSelectDataBlock = new QListWidget(groupBox);
        listSelectDataBlock->setObjectName(QString::fromUtf8("listSelectDataBlock"));
        listSelectDataBlock->setSelectionMode(QAbstractItemView::MultiSelection);

        horizontalLayout_8->addWidget(listSelectDataBlock);


        verticalLayout_2->addLayout(horizontalLayout_8);


        verticalLayout_4->addWidget(groupBox);

        verticalSpacer_6 = new QSpacerItem(20, 13, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_4->addItem(verticalSpacer_6);

        groupBox_2 = new QGroupBox(TrackReportOptionClass);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setAutoFillBackground(true);
        verticalLayout_3 = new QVBoxLayout(groupBox_2);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        cboBlock = new QComboBox(groupBox_2);
        cboBlock->setObjectName(QString::fromUtf8("cboBlock"));

        horizontalLayout_9->addWidget(cboBlock);

        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_9->addWidget(label_4);


        verticalLayout_3->addLayout(horizontalLayout_9);


        verticalLayout_4->addWidget(groupBox_2);

        verticalSpacer = new QSpacerItem(20, 15, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_4->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btnDone = new QPushButton(TrackReportOptionClass);
        btnDone->setObjectName(QString::fromUtf8("btnDone"));

        horizontalLayout->addWidget(btnDone);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout_4->addLayout(horizontalLayout);


        retranslateUi(TrackReportOptionClass);

        QMetaObject::connectSlotsByName(TrackReportOptionClass);
    } // setupUi

    void retranslateUi(QWidget *TrackReportOptionClass)
    {
        TrackReportOptionClass->setWindowTitle(QApplication::translate("TrackReportOptionClass", "TrackReportOption", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("TrackReportOptionClass", "Track Report Option", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("TrackReportOptionClass", "Data Blocks", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("TrackReportOptionClass", "Data Blocks", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("TrackReportOptionClass", "Selected Data Blocks", 0, QApplication::UnicodeUTF8));
        btnLeft->setText(QApplication::translate("TrackReportOptionClass", "<", 0, QApplication::UnicodeUTF8));
        btnRight->setText(QApplication::translate("TrackReportOptionClass", ">", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("TrackReportOptionClass", "Data Blocks Print Option", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("TrackReportOptionClass", "per/time", 0, QApplication::UnicodeUTF8));
        btnDone->setText(QApplication::translate("TrackReportOptionClass", "&Done", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class TrackReportOptionClass: public Ui_TrackReportOptionClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRACKREPORTOPTION_H
