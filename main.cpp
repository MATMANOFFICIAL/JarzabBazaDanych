#include <QApplication>
#include <QPushButton>
#include <iostream>
#include "ui_mainwindow.h" 
#include "ui_addrecordwindow.h"
#include "ui_optionswindow.h"
#include <QDialog>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QSqlRecord>
#include <QDate>
#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <ollama.hpp>


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
        std::cout << "Query failed: " << query.lastError().text().toStdString() << std::endl;
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
            std::cout << "Update failed: " << updateQuery.lastError().text().toStdString() << std::endl;
        } else {
            std::cout << "Update successful!" << std::endl;
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
        std::cout << "Delete failed: " << query.lastError().text().toStdString() << std::endl;
        std::cout << "querytask: " << query.lastQuery().toStdString() << std::endl;
    } else {
        std::cout << "Delete successful!" <<  std::endl;
    }
    QString querytask = "SELECT * FROM public.\"Wyjazdy\""; 
    showTable(ui, querytask);
}
// Funkcja do generowania SQL przez model DeepSeek-R1 (ollama)
void askOllama(const QString& prompt, std::function<void(QString)> onResult) {

    std::string sqltabeli = "CREATE TABLE IF NOT EXISTS public.\"Wyjazdy\"( \n\"ID_Wyjazdu\" integer NOT NULL GENERATED ALWAYS AS IDENTITY ( INCREMENT 1 START 1 MINVALUE 1 MAXVALUE 2147483647 CACHE 1 ), \n\"Data_Wyjazdu\" date NOT NULL, \n\"Ilosc_pasazerow\" integer, \n\"Nazwa_Klienta\" text COLLATE pg_catalog.\"default\", \n\"Godzina_Wyjazdu\" time without time zone, \ndodatkowe_informacje text COLLATE pg_catalog.\"default\", \nCONSTRAINT \"Wyjazdy_pkey\" PRIMARY KEY (\"ID_Wyjazdu\") \n) ";
    std::string systemPrompt = "You are an assistant that translates commands in Polish into SQL queries for a PostgreSQL database. You can only return a query starting with SELECT, INSERT, UPDATE or DELETE. Do not return anything that is not a plain text SQL query, do not write it in markdown (never use ```). Every Query end with ; The SQL that creates the table you are operating on is as follows: ";

    std::string fullPrompt = systemPrompt + sqltabeli + "example working query you should base yours on is SELECT * FROM public.\"Wyjazdy\". Remember to use public.\"Wyjazdy\" written exactly like that including the \" " +"\nQuestion is: " + prompt.toStdString();

    std::string result;
    try {
        // Użyj wersji z dwoma argumentami: model, prompt
        result = ollama::generate("deepseek-r1:latest", fullPrompt);
    } catch (const std::exception& e) {
        std::cout << "Ollama error: " << e.what() << std::endl;
        onResult("");
        return;
    }
    std::cout << "Ollama response: " << result << std::endl;
    //wycinanie z result wszystkiego co jest napisane po </think> nie licząc </think>
    size_t thinkEnd = result.find("</think>");
    if (thinkEnd != std::string::npos) {
        result = result.substr(thinkEnd + 8, result.size()-1); // +8 to uwzględnienie długości </think>
    }
    std::cout << "Ollama response after think: " << result << std::endl;
    

    //obcinanie result tak, aby zawierał tylko znaki znajdujące się pomiędzy SELECT a ;
    size_t start = result.find("SELECT"); //jeżeli nie znajdzie select to szuka Insert
    if (start == std::string::npos) {
        start = result.find("INSERT");
    }//jeżeli nie znajdzie insert to szuka update
    if (start == std::string::npos) {
        start = result.find("UPDATE");
    }//jeżeli nie znajdzie update to szuka delete
    if (start == std::string::npos) {
        std::cout << "Ollama response format error" << std::endl;
        onResult("");
        return;
    }
    size_t end = result.find(";", start + 5); //jeżeli nie znajdzie ; to end = ostatnia pozycja w result
    if (end == std::string::npos) {
        end = result.size();
    }
    if (start != std::string::npos && end != std::string::npos) {
        result = result.substr(start , end - start);
    } else {
        std::cout << "Ollama response format error" << std::endl;
        onResult("");
        return;
    }

    onResult(QString::fromStdString(result).trimmed());
}

