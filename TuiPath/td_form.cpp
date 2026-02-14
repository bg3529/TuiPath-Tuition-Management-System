#include "td_form.h"
#include "ui_td_form.h"
#include "teacherdashboard.h"
#include <QMessageBox>
#include <QSqlError>

td_form::td_form(const QString &Email, QWidget *parent) :
    QDialog(parent), ui(new Ui::td_form), teacherEmail(Email)
{
    ui->setupUi(this);
    initDatabase();
    initInterface();
}

td_form::~td_form() {
    delete ui;
}

void td_form::initDatabase() {
    if (!QSqlDatabase::contains("college_connection")) {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "college_connection");
        db.setDatabaseName("C:/Users/Acer/OneDrive/Desktop/TuiPath1/college_users.db");
        db.open();
    }
}

void td_form::initInterface() {
    ui->td_email->setText(teacherEmail);
    ui->td_email->setReadOnly(true);
    ui->radioScience->setChecked(true);
    ui->groupBox_5->setEnabled(false);
}

void td_form::on_radioScience_toggled(bool checked) {
    ui->Sciencesubjects->setEnabled(checked);
}

void td_form::on_radioCommerce_toggled(bool checked) {
    ui->groupBox_5->setEnabled(checked);
}

QString td_form::getSelectedSubject() {
    if (ui->radioPhysics->isChecked()) return "Physics";
    if (ui->radioChemistry->isChecked()) return "Chemistry";
    if (ui->radioMath->isChecked()) return "Math";
    if (ui->radioBiology->isChecked()) return "Biology";
    if (ui->radioBusiness->isChecked()) return "Business";
    if (ui->radioAccountancy->isChecked()) return "Accountancy";
    if (ui->radioFinance->isChecked()) return "Finance";
    if (ui->radioEconomics->isChecked()) return "Economics";
    return "";
}

bool td_form::isSubjectValidForDept(const QString &subject, const QString &dept) {
    QStringList scienceList = {"Physics", "Chemistry", "Math", "Biology"};
    QStringList commerceList = {"Business", "Accountancy", "Finance", "Economics"};
    if (dept == "Science") return scienceList.contains(subject);
    if (dept == "Commerce") return commerceList.contains(subject);
    return false;
}

void td_form::uncheckAllRadios() {
    QList<QRadioButton *> allButtons = this->findChildren<QRadioButton *>();
    for (QRadioButton *btn : allButtons) {
        btn->setAutoExclusive(false);
        btn->setChecked(false);
        btn->setAutoExclusive(true);
    }
    ui->radioScience->setChecked(true);
}

void td_form::on_add_to_schedule_clicked() {
    QString subject = getSelectedSubject();
    QString dept = ui->radioScience->isChecked() ? "Science" : "Commerce";

    if (subject.isEmpty()) {
        QMessageBox::warning(this, "Error", "Select a subject");
        return;
    }

    if (!isSubjectValidForDept(subject, dept)) {
        QMessageBox::critical(this, "Mismatch", "Subject does not match Department");
        return;
    }

    QString cls = ui->radio11->isChecked() ? "11" : "12";
    QString sec = ui->radioA->isChecked() ? "A" : "B";

    ui->listWidget->addItem(QString("%1 | %2 | %3 | %4").arg(subject, dept, cls, sec));
    uncheckAllRadios();
}

bool td_form::executeTeacherSave(QSqlQuery &query) {
    query.prepare("INSERT OR REPLACE INTO Teachers (teacher_id, Name, Email) VALUES (?, ?, ?)");
    query.addBindValue(ui->td_id->text().toInt());
    query.addBindValue(ui->td_name->text());
    query.addBindValue(teacherEmail);
    return query.exec();
}

bool td_form::executeScheduleSave(QSqlQuery &query) {
    int id = ui->td_id->text().toInt();
    for (int i = 0; i < ui->listWidget->count(); ++i) {
        QStringList parts = ui->listWidget->item(i)->text().split(" | ");
        query.prepare("INSERT INTO Teachers_Schedule (teacher_id, Subject, Department, Class, Section) VALUES (?, ?, ?, ?, ?)");
        query.addBindValue(id);
        query.addBindValue(parts[0]);
        query.addBindValue(parts[1]);
        query.addBindValue(parts[2]);
        query.addBindValue(parts[3]);
        if (!query.exec()) return false;
    }
    return true;
}

void td_form::finalizeTransition() {
    teacherdashboard *dashboard = new teacherdashboard(nullptr, teacherEmail);
    dashboard->showMaximized();
    this->close();
}

void td_form::on_save_clicked() {
    if (ui->td_id->text().isEmpty() || ui->listWidget->count() == 0) {
        QMessageBox::warning(this, "Error", "ID and Schedule required");
        return;
    }

    QSqlDatabase db = QSqlDatabase::database("college_connection");
    db.transaction();
    QSqlQuery query(db);

    if (executeTeacherSave(query) && executeScheduleSave(query)) {
        if (db.commit()) {
            QMessageBox::information(this, "Success", "Saved successfully");
            finalizeTransition();
        }
    } else {
        db.rollback();
        QMessageBox::critical(this, "Error", query.lastError().text());
    }
}
