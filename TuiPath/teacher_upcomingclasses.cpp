#include "teacher_upcomingclasses.h"
#include "ui_teacher_upcomingclasses.h"
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>

Teacher_upcomingclasses::Teacher_upcomingclasses(QWidget *parent)
    : QWidget(parent), ui(new Ui::Teacher_upcomingclasses)
{
    ui->setupUi(this);
}

void Teacher_upcomingclasses::setData(const QString &tuitionId) {
    m_tuitionId = tuitionId;
    loadUIData();
}

void Teacher_upcomingclasses::loadUIData() {
    QSqlQuery query(QSqlDatabase::database("college_connection"));
    query.prepare("SELECT Title, Subject, Class, Section, Department, Description, Date_held, Time_held "
                  "FROM Tuition_Classes WHERE tuition_id = :id");
    query.bindValue(":id", m_tuitionId);

    if (query.exec() && query.next()) {
        ui->tuitionName->setText(query.value("Title").toString());
        ui->tuitionid->setText("ID: " + m_tuitionId);
        ui->classsecdepatmentdetails->setText(QString("%1 | %2-%3 (%4)")
                                                  .arg(query.value("Subject").toString(), query.value("Class").toString(),
                                                       query.value("Section").toString(), query.value("Department").toString()));
        ui->Schedule->setText(query.value("Date_held").toString() + " @ " + query.value("Time_held").toString());
        ui->Description->setText(query.value("Description").toString());
    }
}

void Teacher_upcomingclasses::on_deleteclass_clicked() {
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Confirm Delete",
                                                              "Are you sure you want to delete this class?",
                                                              QMessageBox::Yes|QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        QSqlQuery query(QSqlDatabase::database("college_connection"));
        query.prepare("DELETE FROM Tuition_Classes WHERE tuition_id = :id");
        query.bindValue(":id", m_tuitionId);

        if (query.exec()) {
            emit classDeleted(); // Tell dashboard to refresh the list
        }
    }
}

Teacher_upcomingclasses::~Teacher_upcomingclasses() { delete ui; }
