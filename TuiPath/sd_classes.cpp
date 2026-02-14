#include "sd_classes.h"
#include "ui_sd_classes.h"
#include "attendancepayment.h"
#include <QSqlQuery>
#include <QGridLayout>
#include <QDateTime>

sd_classes::sd_classes(QWidget *parent, QString email)
    : QWidget(parent), ui(new Ui::sd_classes), userEmail(email), studentId(-1)
{
    ui->setupUi(this);
    setupLayout();
    fetchStudentId();
    loadPastClasses();
}

void sd_classes::setupLayout() {
    // Creating a grid layout inside the scroll area if it doesn't exist
    if (!ui->scrollAreaWidgetContents->layout()) {
        QGridLayout *layout = new QGridLayout(ui->scrollAreaWidgetContents);
        layout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
        ui->scrollAreaWidgetContents->setLayout(layout);
    }
}

void sd_classes::fetchStudentId() {
    QSqlQuery query(QSqlDatabase::database("college_connection"));
    query.prepare("SELECT Student_Id FROM Students WHERE Email = :email");
    query.bindValue(":email", userEmail);
    if (query.exec() && query.next()) studentId = query.value(0).toInt();
}

void sd_classes::loadPastClasses() {
    QGridLayout *layout = qobject_cast<QGridLayout*>(ui->scrollAreaWidgetContents->layout());
    if (!layout || studentId == -1) return;

    // Clear old cards from the layout
    QLayoutItem *item;
    while ((item = layout->takeAt(0)) != nullptr) {
        if (item->widget()) item->widget()->deleteLater();
        delete item;
    }

    QDateTime now = QDateTime::currentDateTime();
    QSqlQuery query(QSqlDatabase::database("college_connection"));

    // Fetching class details + teacher name + enrollment status
    query.prepare("SELECT t.tuition_id, t.Title, t.Subject, t.Date_held, t.Time_held, t.Description, "
                  "tr.Name AS TeacherName, e.Attendance_Status, e.Payment_Status "
                  "FROM Enrollments e "
                  "JOIN Tuition_Classes t ON e.tuition_id = t.tuition_id "
                  "JOIN Teachers tr ON t.teacher_id = tr.teacher_id "
                  "WHERE e.student_id = :sid");
    query.bindValue(":sid", studentId);

    if (query.exec()) {
        int i = 0;
        while (query.next()) {
            QString date = query.value("Date_held").toString();
            QString time = query.value("Time_held").toString();
            QString schedule = date + " at " + time;

            // Check if class date has passed
            QDateTime classTime = QDateTime::fromString(date + " " + time, "yyyy-MM-dd hh:mm AP");
            if (classTime < now) {
                attendancepayment *card = new attendancepayment(this);

                // Passing all data to the card labels
                card->setData(
                    query.value("Title").toString(),
                    query.value("tuition_id").toString(),
                    query.value("TeacherName").toString(),
                    schedule,
                    query.value("Description").toString(),
                    query.value("Attendance_Status").toString(),
                    query.value("Payment_Status").toString()
                    );

                layout->addWidget(card, i / 2, i % 2);
                i++;
            }
        }
    }
}

sd_classes::~sd_classes() {
    delete ui;
}
