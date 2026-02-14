#include "admindashboard_teachers.h"
#include "ui_admindashboard_teachers.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>

admindashboard_teachers::admindashboard_teachers(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::admindashboard_teachers)
{
    ui->setupUi(this);

    // 1. Initialize Table Structure (Critical for visibility)
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setHorizontalHeaderLabels({"Teacher ID", "Full Name", "Email Address"});
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // 2. Load Initial Data
    refreshTable();
}

admindashboard_teachers::~admindashboard_teachers() {
    delete ui;
}

// =============================================================================
// DATA DISPLAY & REFRESH
// =============================================================================

void admindashboard_teachers::refreshTable(const QString &filter) {
    QSqlDatabase db = QSqlDatabase::database("college_connection");

    if (!db.isOpen()) {
        qDebug() << "Database connection not found!";
        return;
    }

    QSqlQuery query(db);
    QString sql = "SELECT teacher_id, Name, Email FROM Teachers";
    if (!filter.isEmpty()) sql += filter;

    ui->tableWidget->setRowCount(0); // Clear current contents

    if (query.exec(sql)) {
        while (query.next()) {
            int row = ui->tableWidget->rowCount();
            ui->tableWidget->insertRow(row);

            ui->tableWidget->setItem(row, 0, new QTableWidgetItem(query.value(0).toString()));
            ui->tableWidget->setItem(row, 1, new QTableWidgetItem(query.value(1).toString()));
            ui->tableWidget->setItem(row, 2, new QTableWidgetItem(query.value(2).toString()));
        }
    } else {
        qDebug() << "Query Error:" << query.lastError().text();
    }
}

void admindashboard_teachers::on_tableWidget_cellClicked(int row, int) {
    // Fill the input fields when a row is selected
    ui->td_id->setText(ui->tableWidget->item(row, 0)->text());
    ui->td_name->setText(ui->tableWidget->item(row, 1)->text());
    ui->td_email->setText(ui->tableWidget->item(row, 2)->text());
}

// =============================================================================
// CRUD OPERATIONS
// =============================================================================

void admindashboard_teachers::on_addateache_clicked() {
    QSqlDatabase db = QSqlDatabase::database("college_connection");
    db.transaction();
    QSqlQuery q(db);

    // Insert into Teachers table
    q.prepare("INSERT INTO Teachers (teacher_id, Name, Email) VALUES (?, ?, ?)");
    q.addBindValue(ui->td_id->text().toInt());
    q.addBindValue(ui->td_name->text());
    q.addBindValue(ui->td_email->text());

    if (q.exec()) {
        // Create matching login credentials with default password
        q.prepare("INSERT INTO users (Email, Password, Role) VALUES (?, 'teacher123', 'Teacher')");
        q.addBindValue(ui->td_email->text());

        if (q.exec() && db.commit()) {
            QMessageBox::information(this, "Success", "Teacher added successfully.");
            refreshTable();
            clearForm();
        } else {
            db.rollback();
            QMessageBox::critical(this, "Error", "Failed to create user login.");
        }
    } else {
        db.rollback();
        QMessageBox::critical(this, "Error", "Failed to add teacher: " + q.lastError().text());
    }
}

void admindashboard_teachers::on_saveteacherbutton_clicked() {
    QSqlQuery q(QSqlDatabase::database("college_connection"));
    // Update existing teacher details
    q.prepare("UPDATE Teachers SET Name = ?, teacher_id = ? WHERE Email = ?");
    q.addBindValue(ui->td_name->text());
    q.addBindValue(ui->td_id->text().toInt());
    q.addBindValue(ui->td_email->text());

    if (q.exec()) {
        QMessageBox::information(this, "Success", "Teacher details updated.");
        refreshTable();
    } else {
        QMessageBox::critical(this, "Error", "Update failed: " + q.lastError().text());
    }
}

void admindashboard_teachers::on_deleteteacher_clicked() {
    if (QMessageBox::question(this, "Confirm Deletion", "Are you sure you want to remove this teacher?") == QMessageBox::Yes) {
        QSqlDatabase db = QSqlDatabase::database("college_connection");
        db.transaction();
        QSqlQuery q(db);
        QString email = ui->td_email->text();

        // Delete from both tables to maintain integrity
        q.prepare("DELETE FROM Teachers WHERE Email = ?");
        q.addBindValue(email);
        q.exec();

        q.prepare("DELETE FROM users WHERE Email = ?");
        q.addBindValue(email);

        if (q.exec() && db.commit()) {
            refreshTable();
            clearForm();
            QMessageBox::information(this, "Deleted", "Teacher removed from system.");
        } else {
            db.rollback();
            QMessageBox::critical(this, "Error", "Delete failed.");
        }
    }
}

// =============================================================================
// SEARCH & UTILS
// =============================================================================

void admindashboard_teachers::on_searchbyteacherid_textChanged(const QString &arg1) {
    refreshTable(QString(" WHERE teacher_id LIKE '%1%'").arg(arg1));
}

void admindashboard_teachers::on_searchbyteacheremail_textChanged(const QString &arg1) {
    refreshTable(QString(" WHERE Email LIKE '%%1%'").arg(arg1));
}

void admindashboard_teachers::clearForm() {
    ui->td_id->clear();
    ui->td_name->clear();
    ui->td_email->clear();
}
