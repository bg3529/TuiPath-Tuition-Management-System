#ifndef LOGIN_H
#define LOGIN_H

#include "qsqldatabase.h"
#include "sd_dashboard.h"
#include <QDialog>

namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();

private slots:

    void on_login_loginpage_clicked();
    void on_register_loginpage_clicked();


private:
    Ui::login *ui;
    QSqlDatabase DB_Connection;
    sd_dashboard *dashboardPage;
};

#endif // LOGIN_H
