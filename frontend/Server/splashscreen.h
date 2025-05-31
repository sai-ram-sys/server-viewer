#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include <QWidget>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QTimer>

class SplashScreen : public QWidget {
    Q_OBJECT
public:
    explicit SplashScreen(QWidget *parent = nullptr);

signals:
    void splashFinished();

private:
    QMediaPlayer *player;
    QVideoWidget *videoWidget;
    QTimer *timer;
};

#endif // SPLASHSCREEN_H
