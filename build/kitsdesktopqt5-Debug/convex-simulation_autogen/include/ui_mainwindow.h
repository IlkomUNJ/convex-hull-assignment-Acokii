/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include <coordinatebox.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *button;
    QPushButton *slowConvex;
    QPushButton *fastConvex;
    QPushButton *clearDot;
    CoordinateBox *coordinatebox;
    QLabel *iteration;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        button = new QWidget(MainWindow);
        button->setObjectName(QString::fromUtf8("button"));
        slowConvex = new QPushButton(button);
        slowConvex->setObjectName(QString::fromUtf8("slowConvex"));
        slowConvex->setGeometry(QRect(60, 480, 161, 51));
        fastConvex = new QPushButton(button);
        fastConvex->setObjectName(QString::fromUtf8("fastConvex"));
        fastConvex->setGeometry(QRect(310, 480, 161, 51));
        clearDot = new QPushButton(button);
        clearDot->setObjectName(QString::fromUtf8("clearDot"));
        clearDot->setGeometry(QRect(550, 480, 161, 51));
        coordinatebox = new CoordinateBox(button);
        coordinatebox->setObjectName(QString::fromUtf8("coordinatebox"));
        coordinatebox->setGeometry(QRect(60, 40, 651, 411));
        iteration = new QLabel(button);
        iteration->setObjectName(QString::fromUtf8("iteration"));
        iteration->setGeometry(QRect(60, 460, 66, 18));
        MainWindow->setCentralWidget(button);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        slowConvex->setText(QCoreApplication::translate("MainWindow", "Run Convex Hull", nullptr));
        fastConvex->setText(QCoreApplication::translate("MainWindow", "Run Fast Convex Hull", nullptr));
        clearDot->setText(QCoreApplication::translate("MainWindow", "Clear All", nullptr));
        coordinatebox->setTitle(QCoreApplication::translate("MainWindow", "Shower", nullptr));
        iteration->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
