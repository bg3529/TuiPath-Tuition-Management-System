#ifndef STUDENTDASHBOARD_H
#define STUDENTDASHBOARD_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QString>

// Forward declarations for existing pages
class sd_classes;
class sd_dashboard;

QT_BEGIN_NAMESPACE
namespace Ui { class studentdashboard; }
QT_END_NAMESPACE

class studentdashboard : public QMainWindow {
    Q_OBJECT

public:
    explicit studentdashboard(QWidget *parent = nullptr, QString email = "");
    ~studentdashboard();

    QStackedWidget* getstackedWidget() const;

private slots:
    void on_sddashboard_clicked();
    void on_sdclasses_clicked();


    void on_sdprofile_clicked();
    void on_sdsettings_clicked();
    void on_logout_clicked();

private:
    Ui::studentdashboard *ui;

    // Only keeping the pages that still exist
    sd_classes *classesPage;
    sd_dashboard *dashboardPage;

    QString currentUserEmail;

    // Helper functions for page management
    void initializePages();
    void performGlobalRefresh();
};

#endif
