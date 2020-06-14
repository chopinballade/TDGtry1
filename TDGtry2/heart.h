#ifndef HEART_H
#define HEART_H

#include <QObject>
#include<QPropertyAnimation>
#include<QPoint>
#include<QPixmap>
#include<QPainter>

class Heart : public QObject
{
    Q_OBJECT
public:
    Heart(int HP, QString filename);
    void draw(QPainter * painter);
    int _currentHP;
    QPixmap _pixmap;

signals:

public slots:
};

#endif // HEART_H
