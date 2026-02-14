#ifndef TD_CLASSES_H
#define TD_CLASSES_H

#include <QWidget>
#include <QTableWidgetItem>
#include <QShowEvent> // Added for auto-refresh

namespace Ui {
class td_classes;
}

class td_classes : public QWidget
{
    Q_OBJECT

public:
    explicit td_classes(QWidget *parent = nullptr, const QString &email = "");
    ~td_classes();

    // Method to reload data from the database
    void loadTeacherClasses();

protected:
    // Automatically refresh data when the teacher opens this tab
    void showEvent(QShowEvent *event) override {
        QWidget::showEvent(event);
        loadTeacherClasses();
    }

private slots:
    // Slot to handle the double click for editing (with restrictions)
    void on_tableWidget_itemDoubleClicked(QTableWidgetItem *item);

    // Manual Save button slot
    void on_saveChangesBtn_clicked();



private:
    Ui::td_classes *ui;
    QString teacherEmail;
    int teacherId;

    // Database helpers
    void fetchTeacherId();

    // NEW: Centralized verification helper for your rules
    // Checks for Assignment, Empty fields, Format, and Future Dates
    bool validateRow(int row, QString &msg);
};

#endif // TD_CLASSES_H
