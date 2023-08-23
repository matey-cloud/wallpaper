/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QFrame *header;
    QPushButton *closeButton;
    QPushButton *minButton;
    QPushButton *setButton;
    QFrame *search;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QPushButton *searchButton;
    QFrame *content;
    QStackedWidget *stackedWidget;
    QWidget *homePage;
    QListWidget *listWidget;
    QWidget *collectPage;
    QListWidget *listWidget_2;
    QPushButton *homeButton;
    QPushButton *collectButton;
    QFrame *tool;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1007, 735);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        widget = new QWidget(centralwidget);
        widget->setObjectName("widget");
        header = new QFrame(widget);
        header->setObjectName("header");
        header->setGeometry(QRect(0, 0, 981, 21));
        header->setFrameShape(QFrame::StyledPanel);
        header->setFrameShadow(QFrame::Raised);
        closeButton = new QPushButton(header);
        closeButton->setObjectName("closeButton");
        closeButton->setGeometry(QRect(960, 0, 21, 21));
        closeButton->setStyleSheet(QString::fromUtf8("border-image: url(:/images/close.ico);"));
        minButton = new QPushButton(header);
        minButton->setObjectName("minButton");
        minButton->setGeometry(QRect(930, 0, 21, 21));
        minButton->setStyleSheet(QString::fromUtf8("border-image: url(:/images/min.ico);"));
        setButton = new QPushButton(header);
        setButton->setObjectName("setButton");
        setButton->setGeometry(QRect(900, 0, 21, 21));
        setButton->setStyleSheet(QString::fromUtf8("border-image: url(:/images/set.ico);"));
        search = new QFrame(widget);
        search->setObjectName("search");
        search->setGeometry(QRect(0, 20, 981, 61));
        search->setFrameShape(QFrame::StyledPanel);
        search->setFrameShadow(QFrame::Raised);
        lineEdit = new QLineEdit(search);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(400, 20, 481, 31));
        pushButton = new QPushButton(search);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(60, 20, 101, 29));
        pushButton->setStyleSheet(QString::fromUtf8("border-image: url(:/images/title.ico);\n"
"font: 12pt \"\345\215\216\346\226\207\350\241\214\346\245\267\";"));
        searchButton = new QPushButton(search);
        searchButton->setObjectName("searchButton");
        searchButton->setGeometry(QRect(900, 20, 41, 31));
        content = new QFrame(widget);
        content->setObjectName("content");
        content->setGeometry(QRect(0, 110, 981, 551));
        content->setFrameShape(QFrame::StyledPanel);
        content->setFrameShadow(QFrame::Raised);
        stackedWidget = new QStackedWidget(content);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(40, 50, 911, 491));
        homePage = new QWidget();
        homePage->setObjectName("homePage");
        listWidget = new QListWidget(homePage);
        listWidget->setObjectName("listWidget");
        listWidget->setGeometry(QRect(10, 20, 891, 461));
        listWidget->setLayoutDirection(Qt::LeftToRight);
        stackedWidget->addWidget(homePage);
        collectPage = new QWidget();
        collectPage->setObjectName("collectPage");
        listWidget_2 = new QListWidget(collectPage);
        listWidget_2->setObjectName("listWidget_2");
        listWidget_2->setGeometry(QRect(10, 20, 891, 461));
        listWidget_2->setLayoutDirection(Qt::LeftToRight);
        stackedWidget->addWidget(collectPage);
        homeButton = new QPushButton(content);
        homeButton->setObjectName("homeButton");
        homeButton->setGeometry(QRect(50, 10, 92, 29));
        collectButton = new QPushButton(content);
        collectButton->setObjectName("collectButton");
        collectButton->setGeometry(QRect(170, 10, 92, 29));
        tool = new QFrame(widget);
        tool->setObjectName("tool");
        tool->setGeometry(QRect(30, 660, 921, 51));
        tool->setFrameShape(QFrame::StyledPanel);
        tool->setFrameShadow(QFrame::Raised);

        verticalLayout->addWidget(widget);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);
        QObject::connect(closeButton, &QPushButton::clicked, MainWindow, qOverload<>(&QMainWindow::close));
        QObject::connect(minButton, &QPushButton::clicked, MainWindow, qOverload<>(&QMainWindow::showMinimized));

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        closeButton->setText(QString());
        minButton->setText(QString());
        setButton->setText(QString());
        pushButton->setText(QString());
        searchButton->setText(QCoreApplication::translate("MainWindow", "\346\220\234\347\264\242", nullptr));
        homeButton->setText(QCoreApplication::translate("MainWindow", "\351\246\226\351\241\265", nullptr));
        collectButton->setText(QCoreApplication::translate("MainWindow", "\346\224\266\350\227\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
