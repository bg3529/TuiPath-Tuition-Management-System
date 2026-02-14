#ifndef TD_PROFILE_H
#define TD_PROFILE_H

#include <QDialog>
#include <QString>
#include <QTableWidgetItem>

namespace Ui {
class td_profile;
}

class td_profile : public QDialog
{
    Q_OBJECT

public:
    explicit td_profile(QWidget *parent = nullptr, const QString &email = "");
    ~td_profile();

private slots:
    /*
    void on_gotoupdateprofiledetails_clicked();
    void on_gotoupdateclasses_clicked();
    void on_savebutton1_clicked();
    void on_tdprofile_addtoschedule_clicked();
    void on_savebutton2_clicked();
    void on_tempScheduleTable_itemDoubleClicked(QTableWidgetItem *item);
    */

private:
    Ui::td_profile *ui;
    QString teacherEmail;
    void loadTeacherInfo(QString email);
    void loadTeacherSchedule(int id);
    // void showExistingAssignments();
    // void setupDepartmentLogic();
};

#endif
