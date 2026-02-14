#ifndef REGISTTER_H
#define REGISTTER_H

#include <QDialog>
#include<QtSql>
#include <QSqlDatabase>

namespace Ui {
class registter;
}

class registter : public QDialog
{
    Q_OBJECT

public:
    explicit registter(QWidget *parent = nullptr);
    ~registter();

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_reg_login_clicked();

private:
    Ui::registter *ui;
    QSqlDatabase DB_Connection;
};

#endif // REGISTTER_H
