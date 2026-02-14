#include "admindashboard_students.h"
#include "ui_admindashboard_students.h"
#include "helpfulfunctions.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>

admindashboard_students::admindashboard_students(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::admindashboard_students)
{
    ui->setupUi(this);
    setupTable();
    refreshTable(); // Initial load
}

admindashboard_students::~admindashboard_students()
{
    delete ui;
}

// --- INITIALIZATION ---
void admindashboard_students::setupTable()
{
    ui->tableWidget->setColumnCount(6);
    ui->tableWidget->setHorizontalHeaderLabels({"ID", "Name", "Email", "Department", "Class", "Section"});
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

// --- FILTERING LOGIC (Auto-connected) ---
void admindashboard_students::on_searchstudentid_textChanged(const QString &) { refreshTable(); }
void admindashboard_students::on_departmentcombobox_currentTextChanged(const QString &) { refreshTable(); }
void admindashboard_students::on_classcombobox_currentTextChanged(const QString &) { refreshTable(); }
void admindashboard_students::on_sectioncombobox_currentTextChanged(const QString &) { refreshTable(); }

void admindashboard_students::refreshTable()
{
    QString queryStr = "SELECT Student_Id, Name, Email, Department, Class, Section FROM Students WHERE 1=1";

    // Dynamic Filter Building
    if (!ui->searchstudentid->text().isEmpty())
        queryStr += QString(" AND Student_Id LIKE '%%%1%%'").arg(ui->searchstudentid->text());

    if (ui->departmentcombobox->currentText() != "Select Department")
        queryStr += QString(" AND Department = '%1'").arg(ui->departmentcombobox->currentText());

    if (ui->classcombobox->currentText() != "Select Class")
        queryStr += QString(" AND Class = %1").arg(ui->classcombobox->currentText().toInt());

    if (ui->sectioncombobox->currentText() != "Select Section")
        queryStr += QString(" AND Section = '%1'").arg(ui->sectioncombobox->currentText());

    loadDataIntoTable(queryStr);
}

void admindashboard_students::loadDataIntoTable(const QString &queryStr)
{
    QSqlDatabase db = QSqlDatabase::database("college_connection");
    QSqlQuery query(queryStr, db);

    ui->tableWidget->setRowCount(0);
    while (query.next()) {
        int row = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(row);
        for (int i = 0; i < 6; ++i)
            ui->tableWidget->setItem(row, i, new QTableWidgetItem(query.value(i).toString()));
    }
}

// --- FORM INTERACTION ---
void admindashboard_students::on_tableWidget_cellClicked(int row, int)
{
    // Map Table Row to Right-Side Form
    ui->student_id->setText(ui->tableWidget->item(row, 0)->text());
    ui->sdform_name->setText(ui->tableWidget->item(row, 1)->text());
    ui->sdform_email->setText(ui->tableWidget->item(row, 2)->text());
    ui->sdform_dept->setCurrentText(ui->tableWidget->item(row, 3)->text());
    ui->sdform_class->setCurrentText(ui->tableWidget->item(row, 4)->text());
    ui->sdform_section->setCurrentText(ui->tableWidget->item(row, 5)->text());

    ui->sdform_email->setReadOnly(true); // Email is the unique key
}

// --- BUTTON ACTIONS ---
void admindashboard_students::on_buttonSave_clicked()
{
    QString email = ui->sdform_email->text();
    if (email.isEmpty()) return;

    bool success = helpfulfunctions::updateStudentData(
        email,
        ui->student_id->text().toInt(),
        ui->sdform_name->text(),
        ui->sdform_dept->currentText(),
        ui->sdform_class->currentText().toInt(),
        ui->sdform_section->currentText()
    );

    if (success) {
        QMessageBox::information(this, "Success", "Student updated.");
        refreshTable();
        clearForm();
    }
}

void admindashboard_students::on_deletebutton_clicked()
{
    QString email = ui->sdform_email->text();
    if (email.isEmpty()) {
        QMessageBox::warning(this, "Select Student", "Please select a student from the table first.");
        return;
    }

    auto reply = QMessageBox::question(this, "Confirm", "Delete student and login credentials permanently?",
                                      QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        if (executeDeleteTransaction(email)) {
            QMessageBox::information(this, "Deleted", "Student removed.");
            refreshTable();
            clearForm();
        }
    }
}

// --- DATABASE TRANSACTION ---
bool admindashboard_students::executeDeleteTransaction(const QString &email)
{
    QSqlDatabase db = QSqlDatabase::database("college_connection");
    db.transaction();
    QSqlQuery query(db);

    // Remove from profile and users table
    query.prepare("DELETE FROM Students WHERE Email = ?");
    query.addBindValue(email);
    if (!query.exec()) { db.rollback(); return false; }

    query.prepare("DELETE FROM users WHERE Email = ?");
    query.addBindValue(email);
    if (!query.exec()) { db.rollback(); return false; }

    return db.commit();
}

void admindashboard_students::clearForm()
{
    ui->student_id->clear();
    ui->sdform_name->clear();
    ui->sdform_email->clear();
    ui->sdform_email->setReadOnly(false);
    ui->sdform_dept->setCurrentIndex(0);
    ui->sdform_class->setCurrentIndex(0);
    ui->sdform_section->setCurrentIndex(0);
}

void admindashboard_students::on_buttonAdd_clicked()
{
    clearForm();
    QString email = ui->sdform_email->text();
    QString name = ui->sdform_name->text();

    if (email.isEmpty() || name.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Name and Email are required to add a student.");
        return;
    }

    if (isEmailExists(email)) {
        QMessageBox::warning(this, "Duplicate Error", "A student with this email already exists.");
        return;
    }

    if (createNewStudent(email)) {
        QMessageBox::information(this, "Success", "New student added successfully!");
        refreshTable();
        clearForm();
    } else {
        QMessageBox::critical(this, "Database Error", "Failed to add new student.");
    }
}

bool admindashboard_students::isEmailExists(const QString &email)
{
    QSqlDatabase db = QSqlDatabase::database("college_connection");
    QSqlQuery query(db);
    query.prepare("SELECT Email FROM Students WHERE Email = ?");
    query.addBindValue(email);
    query.exec();
    return query.next(); // Returns true if a record is found
}

bool admindashboard_students::createNewStudent(const QString &email)
{
    QSqlDatabase db = QSqlDatabase::database("college_connection");
    db.transaction();
    QSqlQuery query(db);

    // 1. Insert into Students table
    query.prepare("INSERT INTO Students (Student_Id, Name, Email, Department, Class, Section) "
                  "VALUES (?, ?, ?, ?, ?, ?)");
    query.addBindValue(ui->student_id->text().toInt());
    query.addBindValue(ui->sdform_name->text());
    query.addBindValue(email);
    query.addBindValue(ui->sdform_dept->currentText());
    query.addBindValue(ui->sdform_class->currentText().toInt());
    query.addBindValue(ui->sdform_section->currentText());

    if (!query.exec()) { db.rollback(); return false; }

    // 2. Insert into users table (Default password is '1234')
    query.prepare("INSERT INTO users (Email, Password, Role) VALUES (?, '1234', 'Student')");
    query.addBindValue(email);

    if (!query.exec()) { db.rollback(); return false; }

    return db.commit();
}
