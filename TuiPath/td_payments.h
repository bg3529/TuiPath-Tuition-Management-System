#ifndef TD_PAYMENTS_H
#define TD_PAYMENTS_H

#include <QWidget>
#include <QTableWidgetItem>
#include <QString>

namespace Ui {
class td_payments;
}

class td_payments : public QWidget
{
    Q_OBJECT

public:
    explicit td_payments(QWidget *parent = nullptr, const QString &email = "");
    ~td_payments();

private slots:
    void on_Searchtuitionid_textChanged(const QString &arg1);
    void on_enrolledstudentstable_itemClicked(QTableWidgetItem *item);
    void on_buttonSave_clicked();

private:
    Ui::td_payments *ui;
    QString teacherEmail;
    int teacherId;

    void fetchTeacherId();
};

#endif
