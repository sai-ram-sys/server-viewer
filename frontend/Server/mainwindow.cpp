#include "mainwindow.h"
#include "qnetworkreply.h"
#include "ui_mainwindow.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QMessageBox>
#include <QDebug>
#include <QUrl>
#include <QNetworkRequest>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    serverProcess(new QProcess(this)),
    networkManager(new QNetworkAccessManager(this))
{
    ui->setupUi(this);

    // Set up splash screen
    ui->stackedWidget->setCurrentIndex(0);
    ui->labelSplash->setPixmap(QPixmap(":/resources/splash.png").scaled(ui->labelSplash->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    // Start the Python server
    QString pythonPath = "C:/Users/ASUS/AppData/Local/Programs/Python/Python311/python.exe"; // Adjust as needed
    QString scriptPath = "C:/path/to/main.py"; // Adjust this path

    serverProcess->setProgram(pythonPath);
    serverProcess->setArguments(QStringList() << scriptPath);

    connect(serverProcess, &QProcess::readyReadStandardOutput, this, [this]() {
        qDebug() << serverProcess->readAllStandardOutput();
    });
    connect(serverProcess, &QProcess::readyReadStandardError, this, [this]() {
        qDebug() << serverProcess->readAllStandardError();
    });

    serverProcess->start();
    if (!serverProcess->waitForStarted()) {
        qDebug() << "❌ Failed to start Python server.";
    }

    // Switch to the main screen after 2 seconds and fetch data
    QTimer::singleShot(2000, this, [this]() {
        ui->stackedWidget->setCurrentIndex(1);
        fetchData();
    });

    // Connect the refresh button to fetch data again
    connect(ui->refreshButton, &QPushButton::clicked, this, &MainWindow::fetchData);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::fetchData()
{
    QUrl url("http://127.0.0.1:8000/table");
    QNetworkRequest request(url);
    QNetworkReply *reply = networkManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        if (reply->error()) {
            QMessageBox::critical(this, "Connection Error", "❌ Failed to reach server.\n" + reply->errorString());
            reply -> deleteLater();
            return;
        }

        QByteArray data = reply->readAll();
        QJsonDocument doc = QJsonDocument::fromJson(data);
        QJsonArray array = doc.array();

        ui->tableWidget->clear();
        ui->tableWidget->setRowCount(array.size());

        if (!array.isEmpty()) {
            QStringList headers = array[0].toObject().keys();
            ui->tableWidget->setColumnCount(headers.size());
            ui->tableWidget->setHorizontalHeaderLabels(headers);
        }

        for (int i = 0; i < array.size(); ++i) {
            QJsonObject obj = array[i].toObject();
            int col = 0;
            for (const QString &key : obj.keys()) {
                ui->tableWidget->setItem(i, col++, new QTableWidgetItem(obj[key].toVariant().toString()));
            }
        }

        reply->deleteLater();
    });
}
