#ifndef TEACHER_UPCOMINGCLASSES_H
#define TEACHER_UPCOMINGCLASSES_H

#include <QWidget>
#include <QString>

namespace Ui {
class Teacher_upcomingclasses;
}

class Teacher_upcomingclasses : public QWidget
{
    Q_OBJECT

public:
    explicit Teacher_upcomingclasses(QWidget *parent = nullptr);
    ~Teacher_upcomingclasses();


    void setData(const QString &tuitionId);

private slots:
    void on_deleteclass_clicked();

signals:
    void classDeleted(); // To notify dashboard to refresh

private:
    Ui::Teacher_upcomingclasses *ui;
    QString m_tuitionId;
    void loadUIData();
};

#endif
