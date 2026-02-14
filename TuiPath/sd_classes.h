#ifndef SD_CLASSES_H
#define SD_CLASSES_H

#include <QWidget>
#include <QString>

namespace Ui {
class sd_classes;
}

class sd_classes : public QWidget
{
    Q_OBJECT

public:
    explicit sd_classes(QWidget *parent = nullptr, QString email = "");
    ~sd_classes();

private:
    Ui::sd_classes *ui;
    QString userEmail;
    int studentId;

    void setupLayout();
    void fetchStudentId();
    void loadPastClasses();
};

#endif
