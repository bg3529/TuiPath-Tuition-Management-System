#include "login.h"
#include "admindashboard.h"
#include "registter.h"
#include "sd_form.h"
#include "td_form.h"
#include "studentdashboard.h"
#include "teacherdashboard.h"
#include "ui_login.h"
#include "helpfulfunctions.h"
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>
#include <QFile>

login::login(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::login)
{
    ui->setupUi(this);
    DB_Connection = QSqlDatabase::database("college_connection");

    if (!QFile::exists("C:/Users/Acer/OneDrive/Desktop/TuiPath1/college_users.db")) {
        QMessageBox::warning(this, "Warning", "Database file not found!");
    }
}

login::~login()
{
    delete ui;
}

void login::on_login_loginpage_clicked()
{
    QString email = ui->email_loginpage->text();
    QString password = ui->Password_loginpage->text();

    if (DB_Connection.open()) {
        QSqlQuery query(DB_Connection);
        query.prepare("SELECT Email, Role FROM users WHERE Email = :Email AND Password = :Password");
        query.bindValue(":Email", email);
        query.bindValue(":Password", password);

        if (query.exec() && query.next()) {
            QString userEmail = query.value("Email").toString();
            QString role = query.value("Role").toString().toLower();

            if (role == "student") {
                helpfulfunctions::syncStudentEmail(userEmail);

                if (helpfulfunctions::isProfileIncomplete(userEmail)) {
                    this->hide();
                    sd_form *form = new sd_form(nullptr,userEmail);
                    form->showMaximized();
                }
                else {
                    this->hide();
                    studentdashboard *studentDash = new studentdashboard(nullptr,userEmail);
                    studentDash->showMaximized();
                }

            } else if (role == "teacher") {
                helpfulfunctions::syncTeacherEmail(userEmail);

                if (helpfulfunctions::isTeacherProfileIncomplete(userEmail)) {
                    this->hide();
                    td_form *form = new td_form(userEmail, nullptr);
                    form->show();
                } else {
                    this->hide();
                    teacherdashboard *dash = new teacherdashboard(nullptr,userEmail);
                    dash->showMaximized();
                }

            }else if (role == "admin") {
                // ADMIN LOGIC HERE
                admindashboard *adminDash = new admindashboard();
                adminDash->showMaximized();}
            else {
                QMessageBox::warning(this, "Login", "Unknown role detected.");
            }
        } else {
            QMessageBox::warning(this, "Login", "Invalid username or password.");
        }
    } else {
        QMessageBox::critical(this, "Database Error", DB_Connection.lastError().text());
    }
}

void login::on_register_loginpage_clicked()
{
    auto registterWindow = new registter(this);
    registterWindow->showMaximized();
     this->hide();
}
