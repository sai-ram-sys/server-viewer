#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QProcess>
#include <QTimer>
#include "ui_mainwindow.h"  // Include this to provide the full definition of Ui::MainWindow

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
    Ui::MainWindow *ui; // Full definition of Ui::MainWindow should now be available
    QNetworkAccessManager *networkManager;
    QProcess *serverProcess;

    void fetchData();
};

#endif // MAINWINDOW_H
