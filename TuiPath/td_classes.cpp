#include "td_classes.h"
#include "ui_td_classes.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDate>
#include <QDateTime>
#include <QMessageBox>
#include <QHeaderView>

td_classes::td_classes(QWidget *parent, const QString &email)
    : QWidget(parent)
    , ui(new Ui::td_classes), teacherEmail(email), teacherId(-1)
{
    ui->setupUi(this);

    ui->tableWidget->setColumnCount(10);
    ui->tableWidget->setHorizontalHeaderLabels({
        "ID", "Teacher ID", "Title", "Class", "Section",
        "Subject", "Date", "Time", "Department", "Description"
    });

    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->verticalHeader()->setDefaultSectionSize(50);

    fetchTeacherId();
    loadTeacherClasses();
}

// --- VERIFICATION HELPERS ---

bool td_classes::validateRow(int row, QString &msg) {
    // Check if Title, Subject, or Description are empty
    if (ui->tableWidget->item(row, 2)->text().trimmed().isEmpty() ||
        ui->tableWidget->item(row, 5)->text().trimmed().isEmpty()) {
        msg = "Title and Subject cannot be empty.";
        return false;
    }

    // Validate Date/Time formatting
    QDate d = QDate::fromString(ui->tableWidget->item(row, 6)->text(), "yyyy-MM-dd");
    QTime t = QTime::fromString(ui->tableWidget->item(row, 7)->text(), "hh:mm AP");

    if (!d.isValid() || !t.isValid()) {
        msg = "Format Error: Use YYYY-MM-DD and HH:MM AM/PM.";
        return false;
    }

    // Ensure date is not moved to the past
    if (QDateTime(d, t) < QDateTime::currentDateTime()) {
        msg = "Scheduling Error: Class must be in the future.";
        return false;
    }

    return true;
}

// --- CORE FUNCTIONS ---

void td_classes::loadTeacherClasses() {
    ui->tableWidget->setRowCount(0);
    QDate today = QDate::currentDate();

    QSqlQuery query(QSqlDatabase::database("college_connection"));
    query.prepare("SELECT tuition_id, teacher_id, Title, Class, Section, "
                  "Subject, Date_held, Time_held, Department, Description "
                  "FROM Tuition_Classes WHERE teacher_id = :tid ORDER BY Date_held DESC");
    query.bindValue(":tid", teacherId);

    if (query.exec()) {
        int row = 0;
        while (query.next()) {
            ui->tableWidget->insertRow(row);
            QDate classDate = QDate::fromString(query.value("Date_held").toString(), "yyyy-MM-dd");
            bool isPast = (classDate < today);

            for (int col = 0; col < 10; ++col) {
                QTableWidgetItem *item = new QTableWidgetItem(query.value(col).toString());

                // Rule 1: Past classes are fully locked (Red)
                if (isPast) {
                    item->setBackground(QBrush(QColor(255, 200, 200)));
                    item->setFlags(item->flags() & ~Qt::ItemIsEditable);
                }
                // Rule 2: Lock Tuition ID(0), Teacher ID(1), Class(3), Section(4), Department(8) even for present classes
                else if (col == 0 || col == 1 || col == 3 || col == 4 || col == 8) {
                    item->setFlags(item->flags() & ~Qt::ItemIsEditable);
                    item->setToolTip("This field is fixed and cannot be modified.");
                }

                ui->tableWidget->setItem(row, col, item);
            }
            row++;
        }
    }
}

void td_classes::on_tableWidget_itemDoubleClicked(QTableWidgetItem *item) {
    int col = item->column();

    // Check if class is past
    if (item->background().color() == QColor(255, 200, 200)) {
        QMessageBox::warning(this, "Locked", "Past classes cannot be modified.");
        return;
    }

    // New Protection: Check for strictly read-only columns
    if (col == 0 || col == 1 || col == 3 || col == 4 || col == 8) {
        QMessageBox::information(this, "Read Only",
                                 "Tuition ID, Class, Section, and Department are fixed to your schedule and cannot be changed here.");
        return;
    }

    // Ask before editing editable fields (Title, Subject, Date, Time, Description)
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Edit Field", "Do you want to modify this detail?");
    if (reply == QMessageBox::Yes) {
        item->setFlags(item->flags() | Qt::ItemIsEditable);
    }
}

void td_classes::on_saveChangesBtn_clicked()
{
    QSqlDatabase db = QSqlDatabase::database("college_connection");
    db.transaction();

    QSqlQuery query(db);
    QString errorMsg;

    for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {
        // Skip past classes
        if (ui->tableWidget->item(row, 0)->background().color() == QColor(255, 200, 200)) continue;

        if (!validateRow(row, errorMsg)) {
            db.rollback();
            ui->tableWidget->selectRow(row);
            QMessageBox::critical(this, "Invalid Data", QString("Row %1: %2").arg(row + 1).arg(errorMsg));
            return;
        }

        // Only Update Title, Subject, Date, Time, and Description
        query.prepare("UPDATE Tuition_Classes SET Title=:t, Subject=:sub, "
                      "Date_held=:d, Time_held=:tm, Description=:desc "
                      "WHERE tuition_id=:id AND teacher_id=:tid");

        query.bindValue(":t",    ui->tableWidget->item(row, 2)->text().trimmed());
        query.bindValue(":sub",  ui->tableWidget->item(row, 5)->text());
        query.bindValue(":d",    ui->tableWidget->item(row, 6)->text());
        query.bindValue(":tm",   ui->tableWidget->item(row, 7)->text());
        query.bindValue(":desc", ui->tableWidget->item(row, 9)->text());
        query.bindValue(":id",   ui->tableWidget->item(row, 0)->text());
        query.bindValue(":tid",  this->teacherId);

        if (!query.exec()) {
            db.rollback();
            QMessageBox::critical(this, "Error", query.lastError().text());
            return;
        }
    }

    if (db.commit()) {
        QMessageBox::information(this, "Success", "Changes saved successfully.");
    }
}

void td_classes::fetchTeacherId() {
    QSqlQuery query(QSqlDatabase::database("college_connection"));
    query.prepare("SELECT teacher_id FROM Teachers WHERE Email = :email");
    query.bindValue(":email", teacherEmail);
    if (query.exec() && query.next()) {
        this->teacherId = query.value(0).toInt();
    }
}

td_classes::~td_classes() { delete ui; }
