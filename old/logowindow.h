#ifndef LOGOWINDOW_H
#define LOGOWINDOW_H

#include <QWidget>

namespace Ui {
class LogoWindow;
}

class LogoWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LogoWindow(QWidget *parent = nullptr);
    ~LogoWindow();

private slots:
    void on_clickBtn_clicked();



private:
    Ui::LogoWindow *ui;
};

#endif // LOGOWINDOW_H
