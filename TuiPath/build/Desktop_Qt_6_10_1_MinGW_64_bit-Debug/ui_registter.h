/********************************************************************************
** Form generated from reading UI file 'registter.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTTER_H
#define UI_REGISTTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_registter
{
public:
    QWidget *widget_2;
    QLabel *createyouraccount;
    QLabel *label_4;
    QWidget *verticalWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label_5;
    QLineEdit *regfullname;
    QLabel *label_6;
    QLineEdit *regemail;
    QLabel *label_10;
    QComboBox *comboBox;
    QLabel *label_7;
    QLineEdit *regpassword;
    QLabel *label_8;
    QLineEdit *regcpassword;
    QLabel *label_9;
    QPushButton *pushButton_4;
    QPushButton *pushButton_3;
    QFrame *frame;
    QTextEdit *textEdit_2;
    QTextEdit *textEdit_3;

    void setupUi(QDialog *registter)
    {
        if (registter->objectName().isEmpty())
            registter->setObjectName("registter");
        registter->resize(1021, 768);
        registter->setStyleSheet(QString::fromUtf8("background-color: rgb(103, 103, 255);"));
        widget_2 = new QWidget(registter);
        widget_2->setObjectName("widget_2");
        widget_2->setGeometry(QRect(500, 30, 491, 691));
        widget_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        createyouraccount = new QLabel(widget_2);
        createyouraccount->setObjectName("createyouraccount");
        createyouraccount->setGeometry(QRect(90, 0, 231, 31));
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        createyouraccount->setFont(font);
        createyouraccount->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        label_4 = new QLabel(widget_2);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(50, 40, 321, 31));
        QFont font1;
        font1.setPointSize(12);
        label_4->setFont(font1);
        label_4->setStyleSheet(QString::fromUtf8("color: rgb(43, 43, 43);\n"
"background-color: rgb(248, 220, 200);\n"
"border:none;"));
        verticalWidget = new QWidget(widget_2);
        verticalWidget->setObjectName("verticalWidget");
        verticalWidget->setGeometry(QRect(20, 80, 441, 501));
        verticalWidget->setStyleSheet(QString::fromUtf8("border color : black;"));
        verticalLayout = new QVBoxLayout(verticalWidget);
        verticalLayout->setSpacing(5);
        verticalLayout->setObjectName("verticalLayout");
        label_5 = new QLabel(verticalWidget);
        label_5->setObjectName("label_5");
        label_5->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"border:none;"));

        verticalLayout->addWidget(label_5);

        regfullname = new QLineEdit(verticalWidget);
        regfullname->setObjectName("regfullname");
        regfullname->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));

        verticalLayout->addWidget(regfullname);

        label_6 = new QLabel(verticalWidget);
        label_6->setObjectName("label_6");
        label_6->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));

        verticalLayout->addWidget(label_6);

        regemail = new QLineEdit(verticalWidget);
        regemail->setObjectName("regemail");
        regemail->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));

        verticalLayout->addWidget(regemail);

        label_10 = new QLabel(verticalWidget);
        label_10->setObjectName("label_10");
        label_10->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));

        verticalLayout->addWidget(label_10);

        comboBox = new QComboBox(verticalWidget);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");
        QFont font2;
        font2.setBold(false);
        comboBox->setFont(font2);
        comboBox->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));

        verticalLayout->addWidget(comboBox);

        label_7 = new QLabel(verticalWidget);
        label_7->setObjectName("label_7");
        label_7->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));

        verticalLayout->addWidget(label_7);

        regpassword = new QLineEdit(verticalWidget);
        regpassword->setObjectName("regpassword");
        regpassword->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        regpassword->setEchoMode(QLineEdit::EchoMode::Password);

        verticalLayout->addWidget(regpassword);

        label_8 = new QLabel(verticalWidget);
        label_8->setObjectName("label_8");
        label_8->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));

        verticalLayout->addWidget(label_8);

        regcpassword = new QLineEdit(verticalWidget);
        regcpassword->setObjectName("regcpassword");
        regcpassword->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        regcpassword->setEchoMode(QLineEdit::EchoMode::Password);

        verticalLayout->addWidget(regcpassword);

        label_9 = new QLabel(widget_2);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(80, 640, 321, 31));
        label_9->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        pushButton_4 = new QPushButton(widget_2);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setGeometry(QRect(300, 640, 51, 29));
        QFont font3;
        font3.setBold(true);
        pushButton_4->setFont(font3);
        pushButton_4->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color: rgb(250, 166, 125);"));
        pushButton_3 = new QPushButton(widget_2);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(30, 590, 419, 42));
        QFont font4;
        font4.setPointSize(15);
        font4.setBold(true);
        pushButton_3->setFont(font4);
        pushButton_3->setStyleSheet(QString::fromUtf8("background-color: rgb(16, 112, 255);\n"
"color: rgb(0, 0, 0);"));
        frame = new QFrame(registter);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(40, 80, 491, 611));
        frame->setMinimumSize(QSize(311, 371));
        frame->setStyleSheet(QString::fromUtf8("QFrame{\n"
"	background-color: rgb(106, 255, 225);\n"
"    background: transparent;\n"
"    border: none;\n"
"}"));
        textEdit_2 = new QTextEdit(frame);
        textEdit_2->setObjectName("textEdit_2");
        textEdit_2->setEnabled(true);
        textEdit_2->setGeometry(QRect(30, 0, 241, 41));
        textEdit_2->setStyleSheet(QString::fromUtf8("QTextEdit {\n"
"    background: transparent;\n"
"    border: none;\n"
"}"));
        textEdit_2->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        textEdit_3 = new QTextEdit(frame);
        textEdit_3->setObjectName("textEdit_3");
        textEdit_3->setEnabled(true);
        textEdit_3->setGeometry(QRect(10, 80, 291, 291));
        textEdit_3->setStyleSheet(QString::fromUtf8("QTextEdit {\n"
"	background-color: rgb(201, 255, 239);\n"
"    background: transparent;\n"
"    border: none;\n"
"}"));
        textEdit_3->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);

        retranslateUi(registter);

        QMetaObject::connectSlotsByName(registter);
    } // setupUi

    void retranslateUi(QDialog *registter)
    {
        registter->setWindowTitle(QCoreApplication::translate("registter", "Dialog", nullptr));
        createyouraccount->setText(QCoreApplication::translate("registter", "Create your account", nullptr));
        label_4->setText(QCoreApplication::translate("registter", "Get started with your college email", nullptr));
        label_5->setText(QCoreApplication::translate("registter", "Full Name:", nullptr));
        regfullname->setPlaceholderText(QCoreApplication::translate("registter", "Enter your full name", nullptr));
        label_6->setText(QCoreApplication::translate("registter", "Email:", nullptr));
        regemail->setPlaceholderText(QCoreApplication::translate("registter", "Enter your college email", nullptr));
        label_10->setText(QCoreApplication::translate("registter", "Select your role:", nullptr));
        comboBox->setItemText(0, QString());
        comboBox->setItemText(1, QCoreApplication::translate("registter", "Teacher", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("registter", "Student", nullptr));

        comboBox->setPlaceholderText(QCoreApplication::translate("registter", "Select your role", nullptr));
        label_7->setText(QCoreApplication::translate("registter", "Password", nullptr));
        regpassword->setPlaceholderText(QCoreApplication::translate("registter", "Enter password", nullptr));
        label_8->setText(QCoreApplication::translate("registter", "Confirm Password", nullptr));
        regcpassword->setPlaceholderText(QCoreApplication::translate("registter", "Confirm Password", nullptr));
        label_9->setText(QCoreApplication::translate("registter", "Already have an account , go to", nullptr));
        pushButton_4->setText(QCoreApplication::translate("registter", "Login", nullptr));
        pushButton_3->setText(QCoreApplication::translate("registter", "Register Now", nullptr));
        textEdit_2->setHtml(QCoreApplication::translate("registter", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:14pt; font-weight:700; color:#7ef225;\">Welcome to TuiPath</span></p></body></html>", nullptr));
        textEdit_3->setHtml(QCoreApplication::translate("registter", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"justify\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:26pt; font-weight:700; font-style:italic; color:#000000;\">.</span><span style=\" font-size:12pt; font-style:italic; color:#000000;\">Smart Attendance</span></p>\n"
"<p align=\"justify\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:12pt; font-style:italic"
                        "; color:#000000;\"><br /></p>\n"
"<p align=\"justify\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:26pt; font-weight:700; font-style:italic; color:#000000;\">.</span><span style=\" font-size:12pt; font-style:italic; color:#000000;\">Fee Management </span></p>\n"
"<p align=\"justify\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:12pt; font-style:italic; color:#000000;\"><br /></p>\n"
"<p align=\"justify\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:26pt; font-weight:700; font-style:italic; color:#000000;\">.</span><span style=\" font-size:12pt; font-style:italic; color:#000000;\">Progress Tracking</span></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class registter: public Ui_registter {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTTER_H
