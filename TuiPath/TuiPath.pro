QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    admin_update_teacher_schedule.cpp \
    admindashboard.cpp \
    admindashboard_students.cpp \
    admindashboard_teachers.cpp \
    attendancepayment.cpp \
    enrollclass.cpp \
    helpfulfunctions.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    registter.cpp \
    sd_classes.cpp \
    sd_dashboard.cpp \
    sd_form.cpp \
    sd_profile.cpp \
    sd_settings.cpp \
    studentdashboard.cpp \
    td_attendance.cpp \
    td_classes.cpp \
    td_createclass.cpp \
    td_dashboard.cpp \
    td_form.cpp \
    td_payments.cpp \
    td_profile.cpp \
    td_settings.cpp \
    teacher_upcomingclasses.cpp \
    teacherdashboard.cpp \
    upcomingclasss_student.cpp

HEADERS += \
    admin_update_teacher_schedule.h \
    admindashboard.h \
    admindashboard_students.h \
    admindashboard_teachers.h \
    attendancepayment.h \
    enrollclass.h \
    helpfulfunctions.h \
    login.h \
    mainwindow.h \
    registter.h \
    sd_classes.h \
    sd_dashboard.h \
    sd_form.h \
    sd_profile.h \
    sd_settings.h \
    studentdashboard.h \
    td_attendance.h \
    td_classes.h \
    td_createclass.h \
    td_dashboard.h \
    td_form.h \
    td_payments.h \
    td_profile.h \
    td_settings.h \
    teacher_upcomingclasses.h \
    teacherdashboard.h \
    upcomingclasss_student.h

FORMS += \
    admin_update_teacher_schedule.ui \
    admindashboard.ui \
    admindashboard_students.ui \
    admindashboard_teachers.ui \
    attendancepayment.ui \
    enrollclass.ui \
    login.ui \
    mainwindow.ui \
    registter.ui \
    sd_classes.ui \
    sd_dashboard.ui \
    sd_form.ui \
    sd_profile.ui \
    sd_settings.ui \
    studentdashboard.ui \
    td_attendance.ui \
    td_classes.ui \
    td_createclass.ui \
    td_dashboard.ui \
    td_form.ui \
    td_payments.ui \
    td_profile.ui \
    td_settings.ui \
    teacher_upcomingclasses.ui \
    teacherdashboard.ui \
    upcomingclasss_student.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
