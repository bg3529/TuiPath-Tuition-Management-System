#include "mainwindow.h"
#include "login.h"
#include "registter.h"
#include "ui_mainwindow.h"




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);






};

MainWindow::~MainWindow()
{
    delete ui;
}






    void MainWindow::on_login1pushButton_clicked()
    {

        auto loginWindow = new login(this);
        loginWindow->showMaximized();


    }




    void MainWindow::on_register1pushButton_clicked()
    {
        auto registterWindow = new registter(this);
        registterWindow->showMaximized();



    }


    void MainWindow::on_register1pushButton_2_clicked()
    {
        auto registterWindow = new registter(this);
        registterWindow->showMaximized();

    }

