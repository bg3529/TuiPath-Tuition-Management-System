#include "td_dashboard.h"
#include "td_form.h"
#include "ui_td_dashboard.h"
#include "teacher_upcomingclasses.h"
#include <QDate>
#include <QSqlQuery>
#include <QSqlError>
#include <QVBoxLayout>

td_dashboard::td_dashboard(QWidget *parent, const QString &email)
    : QWidget(parent)
    , ui(new Ui::td_dashboard)
    , teacherEmail(email)
    , teacherId(-1)
{
    ui->setupUi(this);

    // 1. Initialize Layout for the Scroll Area
    if (!ui->scrollAreaWidgetContents->layout()) {
        QVBoxLayout *layout = new QVBoxLayout(ui->scrollAreaWidgetContents);
        layout->setAlignment(Qt::AlignTop);
        layout->setSpacing(10);
    }

    // 2. Initial Data Load
    fetchTeacherId();
    refreshUpcomingClasses();
}

td_dashboard::~td_dashboard()
{
    delete ui;
}

void td_dashboard::fetchTeacherId()
{
    QSqlQuery query(QSqlDatabase::database("college_connection"));
    query.prepare("SELECT teacher_id FROM Teachers WHERE Email = :email");
    query.bindValue(":email", teacherEmail);

    if (query.exec() && query.next()) {
        this->teacherId = query.value(0).toInt();
    }
}

void td_dashboard::refreshUpcomingClasses()
{
    // Clear existing widgets in the layout
    QLayout *layout = ui->scrollAreaWidgetContents->layout();
    while (QLayoutItem *item = layout->takeAt(0)) {
        if (QWidget *widget = item->widget()) widget->deleteLater();
        delete item;
    }

    if (teacherId == -1) return;

    // 3. Date check: Show classes only if the current date hasn't passed the assigned date
    QString today = QDate::currentDate().toString("yyyy-MM-dd");

    QSqlQuery query(QSqlDatabase::database("college_connection"));
    query.prepare("SELECT tuition_id FROM Tuition_Classes "
                  "WHERE teacher_id = :tid AND Date_held >= :today "
                  "ORDER BY Date_held ASC");
    query.bindValue(":tid", teacherId);
    query.bindValue(":today", today);

    if (query.exec()) {
        while (query.next()) {
            QString tId = query.value("tuition_id").toString();

            // 4. Create card and use setData to avoid multi-argument errors
            Teacher_upcomingclasses *card = new Teacher_upcomingclasses(this);
            card->setData(tId);

            // Connect signal for deleting classes
            connect(card, &Teacher_upcomingclasses::classDeleted, this, &td_dashboard::refreshUpcomingClasses);

            layout->addWidget(card);
        }
    }
}

void td_dashboard::on_pushButton_clicked()
{
    td_form *tdformDash = new td_form(teacherEmail, this);

    // Refresh the list automatically when the form is closed
    connect(tdformDash, &QDialog::finished, this, &td_dashboard::refreshUpcomingClasses);

    tdformDash->showMaximized();
}
