#include <QApplication>
#include <QPushButton>
#include <iostream>
#include "ui_mainwindow.h" 
#include "ui_addrecordwindow.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QSqlRecord>
#include <QDebug>
#include <QDate>
#include <QObject>


void connectToDatabase() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");

    db.setHostName("localhost");
    db.setPort(5432);
    db.setDatabaseName("JarzabDatabase");
    db.setUserName("postgres");
    db.setPassword("1234");

    if (!db.open()) {
        std::cout << "Failed to connect to the database:" << db.lastError().text().toStdString() << std::endl;
        return;
    }

    std::cout << "Connected to the database successfully!";
    

}

void showTable(Ui::MainWindow &ui, QString querytask){
    QSqlQuery query;
    if (!query.exec(querytask)) {
        qDebug() << "Query failed:" << query.lastError().text();
    }
    
    int columnCount = query.record().count();
    ui.tabela->setColumnCount(columnCount);
    ui.tabela->setRowCount(0);
    
    for (int i = 0; i < columnCount; ++i) {
        ui.tabela->setHorizontalHeaderItem(i, new QTableWidgetItem(query.record().fieldName(i)));
    }
    
    int row = 0;
    while (query.next()) {
        ui.tabela->insertRow(row);
        for (int col = 0; col < columnCount; ++col) {
            ui.tabela->setItem(row, col, new QTableWidgetItem(query.value(col).toString()));
        }
        ++row;
}
}




int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QMainWindow mainWindow; // Create a QMainWindow instance
    Ui::MainWindow ui;      // Create an instance of the UI class
    ui.setupUi(&mainWindow); // Set up the UI in the main window
  

    mainWindow.show(); // Show the main window
    // Connect to the database
    connectToDatabase();
    // Populate the table with data
    QObject::connect(ui.wszystkietrasyguzik, &QPushButton::clicked, [&]() {
        QString querytask = "SELECT * FROM public.\"Wyjazdy\"";
        showTable(ui, querytask);
    });
    
    QObject::connect(ui.dzisiejszetrasyguzik, &QPushButton::clicked, [&]() {
        QDate today = QDate::currentDate();
        QString querytask = QString("SELECT * FROM public.\"Wyjazdy\" WHERE \"Data_Wyjazdu\" = '%1'").arg(today.toString("yyyy-MM-dd"));
        showTable(ui, querytask);
    });

    QObject::connect(ui.dodajtraseguzik, &QPushButton::clicked, [&]() {
        // Create and show the add record window
        QDialog *addRecordWindow = new QDialog(&mainWindow);
        Ui::Dialog addRecordUi;
        addRecordUi.setupUi(addRecordWindow);
        
        // Connect the button to add a record
        QObject::connect(addRecordUi.okanulujguzik, &QDialogButtonBox::accepted, [=]() {
            QString nazwaKlienta = addRecordUi.nazwaklientabox->text();
            QString dataWyjazdu = addRecordUi.datawyjazdubox->date().toString("yyyy-MM-dd");
            QString godzinaWyjazdu = addRecordUi.godzinawyjazdubox->time().toString("HH:mm:ss");
            QString iloscPasazerow = addRecordUi.iloscpasazerowbox->text();
            QString dodatkoweInfo = addRecordUi.dodinfobox->text();

            // Insert the new record into the database
            QSqlQuery query;
            query.prepare("INSERT INTO public.\"Wyjazdy\" (\"Nazwa_Klienta\", \"Data_Wyjazdu\", \"Godzina_Wyjazdu\", \"Ilosc_Pasazerow\", \"Dodatkowe_Informacje\") "
                          "VALUES (:nazwa_klienta, :data_wyjazdu, :godzina_wyjazdu, :ilosc_pasazerow, :dodatkowe_informacje)");
            query.bindValue(":nazwa_klienta", nazwaKlienta);
            query.bindValue(":data_wyjazdu", dataWyjazdu);
            query.bindValue(":godzina_wyjazdu", godzinaWyjazdu);
            query.bindValue(":ilosc_pasazerow", iloscPasazerow);
            query.bindValue(":dodatkowe_informacje", dodatkoweInfo);

            if (!query.exec()) {
                qDebug() << "Insert failed:" << query.lastError().text();
            } else {
                qDebug() << "Insert successful!";
                // Refresh the table
                //showTable(ui, "SELECT * FROM public.\"Wyjazdy\"");
                addRecordWindow->accept(); // Close the dialog only after successful insertion
            }
        });

        addRecordWindow->exec(); // Show the dialog modally

    });
      
    QObject::connect(ui.usuntraseguzik, &QPushButton::clicked, [&]() {
        QString querytask = "DELETE FROM public.\"Wyjazdy\" WHERE \"Id\" = 1";
        QSqlQuery query;
        if (!query.exec(querytask)) {
            qDebug() << "Delete failed:" << query.lastError().text();
        } else {
            qDebug() << "Delete successful!";
        }
    });
    QObject::connect(ui.edytujtraseguzik, &QPushButton::clicked, [&]() {
        QDate today = QDate::currentDate();
        QString querytask = QString("UPDATE public.\"Wyjazdy\" SET \"Nazwa_Klienta\" = 'Safran transmissions poland', \"Data_Wyjazdu\" = '%1', \"Godzina_Wyjazdu\" = '12:00:00', \"Ilosc_Pasazerow\" = 2, \"Dodatkowe_Informacje\" = 'Brak dodatkowych informacji' WHERE \"Id\" = 1").arg(today.toString("yyyy-MM-dd"));
        
        QSqlQuery query;
        query.exec(querytask);
    });
    

    return app.exec();
}
