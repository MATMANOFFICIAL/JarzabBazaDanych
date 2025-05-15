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

void editRecord(const QString &id, Ui::MainWindow &ui) {
    QDialog editDialog;
    Ui::Dialog editRecordUi;
    editRecordUi.setupUi(&editDialog);

    // Pobierz dane rekordu z bazy danych
    QSqlQuery query;
    query.prepare("SELECT * FROM public.\"Wyjazdy\" WHERE \"ID_Wyjazdu\" = :id");
    query.bindValue(":id", id);
    if (query.exec() && query.next()) {
        editRecordUi.nazwaklientabox->setText(query.value("Nazwa_Klienta").toString());
        editRecordUi.datawyjazdubox->setDate(query.value("Data_Wyjazdu").toDate());
        editRecordUi.godzinawyjazdubox->setTime(query.value("Godzina_Wyjazdu").toTime());
        editRecordUi.iloscpasazerowbox->setText(query.value("Ilosc_Pasazerow").toString());
        editRecordUi.dodinfobox->setText(query.value("Dodatkowe_Informacje").toString());
    }

    // Obsługa zapisania zmian
    QObject::connect(editRecordUi.okanulujguzik, &QDialogButtonBox::accepted, [&]() {
        QString nazwaKlienta = editRecordUi.nazwaklientabox->text();
        QString dataWyjazdu = editRecordUi.datawyjazdubox->date().toString("yyyy-MM-dd");
        QString godzinaWyjazdu = editRecordUi.godzinawyjazdubox->time().toString("HH:mm:ss");
        QString iloscPasazerow = editRecordUi.iloscpasazerowbox->text();
        QString dodatkoweInfo = editRecordUi.dodinfobox->text();

        QSqlQuery updateQuery;
        updateQuery.prepare("UPDATE public.\"Wyjazdy\" SET \"Nazwa_Klienta\" = :nazwa_klienta, \"Data_Wyjazdu\" = :data_wyjazdu, \"Godzina_Wyjazdu\" = :godzina_wyjazdu, \"Ilosc_pasazerow\" = :ilosc_pasazerow, \"dodatkowe_informacje\" = :dodatkowe_informacje WHERE \"ID_Wyjazdu\" = :id");
        updateQuery.bindValue(":nazwa_klienta", nazwaKlienta);
        updateQuery.bindValue(":data_wyjazdu", dataWyjazdu);
        updateQuery.bindValue(":godzina_wyjazdu", godzinaWyjazdu);
        updateQuery.bindValue(":ilosc_pasazerow", iloscPasazerow.toInt());
        updateQuery.bindValue(":dodatkowe_informacje", dodatkoweInfo);
        updateQuery.bindValue(":id", id);

        if (!updateQuery.exec()) {
            qDebug() << "Update failed:" << updateQuery.lastError().text();
        } else {
            qDebug() << "Update successful!";
        }
         QString querytask = "SELECT * FROM public.\"Wyjazdy\""; 
        showTable(ui, querytask);
    });
    editDialog.exec();
}
void deleteRecord(const QString &id, Ui::MainWindow &ui) {
    QSqlQuery query;
    query.prepare("DELETE FROM public.\"Wyjazdy\" WHERE \"ID_Wyjazdu\" = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        std::cout << "Delete failed:" << query.lastError().text().toStdString() << std::endl;
        std::cout<< "querytask: " << query.lastQuery().toStdString() << std::endl;
    } else {
        std::cout << "Delete successful!" <<  std::endl;
    }
    QString querytask = "SELECT * FROM public.\"Wyjazdy\""; 
    showTable(ui, querytask);
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
        QObject::connect(addRecordUi.okanulujguzik, &QDialogButtonBox::accepted, [=, &ui]() {
            QString nazwaKlienta = addRecordUi.nazwaklientabox->text();
            QString dataWyjazdu = addRecordUi.datawyjazdubox->date().toString("yyyy-MM-dd");
            QString godzinaWyjazdu = addRecordUi.godzinawyjazdubox->time().toString("HH:mm:ss");
            QString iloscPasazerow = addRecordUi.iloscpasazerowbox->text();
            QString dodatkoweInfo = addRecordUi.dodinfobox->text();
            std::cout << "Nazwa Klienta: " << nazwaKlienta.toStdString() << std::endl;

            // Przygotowanie zapytania SQL z użyciem konkatenacji ciągów
            QSqlQuery query;
            query.prepare("INSERT INTO public.\"Wyjazdy\" (\"Nazwa_Klienta\", \"Data_Wyjazdu\", \"Godzina_Wyjazdu\", \"Ilosc_pasazerow\", \"dodatkowe_informacje\") "
                          "VALUES (:nazwa_klienta, :data_wyjazdu, :godzina_wyjazdu, :ilosc_pasazerow, :dodatkowe_informacje)");
            query.bindValue(":nazwa_klienta", nazwaKlienta);
            query.bindValue(":data_wyjazdu", dataWyjazdu);
            query.bindValue(":godzina_wyjazdu", godzinaWyjazdu);
            query.bindValue(":ilosc_pasazerow", iloscPasazerow.toInt()); // Konwersja na liczbę
            query.bindValue(":dodatkowe_informacje", dodatkoweInfo);
           
            if (!query.exec()) {
                std::cout << "Insert failed:" << query.lastError().text().toStdString() << std::endl;
            } else {
                std::cout << "Insert successful!" << std::endl;
                
                addRecordWindow->accept(); // Zamknięcie okna dialogowego po udanym dodaniu
            }
            QString querytask = "SELECT * FROM public.\"Wyjazdy\""; 
            showTable(ui, querytask);
        });
        
        addRecordWindow->exec(); // Show the dialog modally

    });

    
        QObject::connect(ui.tabela, &QTableWidget::customContextMenuRequested, [&]() {
        QTableWidgetItem *item = ui.tabela->itemAt(ui.tabela->viewport()->mapFromGlobal(QCursor::pos()));
        if (!item) return;
    
        int row = item->row();
        int column = item->column();
    
        // Sprawdź, czy kliknięto kolumnę ID
        if (column == 0) { // Zakładamy, że kolumna ID to pierwsza kolumna
            QMenu contextMenu;
            QAction *editAction = contextMenu.addAction("Edytuj");
            QAction *deleteAction = contextMenu.addAction("Usuń");
    
            QAction *selectedAction = contextMenu.exec(QCursor::pos());
            if (selectedAction == editAction) {
                // Wywołaj funkcję edycji
                QString id = ui.tabela->item(row, column)->text();
                editRecord(id, ui);
            } else if (selectedAction == deleteAction) {
                // Wywołaj funkcję usuwania
                QString id = ui.tabela->item(row, column)->text();
                deleteRecord(id, ui);
            }
        }
    });
    return app.exec();
}
