#ifndef TD_SETTINGS_H
#define TD_SETTINGS_H

#include <QDialog>
#include <QString>

namespace Ui {
class td_settings;
}

class td_settings : public QDialog
{
    Q_OBJECT

public:
    explicit td_settings(QWidget *parent = nullptr, const QString &email = "");
    ~td_settings();

private slots:

    void on_Changepasswordbutton_clicked();

private:
    Ui::td_settings *ui;
    QString teacherEmail;

    void setupUI();
    void initializeInterface();
    bool validateInputs(const QString &oldP, const QString &newP, const QString &confP);
};

#endif // TD_SETTINGS_H
