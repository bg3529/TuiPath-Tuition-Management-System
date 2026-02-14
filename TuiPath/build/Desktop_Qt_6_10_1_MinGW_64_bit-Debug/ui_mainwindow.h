/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *login1pushButton;
    QPushButton *register1pushButton;
    QFrame *frame_2;
    QTextEdit *textEdit_5;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1024, 768);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: rgb(137, 101, 255);"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        login1pushButton = new QPushButton(centralwidget);
        login1pushButton->setObjectName("login1pushButton");
        login1pushButton->setGeometry(QRect(320, 260, 80, 31));
        QFont font;
        font.setFamilies({QString::fromUtf8("Algerian")});
        font.setPointSize(12);
        font.setUnderline(false);
        login1pushButton->setFont(font);
        login1pushButton->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"\n"
"background-color: rgb(255, 255, 255);"));
        register1pushButton = new QPushButton(centralwidget);
        register1pushButton->setObjectName("register1pushButton");
        register1pushButton->setGeometry(QRect(510, 260, 151, 41));
        register1pushButton->setFont(font);
        register1pushButton->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(0, 0, 0);"));
        frame_2 = new QFrame(centralwidget);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(840, 670, 311, 371));
        frame_2->setMinimumSize(QSize(311, 371));
        frame_2->setStyleSheet(QString::fromUtf8("QFrame{\n"
"    background: transparent;\n"
"    border: none;\n"
"}"));
        textEdit_5 = new QTextEdit(frame_2);
        textEdit_5->setObjectName("textEdit_5");
        textEdit_5->setEnabled(true);
        textEdit_5->setGeometry(QRect(10, 80, 291, 291));
        textEdit_5->setStyleSheet(QString::fromUtf8("QTextEdit {\n"
"    background: transparent;\n"
"    border: none;\n"
"}"));
        textEdit_5->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1024, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        login1pushButton->setText(QCoreApplication::translate("MainWindow", "Login", nullptr));
        register1pushButton->setText(QCoreApplication::translate("MainWindow", "REGISTER NOW", nullptr));
        textEdit_5->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
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
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
