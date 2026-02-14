#include "helpfulfunctions.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QSqlDatabase>

void helpfulfunctions::syncStudentEmail(const QString &Email) {
    QSqlQuery check(QSqlDatabase::database("college_connection"));
    check.prepare("SELECT Email FROM Students WHERE Email = :email");
    check.bindValue(":email", Email);

    if (check.exec() && !check.next()) {
        QSqlQuery insert(QSqlDatabase::database("college_connection"));
        insert.prepare("INSERT INTO Students (Email) VALUES (:email)");
        insert.bindValue(":email", Email);

        if (!insert.exec()) {
            qDebug() << "Insert failed:" << insert.lastError().text();
        }
    }
}

bool helpfulfunctions::isProfileIncomplete(const QString &Email) {
    QSqlQuery query(QSqlDatabase::database("college_connection"));
    query.prepare("SELECT Student_Id, Name, Department, Class, Email, Section "
                  "FROM Students WHERE Email = :sdform_email");
    query.bindValue(":sdform_email", Email);

    if (query.exec() && query.next()) {

        return (query.value("Student_Id").toInt() <= 0 ||
                query.value("Name").toString().isEmpty() ||
                query.value("Department").toString().isEmpty() ||
                query.value("Class").toInt() <= 0 ||
                query.value("Email").toString().isEmpty() ||
                query.value("Section").toString().isEmpty());
    }
    return true;
}

bool helpfulfunctions::updateStudentData(const QString &Email,
                                         int Student_Id,
                                         const QString &Name,
                                         const QString &Department,
                                         int Class,
                                         const QString &Section) {
    QSqlQuery query(QSqlDatabase::database("college_connection"));

    // Attempt Update first based on Email
    query.prepare("UPDATE Students "
                  "SET Student_Id = :student_id, "
                  "    Name = :sdform_name, "
                  "    Department = :sdform_dept, "
                  "    Class = :sdform_class, "
                  "    Section = :sdform_section "
                  "WHERE Email = :sdform_email");

    query.bindValue(":student_id", Student_Id); //
    query.bindValue(":sdform_name", Name);
    query.bindValue(":sdform_dept", Department);
    query.bindValue(":sdform_class", Class);
    query.bindValue(":sdform_section", Section);
    query.bindValue(":sdform_email", Email);

    if (!query.exec()) {
        qDebug() << "Update failed:" << query.lastError().text();
        return false;
    }

    // If record doesn't exist, Insert it
    if (query.numRowsAffected() == 0) {
        QSqlQuery insert(QSqlDatabase::database("college_connection"));
        insert.prepare("INSERT INTO Students (Student_Id, Name, Department, Class, Email, Section) "
                       "VALUES (:student_id, :sdform_name, :sdform_dept, :sdform_class, :sdform_email, :sdform_section)");

        insert.bindValue(":student_id", Student_Id);
        insert.bindValue(":sdform_name", Name);
        insert.bindValue(":sdform_dept", Department);
        insert.bindValue(":sdform_class", Class);
        insert.bindValue(":sdform_email", Email);
        insert.bindValue(":sdform_section", Section);

        if (!insert.exec()) {
            qDebug() << "Insert failed:" << insert.lastError().text();
            return false;
        }
    }

    return true;
}



void helpfulfunctions::syncTeacherEmail(const QString &Email) {
    QSqlQuery check(QSqlDatabase::database("college_connection"));
    check.prepare("SELECT Email FROM Teachers WHERE Email = :email");
    check.bindValue(":email", Email);

    if (check.exec() && !check.next()) {
        QSqlQuery insert(QSqlDatabase::database("college_connection"));
        insert.prepare("INSERT INTO Teachers (Email) VALUES (:email)");
        insert.bindValue(":email", Email);

        if (!insert.exec()) {
            qDebug() << "Teacher Email sync failed:" << insert.lastError().text();
        }
    }
}

// 2. Check if the teacher needs to fill out the registration form
bool helpfulfunctions::isTeacherProfileIncomplete(const QString &Email) {
    QSqlQuery query(QSqlDatabase::database("college_connection"));
    query.prepare("SELECT Teacher_Id, name FROM Teachers WHERE Email = :email");
    query.bindValue(":email", Email);

    if (query.exec() && query.next()) {
        // Returns true if ID is missing or Name is empty
        return (query.value("teacher_id").toInt() <= 0 ||
                query.value("name").toString().isEmpty());
    }
    return true;
}

// 3. Update the Teacher's profile data
bool helpfulfunctions::updateTeacherData(const QString &Email, int teacher_id, const QString &Name) {
    QSqlQuery query(QSqlDatabase::database("college_connection"));

    // Update based on the unique Email key
    query.prepare("UPDATE Teachers SET teacher_id = :td_id, Name = :td_name WHERE Email = :td_email");
    query.bindValue(":td_id", teacher_id);
    query.bindValue(":td_name", Name);
    query.bindValue(":td_email", Email);

    if (!query.exec()) {
        qDebug() << "Teacher Update failed:" << query.lastError().text();
        return false;
    }

    // Handle initial insert if the entry wasn't synced properly
    if (query.numRowsAffected() == 0) {
        QSqlQuery insert(QSqlDatabase::database("college_connection"));
        insert.prepare("INSERT INTO Teachers (teacher_id, Name, Email) VALUES (:td_id, :td_name, :td_email)");
        insert.bindValue(":td_id", teacher_id);
        insert.bindValue(":td_name", Name);
        insert.bindValue(":td_email", Email);
        return insert.exec();
    }

    return true;
}
