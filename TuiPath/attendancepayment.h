#ifndef ATTENDANCEPAYMENT_H
#define ATTENDANCEPAYMENT_H

#include <QWidget>

namespace Ui {
class attendancepayment;
}

class attendancepayment : public QWidget
{
    Q_OBJECT

public:
    explicit attendancepayment(QWidget *parent = nullptr);
    ~attendancepayment();

    // Function to fill the labels with database data
    void setData(QString name, QString id, QString tutor, QString schedule, QString desc, QString att, QString pay);

private:
    Ui::attendancepayment *ui;
};

#endif
