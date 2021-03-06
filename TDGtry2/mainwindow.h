#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QPainter>
#include<QPixmap>
#include<QPaintEvent>
#include<QPushButton>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    void paintEvent(QPaintEvent*); //每次打开mainwindow都会调用（三次）
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void showGameName(QPainter * painter);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
