#include <mainwindow.h>
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

    QFile logoFile(":/ui/LogoWindow.ui");
    logoFile.open(QFile::ReadOnly);
    QUiLoader loader;
    QWidget *logoPage = loader.load(&logoFile, this);
    logoFile.close();

    ui->stackedWidget->addWidget(logoPage);
    ui->stackedWidget->setCurrentWidget(logoPage);

    QString pythonPath = "C:/Users/ASUS/AppData/Local/Programs/Python/Python313/python.exe";
    QString workingDir = "C:/Qt_Files/server/backend";

    serverProcess->setWorkingDirectory(workingDir);
    serverProcess->setProgram(pythonPath);
    serverProcess->setArguments(QStringList() << "-m" << "uvicorn" << "main:app");

    connect(serverProcess, &QProcess::readyReadStandardOutput, this, [this]() {
        qDebug() << "stdout:" << serverProcess->readAllStandardOutput();
    });
    connect(serverProcess, &QProcess::readyReadStandardError, this, [this]() {
        qDebug() << "stderr:" << serverProcess->readAllStandardError();
    });

    connect(serverProcess, &QProcess::started, this, [this]() {
        qDebug() << "✅ Python server started!";
        QTimer::singleShot(2000, this, [this]() {
            QFile mainScreenFile(":/ui/mainwindow.ui");  // Correct path for resource file
            mainScreenFile.open(QFile::ReadOnly);
            QUiLoader loader;
            QWidget *mainScreen = loader.load(&mainScreenFile, this);
            mainScreenFile.close();

            ui->stackedWidget->addWidget(mainScreen);
            ui->stackedWidget->setCurrentWidget(mainScreen);

            QPushButton *refreshBtn = mainScreen->findChild<QPushButton*>("refreshButton");
            tableWidget = mainScreen->findChild<QTableWidget*>("tableWidget");

            if (refreshBtn && tableWidget) {
                connect(refreshBtn, &QPushButton::clicked, this, &MainWindow::fetchData);
                fetchData();
            } else {
                qDebug() << "❌ Could not find table or refresh button.";
            }
        });
    });

    connect(serverProcess, QOverload<QProcess::ProcessError>::of(&QProcess::errorOccurred),
            this, [](QProcess::ProcessError error) {
                qDebug() << "❌ QProcess error:" << error;
            });

    serverProcess->start();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete serverProcess;
    delete networkManager;
}

void MainWindow::fetchData()
{
    if (!tableWidget) {
        qDebug() << "❌ tableWidget is null!";
        return;
    }

    QUrl url("http://127.0.0.1:8001/table");
    QNetworkRequest request(url);
    QNetworkReply *reply = networkManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        if (reply->error()) {
            QMessageBox::critical(this, "Connection Error", "❌ Failed to reach server.\n" + reply->errorString());
            reply->deleteLater();
            return;
        }

        QByteArray data = reply->readAll();
        QJsonDocument doc = QJsonDocument::fromJson(data);
        QJsonArray array = doc.array();

        tableWidget->clear();
        tableWidget->setRowCount(array.size());

        if (!array.isEmpty()) {
            QStringList headers = array[0].toObject().keys();
            tableWidget->setColumnCount(headers.size());
            tableWidget->setHorizontalHeaderLabels(headers);
        }

        for (int i = 0; i < array.size(); ++i) {
            QJsonObject obj = array[i].toObject();
            int col = 0;
            for (const QString &key : obj.keys()) {
                tableWidget->setItem(i, col++, new QTableWidgetItem(obj[key].toVariant().toString()));
            }
        }

        reply->deleteLater();
    });
}
