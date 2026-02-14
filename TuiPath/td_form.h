#ifndef TD_FORM_H
#define TD_FORM_H

#include <QDialog>
#include <QRadioButton>
#include <QList>
#include <QSqlQuery>
#include <QStringList>

namespace Ui { class td_form; }

class td_form : public QDialog {
    Q_OBJECT

public:
    explicit td_form(const QString &Email, QWidget *parent = nullptr);
    ~td_form();

private slots:
    void on_add_to_schedule_clicked();
    void on_save_clicked();
    void on_radioScience_toggled(bool checked);
    void on_radioCommerce_toggled(bool checked);

private:
    Ui::td_form *ui;
    QString teacherEmail;

    void initDatabase();
    void initInterface();
    QString getSelectedSubject();
    void uncheckAllRadios();
    bool isSubjectValidForDept(const QString &subject, const QString &dept);

    bool executeTeacherSave(QSqlQuery &query);
    bool executeScheduleSave(QSqlQuery &query);
    void finalizeTransition();
};

#endif
