#include "td_createclass.h"
#include "ui_td_createclass.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDate>
#include <QTime>

td_createclass::td_createclass(QWidget *parent, const QString &email)
    : QWidget(parent)
    , ui(new Ui::td_createclass)
    , teacherEmail(email)
    , teacherId(-1)
{
    ui->setupUi(this);

    ui->dateEdit->setMinimumDate(QDate::currentDate());

    // Set current date/time as default
    ui->dateEdit->setDate(QDate::currentDate());
    ui->timeEdit->setTime(QTime::currentTime());

    // Start the setup process
    initializeTeacherProfile();
}

// PART A: Database Lookup and Dropdown Population
void td_createclass::initializeTeacherProfile()
{
    QSqlDatabase db = QSqlDatabase::database("college_connection");
    QSqlQuery query(db);

    // 1. Convert Email to Teacher ID
    query.prepare("SELECT teacher_id FROM Teachers WHERE Email = :email");
    query.bindValue(":email", teacherEmail);

    if (query.exec() && query.next()) {
        this->teacherId = query.value(0).toInt();

        // 2. Fetch specific schedule for THIS teacher
        QSqlQuery schedQuery(db);
        schedQuery.prepare("SELECT DISTINCT Subject, Department, Class, Section "
                           "FROM Teachers_Schedule WHERE teacher_id = :tid");
        schedQuery.bindValue(":tid", this->teacherId);

        if (schedQuery.exec()) {
            ui->createclass_subject->clear();
            ui->createclass_department->clear();
            ui->createclass_class->clear();
            ui->createclass_section->clear();

            while (schedQuery.next()) {
                // Populate ComboBoxes without duplicates
                if (ui->createclass_subject->findText(schedQuery.value(0).toString()) == -1)
                    ui->createclass_subject->addItem(schedQuery.value(0).toString());

                if (ui->createclass_department->findText(schedQuery.value(1).toString()) == -1)
                    ui->createclass_department->addItem(schedQuery.value(1).toString());

                if (ui->createclass_class->findText(schedQuery.value(2).toString()) == -1)
                    ui->createclass_class->addItem(schedQuery.value(2).toString());

                if (ui->createclass_section->findText(schedQuery.value(3).toString()) == -1)
                    ui->createclass_section->addItem(schedQuery.value(3).toString());
            }
        }
    } else {
        QMessageBox::critical(this, "Profile Error", "No teacher record found for: " + teacherEmail);
    }
}


void td_createclass::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);
    initializeTeacherProfile();
}


// PART B: Saving the Tuition Class
void td_createclass::on_createclassbutton_clicked()
{
    // Basic Validation
    if (ui->createclass_tuitioname->text().isEmpty() || ui->createclass_tuitionid->text().isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please fill Tuition Title and ID.");
        return;
    }

    QSqlQuery insertQuery(QSqlDatabase::database("college_connection"));
    // Insert into the new Tuition_Classes table
    insertQuery.prepare("INSERT INTO Tuition_Classes (tuition_id, teacher_id, Title, Department, "
                        "Class, Section, Subject, Description, Date_held, Time_held) "
                        "VALUES (:tid, :teacher, :title, :dept, :cls, :sec, :sub, :desc, :date, :time)");

    insertQuery.bindValue(":tid", ui->createclass_tuitionid->text());
    insertQuery.bindValue(":teacher", this->teacherId);
    insertQuery.bindValue(":title", ui->createclass_tuitioname->text());
    insertQuery.bindValue(":dept", ui->createclass_department->currentText());
    insertQuery.bindValue(":cls", ui->createclass_class->currentText().toInt());
    insertQuery.bindValue(":sec", ui->createclass_section->currentText());
    insertQuery.bindValue(":sub", ui->createclass_subject->currentText());
    insertQuery.bindValue(":desc", ui->createclass_description->text());
    insertQuery.bindValue(":date", ui->dateEdit->date().toString("yyyy-MM-dd"));
    insertQuery.bindValue(":time", ui->timeEdit->time().toString("hh:mm AP"));

    if (insertQuery.exec()) {
        QMessageBox::information(this, "Success", "Tuition class created successfully!");
        // --- THE CHANGE IS HERE ---
        // Instead of this->close(), call your reset function
        on_cancel_button_clicked();

        // Optional: Set focus back to the first field for the next entry
        ui->createclass_tuitionid->setFocus();
    } else {
        QMessageBox::critical(this, "Error", "Failed to save class: " + insertQuery.lastError().text());
    }
}

// PART C: Resetting the Form
void td_createclass::on_cancel_button_clicked()
{
    ui->createclass_tuitioname->clear();
    ui->createclass_tuitionid->clear();
    ui->createclass_description->clear();
    ui->dateEdit->setDate(QDate::currentDate());
    ui->timeEdit->setTime(QTime::currentTime());
}

td_createclass::~td_createclass()
{
    delete ui;
}
