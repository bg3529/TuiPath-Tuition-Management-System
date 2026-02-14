#ifndef TEACHERDASHBOARD_H
#define TEACHERDASHBOARD_H

#include <QMainWindow>
#include <QString>
#include <QStackedWidget>

// Include these so the compiler knows the sizes of your sub-pages
#include "td_createclass.h"
#include "td_classes.h"
#include "td_attendance.h"
#include "td_payments.h"
#include "td_dashboard.h"

QT_BEGIN_NAMESPACE
namespace Ui { class teacherdashboard; }
QT_END_NAMESPACE

class teacherdashboard : public QMainWindow {
    Q_OBJECT

public:

    explicit teacherdashboard( QWidget *parent = nullptr,const QString &email="");
    ~teacherdashboard();

    QStackedWidget* getstackedWidget() const;

private slots:
    void on_td_dashboard_clicked();
    void on_td_classes_clicked();
    void on_td_attendance_clicked();
    void on_td_payments_clicked();
    void on_td_profile_clicked();
    void on_td_settings_clicked();
    void on_td_createclass_clicked();

    void on_logothutton_clicked();

private:
    Ui::teacherdashboard *ui;


    td_classes *classesPage;
    td_attendance *attendancePage;
    td_payments *paymentsPage;
    td_dashboard *dashboardPage;
    td_createclass *createclassPage;


        QString teacherEmail;
};

#endif
