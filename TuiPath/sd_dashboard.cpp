#include "sd_dashboard.h"
#include "ui_sd_dashboard.h"
#include "enrollclass.h"
#include "upcomingclasss_student.h"
#include <QDateTime>
#include <QVBoxLayout>
#include <QSqlQuery>
#include <QLabel>
#include <QSqlError>
#include <QDebug>

sd_dashboard::sd_dashboard(QWidget *parent, QString email)
    : QWidget(parent), ui(new Ui::sd_dashboard), userEmail(email), studentId(-1)
{
    ui->setupUi(this);

    // 1. Initialize Layouts
    setupLayouts();

    // 2. Load Data
    fetchStudentDetails();

    // Only refresh if the student was found in the database
    if (studentId != -1) {
        refreshAllLists();
    }
}

void sd_dashboard::setupLayouts() {
    if (!ui->scrollAreaWidgetContents_2->layout()) {
        QVBoxLayout *enrollLayout = new QVBoxLayout(ui->scrollAreaWidgetContents_2);
        enrollLayout->setAlignment(Qt::AlignTop);
        enrollLayout->setSpacing(10);
    }

    if (!ui->scrollAreaWidgetContents->layout()) {
        QVBoxLayout *upLayout = new QVBoxLayout(ui->scrollAreaWidgetContents);
        upLayout->setAlignment(Qt::AlignTop);
        upLayout->setSpacing(10);
    }
}

void sd_dashboard::fetchStudentDetails() {
    QSqlQuery query(QSqlDatabase::database("college_connection"));
    // Uses correct column names from the Students table
    query.prepare("SELECT Student_Id, Class, Section FROM Students WHERE Email = :email");
    query.bindValue(":email", userEmail);

    if (query.exec() && query.next()) {
        this->studentId = query.value("Student_Id").toInt();
        // Database stores Class as TEXT; convert to int for comparison
        this->studentClass = query.value("Class").toInt();
        this->studentSection = query.value("Section").toString();
    } else {
        qDebug() << "Student fetch error:" << query.lastError().text();
    }
}

void sd_dashboard::refreshAllLists() {
    if (studentId == -1) return;
    loadEnrollmentList();
    loadUpcomingList();
}

void sd_dashboard::loadEnrollmentList() {
    QVBoxLayout *layout = qobject_cast<QVBoxLayout*>(ui->scrollAreaWidgetContents_2->layout());
    clearLayout(layout);

    QSqlQuery query(QSqlDatabase::database("college_connection"));
    QString currentDateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm AP");

    // Logic: Only show classes for the student's specific Class/Section [cite: 5, 10]
    // Filter out classes the student is already enrolled in using the Enrollments table
    query.prepare("SELECT tuition_id FROM Tuition_Classes "
                  "WHERE Class = :class AND Section = :section "
                  "AND (Date_held || ' ' || Time_held) > :now "
                  "AND tuition_id NOT IN (SELECT tuition_id FROM Enrollments WHERE student_id = :sid)");

    query.bindValue(":class", studentClass);
    query.bindValue(":section", studentSection);
    query.bindValue(":now", currentDateTime);
    query.bindValue(":sid", studentId);

    if (query.exec()) {
        bool found = false;
        while (query.next()) {
            found = true;
            QString tId = query.value(0).toString();
            enrollclass *card = new enrollclass(this, userEmail, tId);
            connect(card, &enrollclass::enrollmentChanged, this, &sd_dashboard::refreshAllLists);
            layout->addWidget(card);
        }
        if (!found) showEmptyMessage(layout, "No new classes available for your section.");
    }
}

void sd_dashboard::loadUpcomingList() {
    QVBoxLayout *layout = qobject_cast<QVBoxLayout*>(ui->scrollAreaWidgetContents->layout());
    clearLayout(layout);

    if (studentId == -1) return;

    QSqlQuery query(QSqlDatabase::database("college_connection"));
    QString currentDateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm AP");

    // Join Enrollments with Tuition_Classes to find future sessions for this student [cite: 5, 6]
    query.prepare("SELECT e.tuition_id FROM Enrollments e "
                  "JOIN Tuition_Classes t ON e.tuition_id = t.tuition_id "
                  "WHERE e.student_id = :sid AND (t.Date_held || ' ' || t.Time_held) > :now "
                  "ORDER BY t.Date_held ASC, t.Time_held ASC");

    query.bindValue(":sid", studentId);
    query.bindValue(":now", currentDateTime);

    if (query.exec()) {
        bool hasUpcoming = false;
        while (query.next()) {
            hasUpcoming = true;
            QString tId = query.value(0).toString();
            upcomingclasss_student *upCard = new upcomingclasss_student(this, userEmail, tId);
            layout->addWidget(upCard);
        }
        if (!hasUpcoming) showEmptyMessage(layout, "You have no upcoming classes.");
    }
}

void sd_dashboard::clearLayout(QLayout *layout) {
    if (!layout) return;
    while (QLayoutItem *item = layout->takeAt(0)) {
        if (QWidget *widget = item->widget()) {
            widget->deleteLater();
        }
        delete item;
    }
}

void sd_dashboard::showEmptyMessage(QVBoxLayout *layout, QString message) {
    QLabel *label = new QLabel(message);
    label->setAlignment(Qt::AlignCenter);
    label->setStyleSheet("color: gray; padding: 20px; font-style: italic;");
    layout->addWidget(label);
}

sd_dashboard::~sd_dashboard() {
    delete ui;
}
