#include "enrollclass.h"
#include "ui_enrollclass.h"

enrollclass::enrollclass(QWidget *parent, const QString &stuEmail, const QString &tId) :
    QWidget(parent), ui(new Ui::enrollclass),
    studentEmail(stuEmail), targetTuitionId(tId), studentId(-1), isEnrolled(false)
{
    ui->setupUi(this);

    // Initialize data and UI state
    fetchStudentId();
    loadTuitionDetails();
    checkEnrollmentStatus();
}

void enrollclass::fetchStudentId() {
    QSqlQuery query(QSqlDatabase::database("college_connection"));
    query.prepare("SELECT Student_Id FROM Students WHERE Email = :email");
    query.bindValue(":email", studentEmail);

    if (query.exec() && query.next()) {
        this->studentId = query.value(0).toInt();
    }
}

void enrollclass::checkEnrollmentStatus() {
    if (studentId == -1) return;

    QSqlQuery query(QSqlDatabase::database("college_connection"));
    query.prepare("SELECT 1 FROM Enrollments WHERE student_id = :sid AND tuition_id = :tid");
    query.bindValue(":sid", studentId);
    query.bindValue(":tid", targetTuitionId);

    // Update button appearance based on enrollment state
    if (query.exec() && query.next()) {
        isEnrolled = true;
        ui->enrollnowbutton->setText("Unenroll");
        ui->enrollnowbutton->setStyleSheet("background-color: rgb(255, 0, 0); color: white; font: 600 20pt 'Segoe UI';");
    } else {
        isEnrolled = false;
        ui->enrollnowbutton->setText("Enroll Now");
        ui->enrollnowbutton->setStyleSheet("background-color: rgb(77, 232, 0); color: white; font: 600 20pt 'Segoe UI';");
    }
}

void enrollclass::on_enrollnowbutton_clicked() {
    if (studentId == -1) {
        QMessageBox::critical(this, "Error", "Student record not found.");
        return;
    }

    QSqlQuery q(QSqlDatabase::database("college_connection"));

    if (isEnrolled) {
        // --- UNENROLL LOGIC ---
        q.prepare("DELETE FROM Enrollments WHERE student_id = :sid AND tuition_id = :tid");
        q.bindValue(":sid", studentId);
        q.bindValue(":tid", targetTuitionId);

        if (q.exec()) {
            QMessageBox::information(this, "Success", "You have unenrolled from this class.");
            checkEnrollmentStatus();
            emit enrollmentChanged(); // Notify dashboard to refresh lists
        }
    } else {
        // --- ENROLL LOGIC ---
        q.prepare("INSERT INTO Enrollments (student_id, tuition_id, Status) VALUES (:sid, :tid, 'Enrolled')");
        q.bindValue(":sid", studentId);
        q.bindValue(":tid", targetTuitionId);

        if (q.exec()) {
            QMessageBox::information(this, "Success", "Successfully enrolled!");
            checkEnrollmentStatus();
            emit enrollmentChanged(); // Notify dashboard to refresh lists
        } else if (q.lastError().text().contains("UNIQUE")) {
            QMessageBox::warning(this, "Notice", "Already enrolled.");
        }
    }
}

void enrollclass::loadTuitionDetails() {
    QSqlQuery query(QSqlDatabase::database("college_connection"));
    // Join tables to display the teacher's name instead of just their ID
    query.prepare("SELECT t.Title, t.tuition_id, te.Name, t.Date_held, t.Time_held, t.Description "
                  "FROM Tuition_Classes t JOIN Teachers te ON t.teacher_id = te.teacher_id "
                  "WHERE t.tuition_id = :tid");
    query.bindValue(":tid", targetTuitionId);

    if (query.exec() && query.next()) {
        ui->tuitionName->setText(query.value("Title").toString());
        ui->tuitionid->setText("ID: " + query.value("tuition_id").toString());
        ui->teachername->setText("Instructor: " + query.value("Name").toString());
        ui->Schedule->setText(query.value("Date_held").toString() + " | " + query.value("Time_held").toString());
        ui->Description->setText(query.value("Description").toString());
    }
}

enrollclass::~enrollclass() {
    delete ui;
}
