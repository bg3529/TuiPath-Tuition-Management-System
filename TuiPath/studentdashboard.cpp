#include "studentdashboard.h"
#include "qmessagebox.h"
#include "sd_dashboard.h"
#include "sd_classes.h"
#include "sd_profile.h"
#include "sd_settings.h"
#include "ui_studentdashboard.h"
#include <QSqlQuery>
#include <QDebug>

studentdashboard::studentdashboard(QWidget *parent, QString email)
    : QMainWindow(parent)
    , ui(new Ui::studentdashboard)
{
    ui->setupUi(this);
    this->currentUserEmail = email;

    initializePages();
}

void studentdashboard::initializePages() {
    dashboardPage  = new sd_dashboard(this, currentUserEmail);
    classesPage    = new sd_classes(this, currentUserEmail);

    ui->stackedWidget->addWidget(dashboardPage);
    ui->stackedWidget->addWidget(classesPage);

    ui->stackedWidget->setCurrentWidget(dashboardPage);
}

void studentdashboard::performGlobalRefresh() {
    qDebug() << "Refreshing student pages...";

    while (ui->stackedWidget->count() > 0) {
        QWidget* widget = ui->stackedWidget->widget(0);
        ui->stackedWidget->removeWidget(widget);
        widget->deleteLater();
    }

    initializePages();
}

studentdashboard::~studentdashboard() {
    delete ui;
}

void studentdashboard::on_sddashboard_clicked() {
    ui->stackedWidget->setCurrentWidget(dashboardPage);
}

void studentdashboard::on_sdclasses_clicked() {
    ui->stackedWidget->setCurrentWidget(classesPage);
}



void studentdashboard::on_sdprofile_clicked() {
    sd_profile *d = new sd_profile(this, currentUserEmail);
    if (d->exec() == QDialog::Accepted) {
        performGlobalRefresh();
    }
    delete d;
}

void studentdashboard::on_sdsettings_clicked() {
    sd_settings *d = new sd_settings(this, currentUserEmail);
    d->exec();
    delete d;
}

void studentdashboard::on_logout_clicked() {
    if (QMessageBox::question(this, "Logout", "Are you sure.You want to logout?") == QMessageBox::Yes) {
        this->hide();
        this->close();
    }
}
