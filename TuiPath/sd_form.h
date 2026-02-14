#ifndef SD_FORM_H
#define SD_FORM_H

#include <QDialog>

namespace Ui {
class sd_form;
}

class sd_form : public QDialog
{
    Q_OBJECT

public:
    explicit sd_form(QWidget *parent = nullptr, QString email = "");
    ~sd_form();

private slots:
    void on_buttonSave_clicked();

private:
    Ui::sd_form *ui;
    QString userEmail;
};

#endif
