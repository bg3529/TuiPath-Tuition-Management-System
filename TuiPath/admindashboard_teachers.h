#ifndef ADMINDASHBOARD_TEACHERS_H
#define ADMINDASHBOARD_TEACHERS_H

#include <QWidget>
#include <QTableWidgetItem>

namespace Ui {
class admindashboard_teachers;
}

class admindashboard_teachers : public QWidget
{
    Q_OBJECT

public:
    explicit admindashboard_teachers(QWidget *parent = nullptr);
    ~admindashboard_teachers();

private slots:
    // Table Interaction
    void on_tableWidget_cellClicked(int row, int column);

    // CRUD Operations
    void on_addateache_clicked();
    void on_saveteacherbutton_clicked();
    void on_deleteteacher_clicked();

    // Search Functionality
    void on_searchbyteacherid_textChanged(const QString &arg1);
    void on_searchbyteacheremail_textChanged(const QString &arg1);

private:
    Ui::admindashboard_teachers *ui;
    void refreshTable(const QString &filter = "");
    void clearForm();
};

#endif // ADMINDASHBOARD_TEACHERS_H