int main(int argc, char *argv[]) {
    
    QApplication app(argc, argv);
    QMainWindow mainWindow; // Create a QMainWindow instance
    Ui::MainWindow ui;      // Create an instance of the UI class
    ui.setupUi(&mainWindow); // Set up the UI in the main window
  

    mainWindow.show(); // Pokazywanie głównego okna
    // łączenie z bazą danych
    connectToDatabase();
    QObject::connect(ui.wszystkietrasyguzik, &QPushButton::clicked, [&]() { // Pokazanie wszystkich tras w tabeli w GUI
        QString querytask = "SELECT * FROM public.\"Wyjazdy\"";
        showTable(ui, querytask);
    });
    
    QObject::connect(ui.dzisiejszetrasyguzik, &QPushButton::clicked, [&]() { // Pokazanie dzisiejszych tras w tabeli w GUI
        QDate today = QDate::currentDate();
        QString querytask = QString("SELECT * FROM public.\"Wyjazdy\" WHERE \"Data_Wyjazdu\" = '%1'").arg(today.toString("yyyy-MM-dd"));
        showTable(ui, querytask);
    });


    QObject::connect(ui.aiguzik, &QPushButton::clicked, [&ui]() { 
        QString polecenie = ui.aitextbox->toPlainText().trimmed();
        if (polecenie.isEmpty()) {
            ui.ailabel->setText("Wpisz polecenie w języku polskim.");
            return;
        }
        ui.ailabel->setText("Czekaj na odpowiedź AI...");
        askOllama(polecenie, [&](QString sql) {
            if (sql.isEmpty()) {
                ui.ailabel->setText("Brak odpowiedzi lub błąd AI.");
                return;
            }
            ui.ailabel->setText("Wygenerowane SQL: " + sql.left(80) + (sql.length()>80 ? "..." : ""));
            showTable(ui, sql);
        });
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

            QSqlQuery query;
            query.prepare("INSERT INTO public.\"Wyjazdy\" (\"Nazwa_Klienta\", \"Data_Wyjazdu\", \"Godzina_Wyjazdu\", \"Ilosc_pasazerow\", \"dodatkowe_informacje\") "
                          "VALUES (:nazwa_klienta, :data_wyjazdu, :godzina_wyjazdu, :ilosc_pasazerow, :dodatkowe_informacje)");
            query.bindValue(":nazwa_klienta", nazwaKlienta);
            query.bindValue(":data_wyjazdu", dataWyjazdu);
            query.bindValue(":godzina_wyjazdu", godzinaWyjazdu);
            query.bindValue(":ilosc_pasazerow", iloscPasazerow.toInt());
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

    // Obsługa guzika opcji/statystyk
    QObject::connect(ui.opcjeguzik, &QPushButton::clicked, [&]() {
        QDialog optionsDialog(&mainWindow);
        Ui::optionswindow optionsUi;
        optionsUi.setupUi(&optionsDialog);

        // ŚREDNIA ILOŚĆ PASAŻERÓW
        QObject::connect(optionsUi.sredniapasazerowguzik, &QPushButton::clicked, [&]() {
            QString sql = "SELECT AVG(\"Ilosc_pasazerow\") AS \"Średnia pasażerów\" FROM public.\"Wyjazdy\"";
            showTable(ui, sql);
            optionsDialog.accept();
        });


        // MEDIANA ILOŚCI PASAŻERÓW
        QObject::connect(optionsUi.medianailoscpasazerowguzik, &QPushButton::clicked, [&]() {
            QString sql = "SELECT PERCENTILE_CONT(0.5) WITHIN GROUP (ORDER BY \"Ilosc_pasazerow\") AS \"Mediana pasażerów\" FROM public.\"Wyjazdy\"";
            showTable(ui, sql);
            optionsDialog.accept();
        });

        // ŚREDNIA PRZEJAZDÓW NA MIESIĄC
        QObject::connect(optionsUi.sredniaprzejazdowmiesiacguzik, &QPushButton::clicked, [&]() {
            QString sql = "SELECT AVG(cnt) AS \"Średnia przejazdów/miesiąc\" FROM (SELECT COUNT(*) AS cnt FROM public.\"Wyjazdy\" GROUP BY DATE_TRUNC('month', \"Data_Wyjazdu\")) AS miesiace";
            showTable(ui, sql);
            optionsDialog.accept();
        });

        // NAJCZĘSTSZY KLIENT
        QObject::connect(optionsUi.najczestszyklientguzik, &QPushButton::clicked, [&]() {
            QString sql = "SELECT \"Nazwa_Klienta\", COUNT(*) AS \"Liczba przejazdów\" FROM public.\"Wyjazdy\" GROUP BY \"Nazwa_Klienta\" ORDER BY \"Liczba przejazdów\" DESC LIMIT 1";
            showTable(ui, sql);
            optionsDialog.accept();
        });

        // PRZEJAZD Z NAJMNIEJSZĄ LICZBĄ PASAŻERÓW
        QObject::connect(optionsUi.najmniejpasazerowguzik, &QPushButton::clicked, [&]() {
            // Najpierw znajdź minimalną liczbę pasażerów
            QSqlQuery minQuery("SELECT MIN(\"Ilosc_pasazerow\") FROM public.\"Wyjazdy\"");
            int minVal = -1;
            if (minQuery.next()) {
                minVal = minQuery.value(0).toInt();
            }
            // Wyświetl wszystkie przejazdy z tą minimalną liczbą pasażerów
            QString sql = QString("SELECT * FROM public.\"Wyjazdy\" WHERE \"Ilosc_pasazerow\" = %1").arg(minVal);
            showTable(ui, sql);
            optionsDialog.accept();
        });

        // ILOŚĆ PASAŻERÓW NA MIESIĄC
        QObject::connect(optionsUi.pasazerowienamiesiac, &QPushButton::clicked, [&]() {
            QString sql = "SELECT DATE_TRUNC('month', \"Data_Wyjazdu\") AS \"Miesiąc\", SUM(\"Ilosc_pasazerow\") AS \"Suma pasażerów\" FROM public.\"Wyjazdy\" GROUP BY \"Miesiąc\" ORDER BY \"Miesiąc\"";
            showTable(ui, sql);
            optionsDialog.accept();
        });

        // WŁASNE ZAPYTANIE SQL
        QObject::connect(optionsUi.wlasnequeryguzik, &QPushButton::clicked, [&]() {
            QString sql = optionsUi.sqlquerybox->toPlainText().trimmed();
            if (sql.isEmpty()) {
                QMessageBox::warning(&optionsDialog, "Błąd", "Wpisz zapytanie SQL.");
                return;
            }
            if (sql.trimmed().toUpper().startsWith("SELECT")) {
                showTable(ui, sql);
            } else {
                QSqlQuery query;
                if (!query.exec(sql)) {
                    QMessageBox::critical(&optionsDialog, "Błąd SQL", query.lastError().text());
                } else {
                    QMessageBox::information(&optionsDialog, "Sukces", "Zapytanie wykonane poprawnie.");
                }
            }
            optionsDialog.accept();
        });

        optionsDialog.exec();
    });

    return app.exec();
}
