#include "td_attendance.h"
#include "ui_td_attendance.h"
#include <QSqlQuery>
#include <QMessageBox>
#include <QHeaderView>

td_attendance::td_attendance(QWidget *parent, const QString &email)
    : QWidget(parent), ui(new Ui::td_attendance), teacherEmail(email) {
    ui->setupUi(this);

    ui->student_id->setReadOnly(true);
    ui->sdform_name->setReadOnly(true);
    ui->sdform_email->setReadOnly(true);

    fetchTeacherId();
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setHorizontalHeaderLabels({"ID", "Name", "Email", "Status"});
}

void td_attendance::fetchTeacherId() {
    QSqlQuery q(QSqlDatabase::database("college_connection"));
    q.prepare("SELECT teacher_id FROM Teachers WHERE Email = :e");
    q.bindValue(":e", teacherEmail);
    if (q.exec() && q.next()) teacherId = q.value(0).toInt();
}

void td_attendance::on_searchbytuitionid_textChanged(const QString &arg1) {
    ui->tableWidget->setRowCount(0);
    if (arg1.isEmpty()) return;
    QSqlQuery q(QSqlDatabase::database("college_connection"));
    q.prepare("SELECT e.student_id, s.Name, s.Email, e.Attendance_Status FROM Enrollments e "
              "JOIN Students s ON e.student_id = s.Student_Id "
              "JOIN Tuition_Classes t ON e.tuition_id = t.tuition_id "
              "WHERE e.tuition_id = :tid AND t.teacher_id = :t_id");
    q.bindValue(":tid", arg1);
    q.bindValue(":t_id", teacherId);
    if (q.exec()) {
        int r = 0;
        while (q.next()) {
            ui->tableWidget->insertRow(r);
            ui->tableWidget->setItem(r, 0, new QTableWidgetItem(q.value(0).toString()));
            ui->tableWidget->setItem(r, 1, new QTableWidgetItem(q.value(1).toString()));
            ui->tableWidget->setItem(r, 2, new QTableWidgetItem(q.value(2).toString()));
            ui->tableWidget->setItem(r, 3, new QTableWidgetItem(q.value(3).toString()));
            r++;
        }
    }
}

void td_attendance::on_tableWidget_itemClicked(QTableWidgetItem *item) {
    int row = item->row();
    ui->student_id->setText(ui->tableWidget->item(row, 0)->text());
    ui->sdform_name->setText(ui->tableWidget->item(row, 1)->text());
    ui->sdform_email->setText(ui->tableWidget->item(row, 2)->text());
    QString status = ui->tableWidget->item(row, 3)->text();
    if (status == "Present") ui->present->setChecked(true);
    else ui->absent->setChecked(true);
}

void td_attendance::on_buttonSave_clicked() {
    QString status = ui->present->isChecked() ? "Present" : "Absent";
    QSqlQuery q(QSqlDatabase::database("college_connection"));
    q.prepare("UPDATE Enrollments SET Attendance_Status = :s WHERE tuition_id = :tid AND student_id = :sid");
    q.bindValue(":s", status);
    q.bindValue(":tid", ui->searchbytuitionid->text());
    q.bindValue(":sid", ui->student_id->text());
    if (q.exec()) {
        QMessageBox::information(this, "Success", "Attendance Saved");
        on_searchbytuitionid_textChanged(ui->searchbytuitionid->text());
    }
}

td_attendance::~td_attendance() { delete ui; }
