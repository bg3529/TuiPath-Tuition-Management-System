#ifndef TD_CREATECLASS_H
#define TD_CREATECLASS_H

#include <QWidget>
#include <QComboBox>
#include <QString>
#include <QSqlDatabase>

namespace Ui { class td_createclass; }

class td_createclass : public QWidget
{
    Q_OBJECT

public:
    explicit td_createclass(QWidget *parent = nullptr, const QString &email = "");
    ~td_createclass();

private slots:
    // Core actions linked to UI buttons
    void on_createclassbutton_clicked();
    void on_cancel_button_clicked();

protected:
    void showEvent(QShowEvent *event) override;

private:
    Ui::td_createclass *ui;
    QString teacherEmail;
    int teacherId;

    // Phase 1: Setup - Convert Email to ID and fill UI
    void initializeTeacherProfile();
    void populateScheduleDropdowns();

    // Phase 2: Utility - Keep dropdowns clean
    void addUniqueItem(QComboBox* cb, const QString& text);

    // Phase 3: Validation and Execution
    bool validateInputs(); // Check if fields are empty before saving
    bool saveToDatabase(); // The actual SQL INSERT logic
};



#endif
