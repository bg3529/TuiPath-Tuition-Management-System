#include "sd_profile.h"
#include "ui_sd_profile.h"
#include <QSqlTableModel>
#include <QtSql>
#include <QMessageBox>
#include <QDebug>

sd_profile::sd_profile(QWidget *parent, QString Email)
    : QDialog(parent)
    , ui(new Ui::sd_profile)
{
    ui->setupUi(this);

    DB_Connection = QSqlDatabase::database("college_connection");

    // Email is read-only because it links the tables
    ui->sdupdateprofile_email->setReadOnly(true);

    displayStudentInfo(Email);
}

sd_profile::~sd_profile()
{
    delete ui;
}

// --- EDITING PART COMMENTED OUT ---
/*
void sd_profile::on_editbutton_clicked()
{
    ui->profiledetails->setCurrentWidget(ui->updatedetail);
}
*/

void sd_profile::displayStudentInfo(QString userEmail)
{
    QSqlQuery query(DB_Connection);
    query.prepare("SELECT Name, Email, Student_Id, Department, Class, Section FROM Students WHERE Email = :email");
    query.bindValue(":email", userEmail);

    if (query.exec()) {
        if (query.next()) {
            // Display labels (View Mode)
            ui->name_sdprofile->setText(query.value("Name").toString());
            ui->email_sdprofile->setText(query.value("Email").toString());
            ui->id_sdprofile->setText(query.value("Student_Id").toString());
            ui->dept_sdprofile->setText(query.value("Department").toString());
            ui->class_sdprofile->setText(query.value("Class").toString());
            ui->section_sdprofile->setText(query.value("Section").toString());

            // Fill edit fields (Keeping these ready but the user won't reach them)
            ui->sdupdateprofile_email->setText(query.value("Email").toString());
            ui->sdupdateprofile_name->setText(query.value("Name").toString());
            ui->sdupdateprofile_id->setText(query.value("Student_Id").toString());
            ui->sdupdateprofile_dept->setCurrentText(query.value("Department").toString());
            ui->sdupdateprofile_class->setCurrentText(query.value("Class").toString());
            ui->sdupdateprofile_section->setCurrentText(query.value("Section").toString());

            ui->profiledetails->setCurrentWidget(ui->studentdetails);
        } else {
            QMessageBox::information(this, "Not Found", "No student record exists for: " + userEmail);
        }
    } else {
        qDebug() << "SQL Error:" << query.lastError().text();
    }
}

void sd_profile::on_backButton_clicked()
{
    ui->profiledetails->setCurrentWidget(ui->studentdetails);
}

// --- UPDATE LOGIC COMMENTED OUT ---
/*
void sd_profile::on_cancelbutton_clicked()
{
    displayStudentInfo(ui->sdupdateprofile_email->text());
    ui->profiledetails->setCurrentWidget(ui->studentdetails);
}

void sd_profile::on_savebutton_clicked()
{
    QString email = ui->sdupdateprofile_email->text();
    int id = ui->sdupdateprofile_id->text().toInt();
    QString name = ui->sdupdateprofile_name->text();
    QString department = ui->sdupdateprofile_dept->currentText();
    int className = ui->sdupdateprofile_class->currentText().toInt();
    QString section = ui->sdupdateprofile_section->currentText();

    if (name.isEmpty() || id <= 0 || className <= 0) {
        QMessageBox::warning(this, "Input Error", "Please fill all fields correctly.");
        return;
    }

    if (helpfulfunctions::updateStudentData(email, id, name, department, className, section)) {
        QMessageBox::information(this, "Success", "Details updated!");
        this->accept();
    } else {
        QMessageBox::critical(this, "Error", "Update failed.");
    }
}
*/
