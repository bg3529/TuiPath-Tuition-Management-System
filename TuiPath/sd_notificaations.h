#ifndef SD_NOTIFICAATIONS_H
#define SD_NOTIFICAATIONS_H

#include <QMainWindow>

namespace Ui {
class sd_notificaations;
}

class sd_notificaations : public QMainWindow
{
    Q_OBJECT

public:
    explicit sd_notificaations(QWidget *parent = nullptr);
    ~sd_notificaations();

private:
    Ui::sd_notificaations *ui;
};

#endif // SD_NOTIFICAATIONS_H
