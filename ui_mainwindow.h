/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *dzisiejszetrasyguzik;
    QPushButton *wszystkietrasyguzik;
    QPushButton *dodajtraseguzik;
    QTableWidget *tabela;
    QPushButton *usuntraseguzik;
    QPushButton *edytujtraseguzik;
    QMenuBar *menubar;
    QMenu *menuJarzabBazaDanych_v1;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(840, 627);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        dzisiejszetrasyguzik = new QPushButton(centralwidget);
        dzisiejszetrasyguzik->setObjectName("dzisiejszetrasyguzik");
        dzisiejszetrasyguzik->setGeometry(QRect(190, 480, 151, 51));
        wszystkietrasyguzik = new QPushButton(centralwidget);
        wszystkietrasyguzik->setObjectName("wszystkietrasyguzik");
        wszystkietrasyguzik->setGeometry(QRect(20, 480, 151, 51));
        dodajtraseguzik = new QPushButton(centralwidget);
        dodajtraseguzik->setObjectName("dodajtraseguzik");
        dodajtraseguzik->setGeometry(QRect(410, 480, 121, 51));
        tabela = new QTableWidget(centralwidget);
        tabela->setObjectName("tabela");
        tabela->setGeometry(QRect(30, 30, 781, 401));
        usuntraseguzik = new QPushButton(centralwidget);
        usuntraseguzik->setObjectName("usuntraseguzik");
        usuntraseguzik->setGeometry(QRect(540, 480, 121, 51));
        edytujtraseguzik = new QPushButton(centralwidget);
        edytujtraseguzik->setObjectName("edytujtraseguzik");
        edytujtraseguzik->setGeometry(QRect(670, 480, 121, 51));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 840, 33));
        menuJarzabBazaDanych_v1 = new QMenu(menubar);
        menuJarzabBazaDanych_v1->setObjectName("menuJarzabBazaDanych_v1");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuJarzabBazaDanych_v1->menuAction());

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Jarz\304\205b Przewozy Baza Danych", nullptr));
        dzisiejszetrasyguzik->setText(QCoreApplication::translate("MainWindow", "Wy\305\233wietl Dzisiejsze Trasy", nullptr));
        wszystkietrasyguzik->setText(QCoreApplication::translate("MainWindow", "Wy\305\233wietl Wszystkie Trasy", nullptr));
        dodajtraseguzik->setText(QCoreApplication::translate("MainWindow", "Dodaj Tras\304\231", nullptr));
        usuntraseguzik->setText(QCoreApplication::translate("MainWindow", "Usu\305\204 Tras\304\231", nullptr));
        edytujtraseguzik->setText(QCoreApplication::translate("MainWindow", "Edytuj  Tras\304\231", nullptr));
        menuJarzabBazaDanych_v1->setTitle(QCoreApplication::translate("MainWindow", "JarzabBazaDanych", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
