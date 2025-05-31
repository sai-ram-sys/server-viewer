/********************************************************************************
** Form generated from reading UI file 'logowindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGOWINDOW_H
#define UI_LOGOWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LogoWindow
{
public:
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLabel *labelSplash;

    void setupUi(QWidget *LogoWindow)
    {
        if (LogoWindow->objectName().isEmpty())
            LogoWindow->setObjectName("LogoWindow");
        LogoWindow->resize(400, 300);
        gridLayoutWidget = new QWidget(LogoWindow);
        gridLayoutWidget->setObjectName("gridLayoutWidget");
        gridLayoutWidget->setGeometry(QRect(100, 40, 227, 227));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        labelSplash = new QLabel(gridLayoutWidget);
        labelSplash->setObjectName("labelSplash");
        labelSplash->setPixmap(QPixmap(QString::fromUtf8(":/images/hi.png")));
        labelSplash->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout->addWidget(labelSplash, 0, 0, 1, 1);


        retranslateUi(LogoWindow);

        QMetaObject::connectSlotsByName(LogoWindow);
    } // setupUi

    void retranslateUi(QWidget *LogoWindow)
    {
        LogoWindow->setWindowTitle(QCoreApplication::translate("LogoWindow", "Form", nullptr));
        labelSplash->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class LogoWindow: public Ui_LogoWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGOWINDOW_H
