// admindashboard.h
#ifndef ADMINDASHBOARD_H
#define ADMINDASHBOARD_H

#include <QMainWindow>
#include "admindashboard_students.h"
#include "admin_update_teacher_schedule.h"
// Assuming your existing teacher UI has a corresponding class name:
#include "admindashboard_teachers.h"

QT_BEGIN_NAMESPACE
namespace Ui { class admindashboard; }
QT_END_NAMESPACE

class admindashboard : public QMainWindow
{
    Q_OBJECT

public:
    admindashboard(QWidget *parent = nullptr);
    ~admindashboard();

private slots:
    void on_adminstudentupdate_clicked();
    void on_adminteacherupdate_clicked();
    void on_teacherassignedclassupdate_clicked();

    void on_td_profile_clicked();

private:
    Ui::admindashboard *ui;

    // Page Pointers
    admindashboard_students *Update_studentspage;
    admindashboard_teachers *Update_teacherspage;
    admin_update_teacher_schedule *Update_teacher_schedule_page;
};

#endif // ADMINDASHBOARD_H
