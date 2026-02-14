#include "attendancepayment.h"
#include "ui_attendancepayment.h"

attendancepayment::attendancepayment(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::attendancepayment)
{
    ui->setupUi(this);
}

attendancepayment::~attendancepayment()
{
    delete ui;
}

void attendancepayment::setData(QString name, QString id, QString tutor, QString schedule, QString desc, QString att, QString pay)
{
    // Setting text to the specific object names from your UI file
    ui->namelabel->setText(name);
    ui->idlabel->setText("ID: " + id);
    ui->tutorlabel->setText("Tutor: " + tutor);
    ui->schedulelabel->setText(schedule);
    ui->descriptionlabel->setText(desc);

    // Setting attendance and payment status
    ui->label_2->setText("Attendance: " + att); // label_2 is Attendance staus
    ui->label->setText("Payment: " + pay);      // label is Payment status
}
