#include "registter.h"
#include "login.h"
#include "ui_registter.h"
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>
#include <QDir>
#include <QCoreApplication>

registter::registter(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::registter)
{
    ui->setupUi(this);


    DB_Connection = DB_Connection = QSqlDatabase::database("college_connection");


    if (!QFile::exists("C:/Users/Acer/OneDrive/Desktop/TuiPath1/college_users.db")) {
        QMessageBox::warning(this, "Warning", "Database file not found!");
    }
}


registter::~registter()
{
    delete ui;
}


void registter::on_pushButton_3_clicked()
{

    if (!DB_Connection.open()) {
        QMessageBox::critical(this, "Error", DB_Connection.lastError().text());
        return;
    }

    DB_Connection.transaction();

    QSqlQuery QueryInsertData(DB_Connection);
    QueryInsertData.prepare("INSERT INTO users(Full_Name, Email, Role, Password) "
                            "VALUES(:Full_Name, :Email, :Role, :Password)");
    QueryInsertData.bindValue(":Full_Name", ui->regfullname->text());
    QueryInsertData.bindValue(":Email", ui->regemail->text());
    QueryInsertData.bindValue(":Role", ui->regrole->currentText());
    QueryInsertData.bindValue(":Password", ui->regpassword->text());

    if (QueryInsertData.exec()) {
        QMessageBox::information(this, "Success", "Account created successfully!");
        DB_Connection.commit();
    } else {
        QMessageBox::critical(this, "Error", QueryInsertData.lastError().text());
        DB_Connection.rollback();
    }

    DB_Connection.close();
}




void registter::on_reg_login_clicked()
{
    auto loginWindow = new login(this);
    loginWindow->showMaximized();
     this->hide();
}

