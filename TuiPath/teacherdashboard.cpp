#include "teacherdashboard.h"
#include "qmessagebox.h"
#include "td_createclass.h"
#include "td_dashboard.h"
#include "td_classes.h"
#include "td_attendance.h"
#include "td_payments.h"
#include "td_profile.h"
#include "td_settings.h"
#include "ui_teacherdashboard.h"

teacherdashboard::teacherdashboard(QWidget *parent, const QString &email)
    : QMainWindow(parent),
    ui(new Ui::teacherdashboard),
    teacherEmail(email)
{
    ui->setupUi(this);

    dashboardPage = new td_dashboard(this, teacherEmail);
    classesPage = new td_classes(this, teacherEmail);
    createclassPage = new td_createclass(this, teacherEmail);
    attendancePage = new td_attendance(this, teacherEmail);
    paymentsPage = new td_payments(this, teacherEmail);

    ui->stackedWidget->addWidget(dashboardPage);
    ui->stackedWidget->addWidget(classesPage);
    ui->stackedWidget->addWidget(createclassPage);
    ui->stackedWidget->addWidget(attendancePage);
    ui->stackedWidget->addWidget(paymentsPage);

    ui->stackedWidget->setCurrentWidget(dashboardPage);
}

teacherdashboard::~teacherdashboard()
{
    delete ui;
}

void teacherdashboard::on_td_dashboard_clicked()
{
    ui->stackedWidget->setCurrentWidget(dashboardPage);
}

void teacherdashboard::on_td_classes_clicked()
{
    ui->stackedWidget->setCurrentWidget(classesPage);
}

void teacherdashboard::on_td_createclass_clicked()
{
    ui->stackedWidget->setCurrentWidget(createclassPage);
}

void teacherdashboard::on_td_attendance_clicked()
{
    ui->stackedWidget->setCurrentWidget(attendancePage);
}

void teacherdashboard::on_td_payments_clicked()
{
    ui->stackedWidget->setCurrentWidget(paymentsPage);
}

void teacherdashboard::on_td_profile_clicked()
{
    td_profile *d = new td_profile(this, teacherEmail);
    d->exec();
}

void teacherdashboard::on_td_settings_clicked()
{
    td_settings *d = new td_settings(this, teacherEmail);
    d->exec();
}

void teacherdashboard::on_logothutton_clicked()
{
    if (QMessageBox::question(this, "Logout", "Are you sure.You want to logout?") == QMessageBox::Yes) {
        this->hide();
        this->close();
    }
}

