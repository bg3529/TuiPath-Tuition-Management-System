#ifndef TD_ATTENDANCE_H
#define TD_ATTENDANCE_H

#include <QWidget>
#include <QTableWidgetItem>
#include <QString>

namespace Ui {
class td_attendance;
}

class td_attendance : public QWidget
{
    Q_OBJECT

public:
    explicit td_attendance(QWidget *parent = nullptr, const QString &email = "");
    ~td_attendance();

private slots:
    void on_searchbytuitionid_textChanged(const QString &arg1);
    void on_tableWidget_itemClicked(QTableWidgetItem *item);
    void on_buttonSave_clicked();

private:
    Ui::td_attendance *ui;
    QString teacherEmail;
    int teacherId;

    void fetchTeacherId();
};

#endif
