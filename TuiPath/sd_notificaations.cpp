#include "sd_notificaations.h"
#include "ui_sd_notificaations.h"

sd_notificaations::sd_notificaations(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::sd_notificaations)
{
    ui->setupUi(this);
}

sd_notificaations::~sd_notificaations()
{
    delete ui;
}
