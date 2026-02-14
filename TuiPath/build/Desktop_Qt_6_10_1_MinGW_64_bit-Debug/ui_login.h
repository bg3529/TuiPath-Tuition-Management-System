/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_login
{
public:
    QTextEdit *textEdit;
    QPushButton *login1pushButton;
    QLabel *email1;
    QLineEdit *Password1;
    QLabel *label_3;
    QFrame *frame_2;
    QTextEdit *textEdit_6;
    QLabel *label;
    QLineEdit *lineEdit;
    QPushButton *register1pushButton;
    QLabel *label_2;

    void setupUi(QDialog *login)
    {
        if (login->objectName().isEmpty())
            login->setObjectName("login");
        login->resize(1024, 760);
        textEdit = new QTextEdit(login);
        textEdit->setObjectName("textEdit");
        textEdit->setGeometry(QRect(590, 60, 231, 41));
        QFont font;
        font.setUnderline(false);
        font.setKerning(false);
        textEdit->setFont(font);
        textEdit->setStyleSheet(QString::fromUtf8("QTextEdit {\n"
"    background: transparent;\n"
"    border: none;\n"
"}"));
        textEdit->setFrameShape(QFrame::Shape::NoFrame);
        textEdit->setFrameShadow(QFrame::Shadow::Plain);
        textEdit->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        textEdit->setReadOnly(false);
        login1pushButton = new QPushButton(login);
        login1pushButton->setObjectName("login1pushButton");
        login1pushButton->setGeometry(QRect(730, 420, 80, 31));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Algerian")});
        font1.setPointSize(12);
        font1.setUnderline(false);
        login1pushButton->setFont(font1);
        login1pushButton->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"\n"
"background-color: rgb(255, 255, 255);"));
        email1 = new QLabel(login);
        email1->setObjectName("email1");
        email1->setGeometry(QRect(590, 150, 81, 31));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Segoe UI")});
        font2.setPointSize(15);
        font2.setBold(false);
        font2.setItalic(false);
        font2.setUnderline(false);
        email1->setFont(font2);
        email1->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        Password1 = new QLineEdit(login);
        Password1->setObjectName("Password1");
        Password1->setGeometry(QRect(590, 330, 391, 41));
        Password1->setStyleSheet(QString::fromUtf8("border-radius:25 px;"));
        Password1->setEchoMode(QLineEdit::EchoMode::Password);
        label_3 = new QLabel(login);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(670, 480, 231, 21));
        QFont font3;
        font3.setPointSize(12);
        font3.setUnderline(false);
        label_3->setFont(font3);
        label_3->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 127);"));
        frame_2 = new QFrame(login);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(0, 0, 511, 741));
        frame_2->setMinimumSize(QSize(311, 371));
        frame_2->setStyleSheet(QString::fromUtf8("QFrame{\n"
"	background-color: rgb(135, 137, 255);\n"
"    background: transparent;\n"
"	background-color: rgb(142, 90, 255);\n"
"   border radius: 25 px;\n"
"    border: none;\n"
"}"));
        textEdit_6 = new QTextEdit(frame_2);
        textEdit_6->setObjectName("textEdit_6");
        textEdit_6->setEnabled(true);
        textEdit_6->setGeometry(QRect(30, 0, 241, 41));
        textEdit_6->setStyleSheet(QString::fromUtf8("QTextEdit {\n"
"    background: transparent;\n"
"    border: none;\n"
"}"));
        textEdit_6->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        label = new QLabel(frame_2);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 80, 271, 491));
        QFont font4;
        font4.setPointSize(14);
        label->setFont(font4);
        label->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        lineEdit = new QLineEdit(login);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(590, 190, 391, 41));
        lineEdit->setStyleSheet(QString::fromUtf8("border - radius: 100 px;"));
        register1pushButton = new QPushButton(login);
        register1pushButton->setObjectName("register1pushButton");
        register1pushButton->setGeometry(QRect(700, 530, 151, 41));
        register1pushButton->setFont(font1);
        register1pushButton->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(0, 0, 0);"));
        label_2 = new QLabel(login);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(590, 290, 111, 31));
        label_2->setFont(font2);
        label_2->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
""));

        retranslateUi(login);

        QMetaObject::connectSlotsByName(login);
    } // setupUi

    void retranslateUi(QDialog *login)
    {
        login->setWindowTitle(QCoreApplication::translate("login", "Dialog", nullptr));
        textEdit->setHtml(QCoreApplication::translate("login", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:16pt; font-weight:700; font-style:italic; text-decoration: underline; color:#3690c8;\">Welcome Back</span></p></body></html>", nullptr));
        login1pushButton->setText(QCoreApplication::translate("login", "Login", nullptr));
        email1->setText(QCoreApplication::translate("login", "Email:", nullptr));
        label_3->setText(QCoreApplication::translate("login", "Doesn't have account ?", nullptr));
        textEdit_6->setHtml(QCoreApplication::translate("login", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:14pt; font-weight:700; color:#7ef225;\">Welcome to TuiPath</span></p></body></html>", nullptr));
        label->setText(QCoreApplication::translate("login", "Smart Attendance\n"
"\n"
"Fee Management \n"
"\n"
"Progress Tracking", nullptr));
        lineEdit->setText(QString());
        register1pushButton->setText(QCoreApplication::translate("login", "REGISTER NOW", nullptr));
        label_2->setText(QCoreApplication::translate("login", "Password:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class login: public Ui_login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
