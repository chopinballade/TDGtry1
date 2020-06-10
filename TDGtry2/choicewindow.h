#ifndef CHOICEWINDOW_H
#define CHOICEWINDOW_H

#include <QMainWindow>
#include<QPainter>
#include<QPixmap>
#include<QPaintEvent>
#include<QPushButton>
#include<QDebug>

class ChoiceWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChoiceWindow(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);

signals:

public slots:
};

#endif // CHOICEWINDOW_H
