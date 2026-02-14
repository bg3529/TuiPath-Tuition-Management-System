#include "td_profile.h"
#include "ui_td_profile.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>

// =============================================================================
// CONSTRUCTOR & DESTRUCTOR
// =============================================================================

td_profile::td_profile(QWidget *parent, const QString &email)
    : QDialog(parent)
    , ui(new Ui::td_profile)
    , teacherEmail(email)
{
    ui->setupUi(this);

    // Initial Data Load
    loadTeacherInfo(teacherEmail);

    // --- UI Logic for editing commented out ---
    // setupDepartmentLogic();

    // Configure display
    ui->tdupdateprofile_email->setText(email);
    ui->tdupdateprofile_email->setReadOnly(true);

    // Setup Table Visuals
    ui->tempScheduleTable->setColumnCount(4);
    ui->tempScheduleTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

td_profile::~td_profile()
{
    delete ui;
}

// =============================================================================
// DATA LOADING (READ ONLY)
// =============================================================================

void td_profile::loadTeacherInfo(QString email) {
    QSqlDatabase db = QSqlDatabase::database("college_connection");
    QSqlQuery query(db);

    query.prepare("SELECT teacher_id, Name, Email FROM Teachers WHERE Email = :email");
    query.bindValue(":email", email);

    if (query.exec() && query.next()) {
        int id = query.value("teacher_id").toInt();

        // Update Labels on main profile view
        ui->name_tdprofile->setText(query.value("Name").toString());
        ui->email_tdprofile->setText(email);
        ui->id_tdprofile->setText(QString::number(id));

        // Load specific classes for this teacher
        loadTeacherSchedule(id);
        // showExistingAssignments();
    } else {
        qDebug() << "Teacher Info Error:" << query.lastError().text();
    }
}

void td_profile::loadTeacherSchedule(int id) {
    QSqlDatabase db = QSqlDatabase::database("college_connection");
    QSqlQueryModel *model = new QSqlQueryModel(this);

    QString sql = QString(
                      "SELECT Subject || ' ( ' || Department || ' - Class ' || Class || ' - Section ' || Section || ' )' "
                      "FROM Teachers_Schedule WHERE teacher_id = %1"
                      ).arg(id);

    model->setQuery(sql, db);
    ui->allcurrentassignedclasses->setModel(model);
}

// =============================================================================
// NAVIGATION & EDITING LOGIC (COMMENTED OUT)
// =============================================================================

/*
void td_profile::on_gotoupdateprofiledetails_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->updateprofiledetailstd);
}

void td_profile::on_gotoupdateclasses_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->updateyourclassestd);
}

void td_profile::on_savebutton1_clicked() {
    // Logic for updating Name and ID in database
}

void td_profile::on_tdprofile_addtoschedule_clicked() {
    // Logic for temporary schedule selection
}

void td_profile::on_savebutton2_clicked() {
    // Logic for committing schedule changes to DB
}
*/
