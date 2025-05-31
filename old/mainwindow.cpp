#include "mainwindow.h"
#include "logowindow.h"
#include "ui_mainwindow.h"
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QMessageBox>
#include <QDebug>
#include <QUrl>
#include <QNetworkRequest>
#include <QTimer>
#include <QProcess>
#include <QUiLoader>
#include <QFile>
#include <QPushButton>
#include <QTableWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    networkManager(new QNetworkAccessManager(this)),
    serverProcess(new QProcess(this))
{
    ui->setupUi(this);

        init_objects();

        init_stack_widget();

        connectSignalSlot();

}
MainWindow::~MainWindow()
{
    delete ui;
    delete serverProcess;
    delete networkManager;
}
void MainWindow::init_objects()
{
    logoWindow = new LogoWindow();
}


void MainWindow::init_stack_widget()
{
    ui->stackedWidget->addWidget(logoWindow); //index 0

    changePage(0);

}


void MainWindow::changePage(int index){

    ui->stackedWidget->setCurrentIndex(index);
}


void MainWindow::connectSignalSlot(){

    connect(this,SIGNAL(emitChangePage(int)),this,SLOT(changePage(int)),Qt::QueuedConnection);
    connect(logoWindow,SIGNAL(emitChangePage(int)),this,SLOT(changePage(int)),Qt::QueuedConnection);
}
