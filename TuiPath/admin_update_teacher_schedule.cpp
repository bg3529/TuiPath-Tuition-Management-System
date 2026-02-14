#include "admin_update_teacher_schedule.h"
#include "ui_admin_update_teacher_schedule.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>

admin_update_teacher_schedule::admin_update_teacher_schedule(QWidget *parent)
    : QWidget(parent), ui(new Ui::admin_update_teacher_schedule)
{
    ui->setupUi(this);

    // 1. Setup Table Structures (Crucial for visibility)
    setupTables();

    // 2. Initial UI State
    ui->lineEdit->setReadOnly(true);
    ui->lineEdit_2->setReadOnly(true);

    // Subjects hidden until Department is selected
    ui->Sciencesubjects->hide();
    ui->Commercesubjects->hide();

    // 3. Load Data
    refreshTeachersTable();
}

admin_update_teacher_schedule::~admin_update_teacher_schedule() {
    delete ui;
}

// --- INITIALIZATION ---
void admin_update_teacher_schedule::setupTables() {
    // Teacher Selection Table
    ui->showteacherstable->setColumnCount(3);
    ui->showteacherstable->setHorizontalHeaderLabels({"ID", "Name", "Email"});
    ui->showteacherstable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->showteacherstable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->showteacherstable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // Temporary Schedule Table
    ui->tempScheduleTable->setColumnCount(4);
    ui->tempScheduleTable->setHorizontalHeaderLabels({"Subject", "Department", "Class", "Section"});
    ui->tempScheduleTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

// --- UI TOGGLE LOGIC ---
void admin_update_teacher_schedule::on_radioScience_toggled(bool checked) {
    ui->Sciencesubjects->setVisible(checked);
    if(checked) ui->Commercesubjects->hide();
}

void admin_update_teacher_schedule::on_radioCommerce_toggled(bool checked) {
    ui->Commercesubjects->setVisible(checked);
    if(checked) ui->Sciencesubjects->hide();
}

// --- DATA LOADING & SEARCH ---
void admin_update_teacher_schedule::refreshTeachersTable(const QString &condition, const QVariant &value) {
    QSqlDatabase db = QSqlDatabase::database("college_connection");
    if (!db.isOpen()) {
        qDebug() << "Database connection 'college_connection' not found/open!";
        return;
    }

    QSqlQuery query(db);
    QString sql = "SELECT teacher_id, Name, Email FROM Teachers";

    if (!condition.isEmpty()) {
        sql += " WHERE " + condition;
    }

    query.prepare(sql);
    if (!value.isNull()) {
        query.addBindValue(value);
    }

    ui->showteacherstable->setRowCount(0);
    if (query.exec()) {
        while (query.next()) {
            int row = ui->showteacherstable->rowCount();
            ui->showteacherstable->insertRow(row);
            ui->showteacherstable->setItem(row, 0, new QTableWidgetItem(query.value(0).toString()));
            ui->showteacherstable->setItem(row, 1, new QTableWidgetItem(query.value(1).toString()));
            ui->showteacherstable->setItem(row, 2, new QTableWidgetItem(query.value(2).toString()));
        }
    } else {
        qDebug() << "SQL Error:" << query.lastError().text();
    }
}

void admin_update_teacher_schedule::on_showteacherstable_cellClicked(int row, int) {
    QString id = ui->showteacherstable->item(row, 0)->text();
    ui->lineEdit_2->setText(id);
    ui->lineEdit->setText(ui->showteacherstable->item(row, 2)->text());
    loadTeacherSchedule(id.toInt());
}

void admin_update_teacher_schedule::loadTeacherSchedule(int teacherId) {
    QSqlQuery query(QSqlDatabase::database("college_connection"));
    query.prepare("SELECT Subject, Department, Class, Section FROM Teachers_Schedule WHERE teacher_id = ?");
    query.addBindValue(teacherId);

    ui->tempScheduleTable->setRowCount(0);
    if (query.exec()) {
        while (query.next()) {
            int row = ui->tempScheduleTable->rowCount();
            ui->tempScheduleTable->insertRow(row);
            for(int i = 0; i < 4; ++i)
                ui->tempScheduleTable->setItem(row, i, new QTableWidgetItem(query.value(i).toString()));
        }
    }
}

// --- SCHEDULE MANAGEMENT ---


bool admin_update_teacher_schedule::isScheduleConflict(const QString &sub, const QString &dept, const QString &cls, const QString &sec) {
    // --- 1. PREVENT DUPLICATES IN THE CURRENT UI TABLE ---
    for (int i = 0; i < ui->tempScheduleTable->rowCount(); ++i) {
        if (ui->tempScheduleTable->item(i, 0)->text() == sub &&
            ui->tempScheduleTable->item(i, 1)->text() == dept &&
            ui->tempScheduleTable->item(i, 2)->text() == cls &&
            ui->tempScheduleTable->item(i, 3)->text() == sec) {

            QMessageBox::warning(this, "Duplicate", "This specific class is already in your list below.");
            return true; // Conflict found
        }
    }

    // --- 2. CONFLICT DETECTION IN DATABASE ---
    QSqlDatabase db = QSqlDatabase::database("college_connection");
    QSqlQuery checkQuery(db);
    checkQuery.prepare("SELECT teacher_id FROM Teachers_Schedule "
                       "WHERE Class = :cls AND Section = :sec "
                       "AND Subject = :sub AND Department = :dept");
    checkQuery.bindValue(":cls", cls);
    checkQuery.bindValue(":sec", sec);
    checkQuery.bindValue(":sub", sub);
    checkQuery.bindValue(":dept", dept);

    if (checkQuery.exec() && checkQuery.next()) {
        int assignedTeacherId = checkQuery.value(0).toInt();
        int currentTeacherId = ui->lineEdit_2->text().toInt(); // Your Teacher ID field

        // Only trigger conflict if the teacher assigned is NOT the one currently selected
        if (assignedTeacherId != currentTeacherId) {
            QMessageBox::critical(this, "Conflict",
                                  QString("This slot (%1 - Class %2 %3) is already assigned to another teacher (ID: %4).")
                                      .arg(sub).arg(cls).arg(sec).arg(assignedTeacherId));
            return true; // Conflict found
        }
    }

    return false; // No conflict
}

void admin_update_teacher_schedule::on_tdprofile_addtoschedule_clicked() {
    if (ui->lineEdit_2->text().isEmpty()) {
        QMessageBox::warning(this, "Selection Required", "Please select a teacher from the table.");
        return;
    }

    QString dept = ui->radioScience->isChecked() ? "Science" : (ui->radioCommerce->isChecked() ? "Commerce" : "");
    QString sub = "";

    // Identify selected subject from visible group
    if (ui->radioScience->isChecked()) {
        if(ui->radioPhysics->isChecked()) sub = "Physics";
        else if(ui->radioChemistry->isChecked()) sub = "Chemistry";
        else if(ui->radioMath->isChecked()) sub = "Math";
        else if(ui->radioBiology->isChecked()) sub = "Biology";
    } else if (ui->radioCommerce->isChecked()) {
        if(ui->radioBusiness->isChecked()) sub = "Business";
        else if(ui->radioAccountancy->isChecked()) sub = "Accountancy";
        else if(ui->radioFinance->isChecked()) sub = "Finance";
        else if(ui->radioEconomics->isChecked()) sub = "Economics";
    }

    QString cls = ui->radio11->isChecked() ? "11" : (ui->radio12->isChecked() ? "12" : "");
    QString sec = ui->radioA->isChecked() ? "A" : (ui->radioB->isChecked() ? "B" : "");

    if (dept.isEmpty() || sub.isEmpty() || cls.isEmpty() || sec.isEmpty()) {
        QMessageBox::warning(this, "Missing Info", "Ensure Department, Subject, Class, and Section are selected.");
        return;
    }

    // 3. CALL VALIDATION FUNCTION
    if (isScheduleConflict(sub, dept, cls, sec)) {
        return; // Stop if there is a duplicate or database conflict
    }


    int row = ui->tempScheduleTable->rowCount();
    ui->tempScheduleTable->insertRow(row);
    ui->tempScheduleTable->setItem(row, 0, new QTableWidgetItem(sub));
    ui->tempScheduleTable->setItem(row, 1, new QTableWidgetItem(dept));
    ui->tempScheduleTable->setItem(row, 2, new QTableWidgetItem(cls));
    ui->tempScheduleTable->setItem(row, 3, new QTableWidgetItem(sec));
}

void admin_update_teacher_schedule::on_savebutton2_clicked() {
    int id = ui->lineEdit_2->text().toInt();
    if (id <= 0) return;

    QSqlDatabase db = QSqlDatabase::database("college_connection");
    db.transaction();
    QSqlQuery q(db);

    // 1. Wipe existing schedule
    q.prepare("DELETE FROM Teachers_Schedule WHERE teacher_id = ?");
    q.addBindValue(id);
    if(!q.exec()) { db.rollback(); return; }

    // 2. Insert new rows from table
    for(int i = 0; i < ui->tempScheduleTable->rowCount(); ++i) {
        q.prepare("INSERT INTO Teachers_Schedule (teacher_id, Subject, Department, Class, Section) VALUES (?,?,?,?,?)");
        q.addBindValue(id);
        q.addBindValue(ui->tempScheduleTable->item(i, 0)->text());
        q.addBindValue(ui->tempScheduleTable->item(i, 1)->text());
        q.addBindValue(ui->tempScheduleTable->item(i, 2)->text());
        q.addBindValue(ui->tempScheduleTable->item(i, 3)->text());
        if(!q.exec()) { db.rollback(); return; }
    }

    if(db.commit()) {
        QMessageBox::information(this, "Success", "Schedule successfully updated.");
    }
}

// --- SEARCH SLOTS ---
void admin_update_teacher_schedule::on_searchbyteacherid_textChanged(const QString &arg1) {
    if(arg1.isEmpty()) refreshTeachersTable();
    else refreshTeachersTable("teacher_id LIKE ?", "%" + arg1 + "%");
}

void admin_update_teacher_schedule::on_searchbyteacheremail_textChanged(const QString &arg1) {
    if(arg1.isEmpty()) refreshTeachersTable();
    else refreshTeachersTable("Email LIKE ?", "%" + arg1 + "%");
}

void admin_update_teacher_schedule::on_tempScheduleTable_itemDoubleClicked(QTableWidgetItem *item) {
    ui->tempScheduleTable->removeRow(item->row());
}
