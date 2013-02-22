/********************************************************************************
** Form generated from reading UI file 'createtrackreport.ui'
**
** Created: Fri Feb 1 10:10:55 2013
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATETRACKREPORT_H
#define UI_CREATETRACKREPORT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDateEdit>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QTimeEdit>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CreateTrackReportClass
{
public:
    QPushButton *btnOK;
    QPushButton *btnClose;
    QLabel *label;
    QLabel *label_2;
    QDateEdit *fromDt;
    QTimeEdit *fromTM;
    QDateEdit *toDt;
    QLabel *label_3;
    QTimeEdit *toTM;

    void setupUi(QWidget *CreateTrackReportClass)
    {
        if (CreateTrackReportClass->objectName().isEmpty())
            CreateTrackReportClass->setObjectName(QString::fromUtf8("CreateTrackReportClass"));
        CreateTrackReportClass->resize(591, 148);
        btnOK = new QPushButton(CreateTrackReportClass);
        btnOK->setObjectName(QString::fromUtf8("btnOK"));
        btnOK->setGeometry(QRect(190, 110, 75, 23));
        btnClose = new QPushButton(CreateTrackReportClass);
        btnClose->setObjectName(QString::fromUtf8("btnClose"));
        btnClose->setGeometry(QRect(300, 110, 75, 23));
        label = new QLabel(CreateTrackReportClass);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(200, 10, 241, 20));
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label_2 = new QLabel(CreateTrackReportClass);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 50, 56, 12));
        fromDt = new QDateEdit(CreateTrackReportClass);
        fromDt->setObjectName(QString::fromUtf8("fromDt"));
        fromDt->setGeometry(QRect(90, 46, 110, 22));
        fromTM = new QTimeEdit(CreateTrackReportClass);
        fromTM->setObjectName(QString::fromUtf8("fromTM"));
        fromTM->setGeometry(QRect(208, 46, 71, 22));
        toDt = new QDateEdit(CreateTrackReportClass);
        toDt->setObjectName(QString::fromUtf8("toDt"));
        toDt->setGeometry(QRect(372, 47, 110, 22));
        label_3 = new QLabel(CreateTrackReportClass);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(318, 51, 56, 12));
        toTM = new QTimeEdit(CreateTrackReportClass);
        toTM->setObjectName(QString::fromUtf8("toTM"));
        toTM->setGeometry(QRect(490, 47, 71, 22));

        retranslateUi(CreateTrackReportClass);

        QMetaObject::connectSlotsByName(CreateTrackReportClass);
    } // setupUi

    void retranslateUi(QWidget *CreateTrackReportClass)
    {
        CreateTrackReportClass->setWindowTitle(QApplication::translate("CreateTrackReportClass", "CreateTrackReport", 0, QApplication::UnicodeUTF8));
        btnOK->setText(QApplication::translate("CreateTrackReportClass", "&Ok", 0, QApplication::UnicodeUTF8));
        btnClose->setText(QApplication::translate("CreateTrackReportClass", "&Close", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("CreateTrackReportClass", "Create Track Report", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("CreateTrackReportClass", "From : ", 0, QApplication::UnicodeUTF8));
        fromTM->setDisplayFormat(QApplication::translate("CreateTrackReportClass", "hh:mm", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("CreateTrackReportClass", "To : ", 0, QApplication::UnicodeUTF8));
        toTM->setDisplayFormat(QApplication::translate("CreateTrackReportClass", "hh:mm", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class CreateTrackReportClass: public Ui_CreateTrackReportClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATETRACKREPORT_H
