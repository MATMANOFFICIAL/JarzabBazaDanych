/********************************************************************************
** Form generated from reading UI file 'optionswindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPTIONSWINDOW_H
#define UI_OPTIONSWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_optionswindow
{
public:
    QPushButton *sredniapasazerowguzik;
    QPushButton *medianailoscpasazerowguzik;
    QPushButton *sredniaprzejazdowmiesiacguzik;
    QPushButton *najczestszyklientguzik;
    QPushButton *najmniejpasazerowguzik;
    QPushButton *pasazerowienamiesiac;
    QPushButton *wlasnequeryguzik;
    QTextEdit *sqlquerybox;
    QLabel *label;

    void setupUi(QDialog *optionswindow)
    {
        if (optionswindow->objectName().isEmpty())
            optionswindow->setObjectName("optionswindow");
        optionswindow->resize(409, 348);
        sredniapasazerowguzik = new QPushButton(optionswindow);
        sredniapasazerowguzik->setObjectName("sredniapasazerowguzik");
        sredniapasazerowguzik->setGeometry(QRect(10, 10, 251, 31));
        medianailoscpasazerowguzik = new QPushButton(optionswindow);
        medianailoscpasazerowguzik->setObjectName("medianailoscpasazerowguzik");
        medianailoscpasazerowguzik->setGeometry(QRect(10, 50, 251, 31));
        sredniaprzejazdowmiesiacguzik = new QPushButton(optionswindow);
        sredniaprzejazdowmiesiacguzik->setObjectName("sredniaprzejazdowmiesiacguzik");
        sredniaprzejazdowmiesiacguzik->setGeometry(QRect(10, 90, 251, 31));
        najczestszyklientguzik = new QPushButton(optionswindow);
        najczestszyklientguzik->setObjectName("najczestszyklientguzik");
        najczestszyklientguzik->setGeometry(QRect(10, 130, 251, 31));
        najmniejpasazerowguzik = new QPushButton(optionswindow);
        najmniejpasazerowguzik->setObjectName("najmniejpasazerowguzik");
        najmniejpasazerowguzik->setGeometry(QRect(10, 170, 251, 31));
        pasazerowienamiesiac = new QPushButton(optionswindow);
        pasazerowienamiesiac->setObjectName("pasazerowienamiesiac");
        pasazerowienamiesiac->setGeometry(QRect(10, 210, 251, 31));
        wlasnequeryguzik = new QPushButton(optionswindow);
        wlasnequeryguzik->setObjectName("wlasnequeryguzik");
        wlasnequeryguzik->setGeometry(QRect(290, 270, 111, 71));
        sqlquerybox = new QTextEdit(optionswindow);
        sqlquerybox->setObjectName("sqlquerybox");
        sqlquerybox->setGeometry(QRect(0, 270, 281, 71));
        label = new QLabel(optionswindow);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 240, 241, 31));

        retranslateUi(optionswindow);

        QMetaObject::connectSlotsByName(optionswindow);
    } // setupUi

    void retranslateUi(QDialog *optionswindow)
    {
        optionswindow->setWindowTitle(QCoreApplication::translate("optionswindow", "Wybierz Co chcesz wy\305\233wietli\304\207 ", nullptr));
        sredniapasazerowguzik->setText(QCoreApplication::translate("optionswindow", "\305\232rednia ilo\305\233\304\207 pasa\305\274er\303\263w", nullptr));
        medianailoscpasazerowguzik->setText(QCoreApplication::translate("optionswindow", "Mediana ilo\305\233ci pasa\305\274er\303\263w", nullptr));
        sredniaprzejazdowmiesiacguzik->setText(QCoreApplication::translate("optionswindow", "\305\232rednia ilo\305\233\304\207 przejazd\303\263w na miesi\304\205c", nullptr));
        najczestszyklientguzik->setText(QCoreApplication::translate("optionswindow", "Najcz\304\231stszy klient", nullptr));
        najmniejpasazerowguzik->setText(QCoreApplication::translate("optionswindow", "Przejazd z najmniejsz\304\205 ilo\305\233ci\304\205 pasa\305\274er\303\263w", nullptr));
        pasazerowienamiesiac->setText(QCoreApplication::translate("optionswindow", "Ilo\305\233\304\207 pasa\305\274er\303\263w na miesiac", nullptr));
        wlasnequeryguzik->setText(QCoreApplication::translate("optionswindow", "Wy\305\233lij", nullptr));
        label->setText(QCoreApplication::translate("optionswindow", "Wpisz w\305\202asne zapytanie SQL:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class optionswindow: public Ui_optionswindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPTIONSWINDOW_H
