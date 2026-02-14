#ifndef UPCOMINGCLASSS_STUDENT_H
#define UPCOMINGCLASSS_STUDENT_H

#include <QWidget>
#include <QString>
#include <QSqlQuery>
#include <QSqlError>

namespace Ui {
class upcomingclasss_student;
}

class upcomingclasss_student : public QWidget
{
    Q_OBJECT

public:
    explicit upcomingclasss_student(QWidget *parent = nullptr, QString email = "", QString tId = "");
    ~upcomingclasss_student();

private:
    Ui::upcomingclasss_student *ui;
    QString userEmail;
    QString targetTuitionId;

    void loadClassData();
};

#endif
