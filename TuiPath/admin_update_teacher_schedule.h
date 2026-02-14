#ifndef ADMIN_UPDATE_TEACHER_SCHEDULE_H
#define ADMIN_UPDATE_TEACHER_SCHEDULE_H

#include <QWidget>
#include <QTableWidgetItem>

namespace Ui { class admin_update_teacher_schedule; }

class admin_update_teacher_schedule : public QWidget {
    Q_OBJECT

public:
    explicit admin_update_teacher_schedule(QWidget *parent = nullptr);
    ~admin_update_teacher_schedule();

private slots:
    void on_radioScience_toggled(bool checked);
    void on_radioCommerce_toggled(bool checked);
    void on_showteacherstable_cellClicked(int row, int col);
    void on_tdprofile_addtoschedule_clicked();
    void on_savebutton2_clicked();
    void setupTables();
    void on_searchbyteacherid_textChanged(const QString &arg1);
    void on_searchbyteacheremail_textChanged(const QString &arg1);
    void on_tempScheduleTable_itemDoubleClicked(QTableWidgetItem *item);

private:
    Ui::admin_update_teacher_schedule *ui;
    bool isScheduleConflict(const QString &sub, const QString &dept, const QString &cls, const QString &sec);
    void refreshTeachersTable(const QString &condition = "", const QVariant &value = QVariant());
    void loadTeacherSchedule(int teacherId);
    void clearScheduleInputs();
};

#endif
