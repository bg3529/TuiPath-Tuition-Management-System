#include "sd_form.h"
#include "studentdashboard.h"
#include "ui_sd_form.h"
#include "helpfulfunctions.h"
#include <QMessageBox>
#include <QDebug>

sd_form::sd_form(QWidget *parent, QString email)
    : QDialog(parent)
    , ui(new Ui::sd_form)
    , userEmail(email)
{
    ui->setupUi(this);
    ui->sdform_email->setText(userEmail);
    ui->sdform_email->setReadOnly(true);
}

void sd_form::on_buttonSave_clicked()
{
    int id = ui->student_id->text().toInt();
    QString name = ui->sdform_name->text();
    QString department = ui->sdform_dept->currentText();
    int className = ui->sdform_class->currentText().toInt();
    QString section = ui->sdform_section->currentText();

    if (name.isEmpty() || id <= 0 || className <= 0) {
        QMessageBox::warning(this, "Input Error", "Please fill all fields correctly.");
        return;
    }

    if (helpfulfunctions::updateStudentData(userEmail, id, name, department, className, section)) {
        qDebug() << "Student data updated successfully!";
        studentdashboard *studentDash = new studentdashboard(nullptr, userEmail);
        studentDash->showMaximized();
        this->close();
    } else {
        QMessageBox::critical(this, "Error", "Failed to update student data.");
    }
}

sd_form::~sd_form()
{
    delete ui;
}
