#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "logowindow.h"
#include <QMainWindow>
#include <ui_logowindow.h>
#include <logowindow.h>
#include <QNetworkAccessManager>
#include <QProcess>
#include <QTableWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    LogoWindow * logoWindow;
    QNetworkAccessManager *networkManager;
    QProcess *serverProcess;
    QTableWidget *tableWidget = nullptr;
        void fetchData();

private slots:

    void init_objects();

    void init_stack_widget();

    void connectSignalSlot();

    void changePage(int index);


};

#endif // MAINWINDOW_H
