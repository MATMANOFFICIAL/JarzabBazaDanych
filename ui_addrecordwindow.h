/********************************************************************************
** Form generated from reading UI file 'addrecordwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDRECORDWINDOW_H
#define UI_ADDRECORDWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QTimeEdit>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QDialogButtonBox *okanulujguzik;
    QLineEdit *nazwaklientabox;
    QDateEdit *datawyjazdubox;
    QTimeEdit *godzinawyjazdubox;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLineEdit *iloscpasazerowbox;
    QLineEdit *dodinfobox;
    QLabel *label_5;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName("Dialog");
        Dialog->resize(347, 304);
        okanulujguzik = new QDialogButtonBox(Dialog);
        okanulujguzik->setObjectName("okanulujguzik");
        okanulujguzik->setGeometry(QRect(-10, 260, 341, 32));
        okanulujguzik->setOrientation(Qt::Orientation::Horizontal);
        okanulujguzik->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);
        nazwaklientabox = new QLineEdit(Dialog);
        nazwaklientabox->setObjectName("nazwaklientabox");
        nazwaklientabox->setGeometry(QRect(150, 30, 181, 22));
        datawyjazdubox = new QDateEdit(Dialog);
        datawyjazdubox->setObjectName("datawyjazdubox");
        datawyjazdubox->setGeometry(QRect(150, 70, 171, 24));
        godzinawyjazdubox = new QTimeEdit(Dialog);
        godzinawyjazdubox->setObjectName("godzinawyjazdubox");
        godzinawyjazdubox->setGeometry(QRect(150, 110, 181, 24));
        label = new QLabel(Dialog);
        label->setObjectName("label");
        label->setGeometry(QRect(30, 30, 91, 21));
        label->setTextFormat(Qt::TextFormat::RichText);
        label->setScaledContents(false);
        label_2 = new QLabel(Dialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(30, 70, 81, 16));
        label_3 = new QLabel(Dialog);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(30, 110, 111, 16));
        label_4 = new QLabel(Dialog);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(30, 150, 111, 16));
        iloscpasazerowbox = new QLineEdit(Dialog);
        iloscpasazerowbox->setObjectName("iloscpasazerowbox");
        iloscpasazerowbox->setGeometry(QRect(150, 150, 181, 22));
        dodinfobox = new QLineEdit(Dialog);
        dodinfobox->setObjectName("dodinfobox");
        dodinfobox->setGeometry(QRect(150, 190, 181, 51));
        label_5 = new QLabel(Dialog);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(20, 190, 131, 16));

        retranslateUi(Dialog);
        QObject::connect(okanulujguzik, &QDialogButtonBox::accepted, Dialog, qOverload<>(&QDialog::accept));
        QObject::connect(okanulujguzik, &QDialogButtonBox::rejected, Dialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("Dialog", "Dodaj Tras\304\231", nullptr));
        label->setText(QCoreApplication::translate("Dialog", "Nazwa Klienta", nullptr));
        label_2->setText(QCoreApplication::translate("Dialog", "Data Wyjazdu", nullptr));
        label_3->setText(QCoreApplication::translate("Dialog", "Godzina Wyjazdu", nullptr));
        label_4->setText(QCoreApplication::translate("Dialog", "Ilosc Pasazerow", nullptr));
        label_5->setText(QCoreApplication::translate("Dialog", "Dodatkowe Informacje ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDRECORDWINDOW_H
