#ifndef ENROLLCLASS_H
#define ENROLLCLASS_H

#include <QWidget>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

namespace Ui {
class enrollclass;
}

class enrollclass : public QWidget
{
    Q_OBJECT

public:
    explicit enrollclass(QWidget *parent = nullptr, const QString &stuEmail = "", const QString &tId = "");
    ~enrollclass();

    // Signals must be in their own block to be accessible by the parent dashboard
signals:
    void enrollmentChanged();

private slots:
    void on_enrollnowbutton_clicked();

private:
    Ui::enrollclass *ui;
    QString studentEmail;
    QString targetTuitionId;
    int studentId;
    bool isEnrolled;

    void fetchStudentId();
    void loadTuitionDetails();
    void checkEnrollmentStatus();
};

#endif
