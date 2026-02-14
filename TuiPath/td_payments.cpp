#include "td_payments.h"
#include "ui_td_payments.h"
#include <QSqlQuery>
#include <QMessageBox>
#include <QHeaderView>

td_payments::td_payments(QWidget *parent, const QString &email)
    : QWidget(parent), ui(new Ui::td_payments), teacherEmail(email) {
    ui->setupUi(this);
    fetchTeacherId();

    ui->student_id->setReadOnly(true);
    ui->sdform_name->setReadOnly(true);
    ui->sdform_email->setReadOnly(true);

    // Table setup: Full width and 4 columns
    ui->enrolledstudentstable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->enrolledstudentstable->setColumnCount(4);
    ui->enrolledstudentstable->setHorizontalHeaderLabels({"ID", "Name", "Email", "Payment"});
}

void td_payments::fetchTeacherId() {
    QSqlQuery q(QSqlDatabase::database("college_connection"));
    q.prepare("SELECT teacher_id FROM Teachers WHERE Email = :e");
    q.bindValue(":e", teacherEmail);
    if (q.exec() && q.next()) teacherId = q.value(0).toInt();
}

void td_payments::on_Searchtuitionid_textChanged(const QString &arg1) {
    ui->enrolledstudentstable->setRowCount(0);
    if (arg1.isEmpty()) return;

    QSqlQuery q(QSqlDatabase::database("college_connection"));
    q.prepare("SELECT e.student_id, s.Name, s.Email, e.Payment_Status FROM Enrollments e "
              "JOIN Students s ON e.student_id = s.Student_Id "
              "JOIN Tuition_Classes t ON e.tuition_id = t.tuition_id "
              "WHERE e.tuition_id = :tid AND t.teacher_id = :t_id");
    q.bindValue(":tid", arg1);
    q.bindValue(":t_id", teacherId);

    if (q.exec()) {
        int r = 0;
        while (q.next()) {
            ui->enrolledstudentstable->insertRow(r);
            ui->enrolledstudentstable->setItem(r, 0, new QTableWidgetItem(q.value(0).toString()));
            ui->enrolledstudentstable->setItem(r, 1, new QTableWidgetItem(q.value(1).toString()));
            ui->enrolledstudentstable->setItem(r, 2, new QTableWidgetItem(q.value(2).toString())); // Email column
            ui->enrolledstudentstable->setItem(r, 3, new QTableWidgetItem(q.value(3).toString())); // Status column
            r++;
        }
    }
}

void td_payments::on_enrolledstudentstable_itemClicked(QTableWidgetItem *item) {
    int row = item->row();
    // Maps table data to the side form fields
    ui->student_id->setText(ui->enrolledstudentstable->item(row, 0)->text());
    ui->sdform_name->setText(ui->enrolledstudentstable->item(row, 1)->text());
    ui->sdform_email->setText(ui->enrolledstudentstable->item(row, 2)->text()); // Auto-fills Email

    QString pay = ui->enrolledstudentstable->item(row, 3)->text();
    if (pay == "Paid") ui->paidradiobutton->setChecked(true);
    else ui->notpaidradiobutton->setChecked(true);
}

void td_payments::on_buttonSave_clicked() {
    QString payStatus = ui->paidradiobutton->isChecked() ? "Paid" : "Not Paid";
    QSqlQuery q(QSqlDatabase::database("college_connection"));
    q.prepare("UPDATE Enrollments SET Payment_Status = :p WHERE tuition_id = :tid AND student_id = :sid");
    q.bindValue(":p", payStatus);
    q.bindValue(":tid", ui->Searchtuitionid->text());
    q.bindValue(":sid", ui->student_id->text());

    if (q.exec()) {
        QMessageBox::information(this, "Success", "Payment Updated");
        on_Searchtuitionid_textChanged(ui->Searchtuitionid->text()); // Refresh table
    }
}

td_payments::~td_payments() { delete ui; }
