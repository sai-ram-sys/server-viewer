#include "logowindow.h"
#include "ui_logowindow.h"
#include <QPixmap>
#include <QDebug>

LogoWindow::LogoWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LogoWindow)
{
    ui->setupUi(this);

    QPixmap splashPixmap(":/images/hi.png");
    if (splashPixmap.isNull()) {
        qDebug() << "❌ Error: Splash image not found!";
    } else {
        qDebug() << "✅ Splash image loaded successfully!";
        ui->labelSplash->setPixmap(splashPixmap.scaled(
            ui->labelSplash->size(),
            Qt::KeepAspectRatio,
            Qt::SmoothTransformation));
    }
}

LogoWindow::~LogoWindow()
{
    delete ui;
}
