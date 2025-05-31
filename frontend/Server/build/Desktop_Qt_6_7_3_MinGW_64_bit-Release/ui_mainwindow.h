/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mainWindow
{
public:
    QWidget *centralwidget;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QLabel *labelSplash;
    QWidget *page_2;
    QTableWidget *tableWidget;
    QPushButton *refreshButton;
    QMenuBar *menubar;
    QMenu *menuAnu_Server;
    QMenu *menu;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *mainWindow)
    {
        if (mainWindow->objectName().isEmpty())
            mainWindow->setObjectName("mainWindow");
        mainWindow->setEnabled(true);
        mainWindow->resize(800, 600);
        mainWindow->setTabShape(QTabWidget::TabShape::Rounded);
        centralwidget = new QWidget(mainWindow);
        centralwidget->setObjectName("centralwidget");
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(40, 30, 721, 471));
        page = new QWidget();
        page->setObjectName("page");
        labelSplash = new QLabel(page);
        labelSplash->setObjectName("labelSplash");
        labelSplash->setGeometry(QRect(200, 120, 201, 151));
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        tableWidget = new QTableWidget(page_2);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(20, 70, 681, 371));
        refreshButton = new QPushButton(page_2);
        refreshButton->setObjectName("refreshButton");
        refreshButton->setGeometry(QRect(30, 20, 80, 24));
        stackedWidget->addWidget(page_2);
        mainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(mainWindow);
        menubar->setObjectName("menubar");
        menubar->setEnabled(false);
        menubar->setGeometry(QRect(0, 0, 800, 21));
        menuAnu_Server = new QMenu(menubar);
        menuAnu_Server->setObjectName("menuAnu_Server");
        menu = new QMenu(menubar);
        menu->setObjectName("menu");
        mainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(mainWindow);
        statusbar->setObjectName("statusbar");
        mainWindow->setStatusBar(statusbar);

        menubar->addAction(menuAnu_Server->menuAction());
        menubar->addAction(menu->menuAction());

        retranslateUi(mainWindow);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(mainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *mainWindow)
    {
        mainWindow->setWindowTitle(QCoreApplication::translate("mainWindow", "MainWindow", nullptr));
        labelSplash->setText(QCoreApplication::translate("mainWindow", "TextLabel", nullptr));
        refreshButton->setText(QCoreApplication::translate("mainWindow", "Refresh Button", nullptr));
        menuAnu_Server->setTitle(QCoreApplication::translate("mainWindow", "Anu Server", nullptr));
        menu->setTitle(QString());
    } // retranslateUi

};

namespace Ui {
    class mainWindow: public Ui_mainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
