#include "sd_settings.h"
#include "ui_sd_settings.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>

sd_settings::sd_settings(QWidget *parent, const QString &email)
    : QDialog(parent)
    , ui(new Ui::sd_settings)
    , userEmail(email.trimmed()) // Keep the C++ trim to ensure clean input
{
    ui->setupUi(this);

    // Initialization
    setupUI();
}

sd_settings::~sd_settings() {
    delete ui;
}

void sd_settings::setupUI() {
    ui->regemail->setText(userEmail);
    ui->regemail->setReadOnly(true);

    // Set input constraints for password security
    ui->regpassword_2->setEchoMode(QLineEdit::Password);
    ui->regpassword->setEchoMode(QLineEdit::Password);
    ui->regcpassword->setEchoMode(QLineEdit::Password);
}

void sd_settings::on_Changepasswordbutton_clicked() {
    const QString oldPass     = ui->regpassword_2->text();
    const QString newPass     = ui->regpassword->text();
    const QString confirmPass = ui->regcpassword->text();

    // 1. Validation Logic
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

    // 2. Database Operations
    // Accessing the specific connection name
    QSqlDatabase db = QSqlDatabase::database("college_connection");

    if (!db.isOpen()) {
        QMessageBox::critical(this, "Database Error", "Database connection is lost.");
        return;
    }

    QSqlQuery query(db);

    // SQL: Removed TRIM() for better indexing performance
    query.prepare("SELECT Password FROM users WHERE Email = :email");
    query.bindValue(":email", userEmail);

    if (!query.exec()) {
        qDebug() << "Select Error:" << query.lastError().text();
        QMessageBox::critical(this, "Error", "Database access failed.");
        return;
    }

    if (query.next()) {
        QString dbPassword = query.value(0).toString();

        // Note: Comparing plain-text passwords.
        // In a production app, you should compare hashes instead.
        if (dbPassword != oldPass) {
            QMessageBox::critical(this, "Unauthorized", "The current password you entered is incorrect.");
            return;
        }

        // 3. Update the password
        // SQL: Removed TRIM() here as well
        query.prepare("UPDATE users SET Password = :newPass WHERE Email = :email");
        query.bindValue(":newPass", newPass);
        query.bindValue(":email", userEmail);

        if (query.exec()) {
            QMessageBox::information(this, "Success", "Password updated successfully.");
            this->accept(); // Closes the dialog with an "Accepted" result
        } else {
            qDebug() << "Update Error:" << query.lastError().text();
            QMessageBox::critical(this, "Error", "Failed to update password.");
        }
    } else {
        QMessageBox::warning(this, "Error", "User record not found.");
    }
}
