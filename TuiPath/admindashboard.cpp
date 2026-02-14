
#include "admindashboard.h"
#include "ui_admindashboard.h"

admindashboard::admindashboard(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::admindashboard)
{
    ui->setupUi(this);

    // 1. Initialize the pages
    Update_studentspage = new admindashboard_students(this);
    Update_teacherspage = new admindashboard_teachers(this);
    Update_teacher_schedule_page = new admin_update_teacher_schedule(this);

    // 2. Add pages to the stacked widget

    ui->stackedWidget->addWidget(Update_studentspage);
    ui->stackedWidget->addWidget(Update_teacherspage);
    ui->stackedWidget->addWidget(Update_teacher_schedule_page);
}

admindashboard::~admindashboard()
{
    delete ui;
}

// Navigates to Student Update Page
void admindashboard::on_adminstudentupdate_clicked()
{
    ui->stackedWidget->setCurrentWidget(Update_studentspage);
}

// Navigates to General Teacher Management (admindashboard_teachers)
void admindashboard::on_adminteacherupdate_clicked()
{
    ui->stackedWidget->setCurrentWidget(Update_teacherspage);
}

// Navigates to the Teacher Schedule Update Page (the code we just wrote)
void admindashboard::on_teacherassignedclassupdate_clicked()
{
    ui->stackedWidget->setCurrentWidget(Update_teacher_schedule_page);
}

void admindashboard::on_td_profile_clicked()
{
    this->hide();
    this->close();
}

