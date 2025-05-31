#include "splashscreen.h"

SplashScreen::SplashScreen(QWidget *parent) : QWidget(parent) {
    setFixedSize(640, 360);
    setWindowFlags(Qt::FramelessWindowHint);

    player = new QMediaPlayer(this);
    videoWidget = new QVideoWidget(this);
    player->setVideoOutput(videoWidget);
    videoWidget->setGeometry(0, 0, width(), height());

    player->setSource(QUrl::fromLocalFile("splash.mp4")); // 🔧 Place next to .exe
    player->play();

    timer = new QTimer(this);
    timer->setInterval(2000);
    connect(timer, &QTimer::timeout, this, [this]() {
        player->stop();
        emit splashFinished();
    });
    timer->start();
}
