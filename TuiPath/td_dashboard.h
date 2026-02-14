#ifndef TD_DASHBOARD_H
#define TD_DASHBOARD_H

#include <QWidget>
#include <QString>
#include <QLayout>

namespace Ui {
class td_dashboard;
}

class td_dashboard : public QWidget
{
    Q_OBJECT

public:
    explicit td_dashboard(QWidget *parent = nullptr, const QString &email = "");
    ~td_dashboard();

private slots:
    // Triggered when clicking the "Add Class" button
    void on_pushButton_clicked();

    // Automatically refreshes the list when a class is added or deleted
    void refreshUpcomingClasses();

private:
    Ui::td_dashboard *ui;

    // Identity Data
    QString teacherEmail;
    int teacherId; // To store the primary key from the database

    // Logic Methods
    void fetchTeacherId();      // Gets teacher_id from email
    void clearLayout(QLayout *layout); // Cleanly removes existing UI cards
};

#endif // TD_DASHBOARD_H
