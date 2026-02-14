#include "upcomingclasss_student.h"
#include "ui_upcomingclasss_student.h"

upcomingclasss_student::upcomingclasss_student(QWidget *parent, QString email, QString tId) :
    QWidget(parent),
    ui(new Ui::upcomingclasss_student),
    userEmail(email),
    targetTuitionId(tId)
{
    ui->setupUi(this);
    loadClassData();
}

void upcomingclasss_student::loadClassData()
{
    // Connect to your database
    QSqlQuery query(QSqlDatabase::database("college_connection"));

    // Join Tuition_Classes with Teachers to get the instructor name
    query.prepare("SELECT t.Title, t.tuition_id, te.Name, t.Date_held, t.Time_held, t.Description "
                  "FROM Tuition_Classes t "
                  "JOIN Teachers te ON t.teacher_id = te.teacher_id "
                  "WHERE t.tuition_id = :tid");
    query.bindValue(":tid", targetTuitionId);

    if (query.exec() && query.next()) {
        // Set labels based on the names in your .ui XML
        ui->tuitionName->setText(query.value("Title").toString());
        ui->tuitionid->setText("ID: " + query.value("tuition_id").toString());
        ui->teachername->setText("Instructor: " + query.value("Name").toString());

        // Combine Date and Time for the Schedule label
        QString scheduleInfo = query.value("Date_held").toString() + " | " + query.value("Time_held").toString();
        ui->Schedule->setText(scheduleInfo);

        ui->Description->setText(query.value("Description").toString());
    }
}

upcomingclasss_student::~upcomingclasss_student()
{
    delete ui;
}
