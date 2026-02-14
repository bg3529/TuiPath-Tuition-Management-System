#ifndef SD_DASHBOARD_H
#define SD_DASHBOARD_H

#include <QWidget>
#include <QString>
#include <QtSql>
#include <QVBoxLayout>

namespace Ui {
class sd_dashboard;
}

class sd_dashboard : public QWidget {
    Q_OBJECT

public:
    explicit sd_dashboard(QWidget *parent = nullptr, QString email = "");
    ~sd_dashboard();

private slots:

    void refreshAllLists();

private:
    Ui::sd_dashboard *ui;

    // Student Data
    QString userEmail;
    int studentId;
    int studentClass;
    QString studentSection;

    // Initialization logic
    void setupLayouts();
    void fetchStudentDetails();

    // Data loading logic
    void loadEnrollmentList();
    void loadUpcomingList();

    // UI helpers
    /**
      Safely removes all widgets from a given layout.
     */
    void clearLayout(QLayout *layout);

    /**
     Displays a placeholder message when no classes are found.
     */
    void showEmptyMessage(QVBoxLayout *layout, QString message);
};

#endif // SD_DASHBOARD_H
