#ifndef SD_SETTINGS_H
#define SD_SETTINGS_H

#include <QDialog>
#include <QString>
#include <QSqlDatabase>

namespace Ui {
class sd_settings;
}

class sd_settings : public QDialog
{
    Q_OBJECT

public:
    // Use const reference for string parameters to improve performance
    explicit sd_settings(QWidget *parent = nullptr, const QString &email = "");
    ~sd_settings();

private slots:
    // Slot for the "Change Password" button
    void on_Changepasswordbutton_clicked();

private:
    // Helper to initialize UI state (read-only fields, echo modes, etc.)
    void setupUI();

    Ui::sd_settings *ui;
    QString userEmail;

    // Represents the persistent connection handle
    QSqlDatabase db;
};

#endif // SD_SETTINGS_H
