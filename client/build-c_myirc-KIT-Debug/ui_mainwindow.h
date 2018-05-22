/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QTextEdit *sendText;
    QPushButton *sendBtn;
    QFrame *line;
    QListView *channelList;
    QListView *peopleList;
    QLabel *label;
    QLabel *label_2;
    QTextEdit *channelText;
    QPushButton *connectBtn;
    QLabel *label_3;
    QPushButton *quitChannelBtn;
    QPushButton *refreshChannelBtn;
    QPushButton *peopleChannelBtn;
    QPushButton *clearChannleBtn;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1280, 720);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        sendText = new QTextEdit(centralWidget);
        sendText->setObjectName(QStringLiteral("sendText"));
        sendText->setGeometry(QRect(650, 610, 511, 101));
        sendBtn = new QPushButton(centralWidget);
        sendBtn->setObjectName(QStringLiteral("sendBtn"));
        sendBtn->setGeometry(QRect(1170, 610, 101, 101));
        line = new QFrame(centralWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(630, 0, 20, 721));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        channelList = new QListView(centralWidget);
        channelList->setObjectName(QStringLiteral("channelList"));
        channelList->setGeometry(QRect(10, 90, 251, 621));
        peopleList = new QListView(centralWidget);
        peopleList->setObjectName(QStringLiteral("peopleList"));
        peopleList->setGeometry(QRect(270, 90, 361, 621));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 50, 161, 31));
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        font.setItalic(false);
        font.setWeight(75);
        label->setFont(font);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(270, 50, 271, 31));
        QFont font1;
        font1.setPointSize(14);
        font1.setBold(true);
        font1.setWeight(75);
        label_2->setFont(font1);
        channelText = new QTextEdit(centralWidget);
        channelText->setObjectName(QStringLiteral("channelText"));
        channelText->setGeometry(QRect(650, 50, 621, 551));
        connectBtn = new QPushButton(centralWidget);
        connectBtn->setObjectName(QStringLiteral("connectBtn"));
        connectBtn->setGeometry(QRect(10, 10, 251, 31));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(660, 10, 351, 31));
        label_3->setFont(font1);
        quitChannelBtn = new QPushButton(centralWidget);
        quitChannelBtn->setObjectName(QStringLiteral("quitChannelBtn"));
        quitChannelBtn->setGeometry(QRect(1140, 10, 131, 31));
        refreshChannelBtn = new QPushButton(centralWidget);
        refreshChannelBtn->setObjectName(QStringLiteral("refreshChannelBtn"));
        refreshChannelBtn->setGeometry(QRect(180, 50, 80, 31));
        peopleChannelBtn = new QPushButton(centralWidget);
        peopleChannelBtn->setObjectName(QStringLiteral("peopleChannelBtn"));
        peopleChannelBtn->setGeometry(QRect(550, 50, 80, 31));
        clearChannleBtn = new QPushButton(centralWidget);
        clearChannleBtn->setObjectName(QStringLiteral("clearChannleBtn"));
        clearChannleBtn->setGeometry(QRect(1020, 10, 111, 31));
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        sendBtn->setText(QApplication::translate("MainWindow", "SEND", 0));
        label->setText(QApplication::translate("MainWindow", "Channels", 0));
        label_2->setText(QApplication::translate("MainWindow", "People", 0));
        connectBtn->setText(QApplication::translate("MainWindow", "Connect", 0));
        label_3->setText(QApplication::translate("MainWindow", "Messages", 0));
        quitChannelBtn->setText(QApplication::translate("MainWindow", "Quit channel", 0));
        refreshChannelBtn->setText(QApplication::translate("MainWindow", "Refresh", 0));
        peopleChannelBtn->setText(QApplication::translate("MainWindow", "Refresh", 0));
        clearChannleBtn->setText(QApplication::translate("MainWindow", "Clear channel", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
