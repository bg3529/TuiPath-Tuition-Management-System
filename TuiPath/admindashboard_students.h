#ifndef ADMINDASHBOARD_STUDENTS_H
#define ADMINDASHBOARD_STUDENTS_H

#include <QWidget>
#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>

namespace Ui {
class admindashboard_students;
}

class admindashboard_students : public QWidget
{
    Q_OBJECT

public:
    explicit admindashboard_students(QWidget *parent = nullptr);
    ~admindashboard_students();

private slots:
    // Filter Auto-slots (Named to match UI objects)
    void on_searchstudentid_textChanged(const QString &arg1);
    void on_departmentcombobox_currentTextChanged(const QString &arg1);
    void on_classcombobox_currentTextChanged(const QString &arg1);
    void on_sectioncombobox_currentTextChanged(const QString &arg1);

    // Form and Table Interaction Auto-slots
    void on_tableWidget_cellClicked(int row, int column);
    void on_buttonSave_clicked();
    void on_deletebutton_clicked();
    void on_buttonAdd_clicked();

private:
    Ui::admindashboard_students *ui;

    // Internal logic helpers
    void setupTable();
    void refreshTable();
    void loadDataIntoTable(const QString &queryStr);
    void clearForm();
    bool executeDeleteTransaction(const QString &email);
    bool isEmailExists(const QString &email);
    bool createNewStudent(const QString &email);
};

#endif // ADMINDASHBOARD_STUDENTS_H
