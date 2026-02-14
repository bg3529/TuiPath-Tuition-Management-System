#include "td_settings.h"
#include "ui_td_settings.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>

td_settings::td_settings(QWidget *parent, const QString &email)
    : QDialog(parent)
    , ui(new Ui::td_settings)
    , teacherEmail(email.trimmed()) // Clean the input immediately
{
    ui->setupUi(this);

    // Initialization
    setupUI();
}

td_settings::~td_settings() {
    delete ui;
}

void td_settings::setupUI() {
    // Fill the email field from the passed variable
    ui->regemail->setText(teacherEmail);
    ui->regemail->setReadOnly(true);

    // Security: Ensure all password fields mask characters
    ui->regpassword_2->setEchoMode(QLineEdit::Password);
    ui->regpassword->setEchoMode(QLineEdit::Password);
    ui->regcpassword->setEchoMode(QLineEdit::Password);
}

void td_settings::on_Changepasswordbutton_clicked() {
    const QString oldPass     = ui->regpassword_2->text();
    const QString newPass     = ui->regpassword->text();
    const QString confirmPass = ui->regcpassword->text();

    // 1. Validation
    if (oldPass.isEmpty() || newPass.isEmpty() || confirmPass.isEmpty()) {
        QMessageBox::warning(this, "Input Required", "Please fill in all password fields.");
        return;
    }

    if (newPass != confirmPass) {
        QMessageBox::warning(this, "Mismatch", "New password and confirmation do not match.");
        return;
    }

    if (oldPass == newPass) {
        QMessageBox::warning(this, "No Change", "New password cannot be the same as the old password.");
        return;
    }


    QSqlDatabase db = QSqlDatabase::database("college_connection");

    if (!db.isOpen()) {
        QMessageBox::critical(this, "Database Error", "Database connection is lost.");
        return;
    }

    QSqlQuery query(db);

    // Removed TRIM() for performance and used the correct teacherEmail variable
    query.prepare("SELECT Password FROM users WHERE Email = :email");
    query.bindValue(":email", teacherEmail);

    if (!query.exec()) {
        qDebug() << "Select Error:" << query.lastError().text();
        QMessageBox::critical(this, "Error", "Database access failed.");
        return;
    }

    if (query.next()) {
        QString dbPassword = query.value(0).toString();

        // Verification
        if (dbPassword != oldPass) {
            QMessageBox::critical(this, "Unauthorized", "The current password you entered is incorrect.");
            return;
        }

        // 3. Perform the Update
        query.prepare("UPDATE users SET Password = :newPass WHERE Email = :email");
        query.bindValue(":newPass", newPass);
        query.bindValue(":email", teacherEmail);

        if (query.exec()) {
            QMessageBox::information(this, "Success", "Teacher password updated successfully.");
            this->accept();
        } else {
            qDebug() << "Update Error:" << query.lastError().text();
            QMessageBox::critical(this, "Error", "Failed to update password.");
        }
    } else {
        QMessageBox::warning(this, "Error", "Teacher record not found.");
    }
}
