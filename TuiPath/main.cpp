#include "mainwindow.h"

#include <QApplication>
#include<QMessageBox>
#include<QtSql>
#include <QSqlDatabase>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "college_connection");
    db.setDatabaseName("C:/Users/Acer/OneDrive/Desktop/TuiPath1/college_users.db");

    if (db.open()) {
        //Turn on Foreign Keys centrally
        QSqlQuery query;
        query.exec("PRAGMA foreign_keys = ON;");
    } else {
        //  show error if the file can't be opened

        QMessageBox::critical(nullptr, "Database Error", db.lastError().text());
        return -1;
    }



    MainWindow w;
    w.showMaximized();
    return a.exec();
}
