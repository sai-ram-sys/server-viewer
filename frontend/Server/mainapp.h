#ifndef MAINAPP_H
#define MAINAPP_H

#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QNetworkAccessManager>
#include <QMovie>
#include <QLabel>

class MainApp : public QWidget {
    Q_OBJECT
public:
    explicit MainApp(QWidget *parent = nullptr);

private slots:
    void fetchData();
    void onReply(QNetworkReply *reply);
    void showError(const QString &msg);

private:
    QTableWidget *table;
    QPushButton *refreshBtn;
    QLabel *spinnerOverlay;
    QMovie *spinner;
    QNetworkAccessManager *manager;
};

#endif // MAINAPP_H
