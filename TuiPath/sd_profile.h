#ifndef SD_PROFILE_H
#define SD_PROFILE_H

#include <QDialog>
#include <QtSql/QSqlDatabase>
#include <QString>

namespace Ui {
class sd_profile;
}

class sd_profile : public QDialog
{
    Q_OBJECT

public:
    // Constructor receives parent and student email
    explicit sd_profile(QWidget *parent = nullptr, QString Email = "");
    ~sd_profile();

private slots:
    // Navigation and Action slots
    void on_backButton_clicked();

    // --- EDITING SLOTS COMMENTED OUT ---
    /*
    void on_editbutton_clicked();
    void on_cancelbutton_clicked();
    void on_savebutton_clicked();
    */

private:
    Ui::sd_profile *ui;
    QSqlDatabase DB_Connection;

    // Helper to fetch and show data from database
    void displayStudentInfo(QString Email);
};

#endif // SD_PROFILE_H
