#include "mainapp.h"
#include <QVBoxLayout>
#include <QMessageBox>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonArray>

MainApp::MainApp(QWidget *parent) : QWidget(parent) {
    table = new QTableWidget(this);
    refreshBtn = new QPushButton("🔄 Refresh", this);
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(refreshBtn);
    layout->addWidget(table);

    manager = new QNetworkAccessManager(this);
    connect(refreshBtn, &QPushButton::clicked, this, &MainApp::fetchData);
    connect(manager, &QNetworkAccessManager::finished, this, &MainApp::onReply);

    spinnerOverlay = new QLabel(this);
    spinnerOverlay->setStyleSheet("background-color: rgba(0, 0, 0, 128);");
    spinnerOverlay->setAlignment(Qt::AlignCenter);
    spinnerOverlay->setGeometry(this->rect());
    spinnerOverlay->hide();

    spinner = new QMovie("spinner.gif");
    spinnerOverlay->setMovie(spinner);

    fetchData();
}

void MainApp::fetchData() {
    spinnerOverlay->show();
    spinner->start();
    manager->get(QNetworkRequest(QUrl("http://127.0.0.1:8000/table")));
}

void MainApp::onReply(QNetworkReply *reply) {
    spinner->stop();
    spinnerOverlay->hide();

    if (reply->error()) {
        showError(reply->errorString());
        reply->deleteLater();
        return;
    }

    auto data = reply->readAll();
    auto doc = QJsonDocument::fromJson(data);
    auto array = doc.array();

    table->clear();
    table->setRowCount(array.size());

    QStringList headers;
    if (!array.isEmpty()) {
        // Set headers from the first object
        headers = array[0].toObject().keys();
        table->setColumnCount(headers.size());
        table->setHorizontalHeaderLabels(headers);
    }

    // Fill data row by row using consistent headers
    for (int i = 0; i < array.size(); ++i) {
        QJsonObject obj = array[i].toObject();
        for (int j = 0; j < headers.size(); ++j) {
            QString key = headers[j];
            QString value = obj.contains(key) ? obj[key].toVariant().toString() : "N/A";
            table->setItem(i, j, new QTableWidgetItem(value));
        }
    }

    reply->deleteLater();
}


void MainApp::showError(const QString &msg) {
    QMessageBox::critical(this, "Error", "Failed to fetch data: " + msg);
}
