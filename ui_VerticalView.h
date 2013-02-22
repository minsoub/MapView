/********************************************************************************
** Form generated from reading UI file 'VerticalView.ui'
**
** Created: Fri Feb 1 10:10:55 2013
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VERTICALVIEW_H
#define UI_VERTICALVIEW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QFrame>
#include <QtGui/QGraphicsView>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VerticalViewClass
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_5;
    QLabel *label;
    QSpacerItem *horizontalSpacer_6;
    QFrame *line;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_7;
    QComboBox *cboSelect;
    QGraphicsView *graphicsView;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *btnZoomIn;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnZoomOut;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *btnClose;
    QSpacerItem *horizontalSpacer_4;

    void setupUi(QWidget *VerticalViewClass)
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
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer_7 = new QSpacerItem(38, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_7);

        cboSelect = new QComboBox(VerticalViewClass);
        cboSelect->setObjectName(QString::fromUtf8("cboSelect"));
        cboSelect->setMinimumSize(QSize(200, 0));

        horizontalLayout_3->addWidget(cboSelect);


        verticalLayout->addLayout(horizontalLayout_3);

        graphicsView = new QGraphicsView(VerticalViewClass);
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


        retranslateUi(VerticalViewClass);

        QMetaObject::connectSlotsByName(VerticalViewClass);
    } // setupUi

    void retranslateUi(QWidget *VerticalViewClass)
    {
        VerticalViewClass->setWindowTitle(QApplication::translate("VerticalViewClass", "VerticalView", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("VerticalViewClass", "Vertical View", 0, QApplication::UnicodeUTF8));
        btnZoomIn->setText(QApplication::translate("VerticalViewClass", "Zoom-&In", 0, QApplication::UnicodeUTF8));
        btnZoomOut->setText(QApplication::translate("VerticalViewClass", "Zoom-&Out", 0, QApplication::UnicodeUTF8));
        btnClose->setText(QApplication::translate("VerticalViewClass", "&Close", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class VerticalViewClass: public Ui_VerticalViewClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VERTICALVIEW_H
