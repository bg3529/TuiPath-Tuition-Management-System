#ifndef HELPFULFUNCTIONS_H
#define HELPFULFUNCTIONS_H

#include <QString>

class helpfulfunctions {
public:
    static void syncStudentEmail(const QString &Email);

    static bool isProfileIncomplete(const QString &Email);

    static bool updateStudentData(const QString &Email, int Student_Id, const QString &Name,const QString &Department,int Class,
   const QString &Section);

    static void syncTeacherEmail(const QString &Email);
    static bool isTeacherProfileIncomplete(const QString &Email);
    static bool updateTeacherData(const QString &Email, int teacher_id, const QString &Name);
};


#endif
