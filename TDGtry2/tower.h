#ifndef TOWER_H
#define TOWER_H

#include <QObject>
#include<QPoint>
#include<QPixmap>

class Tower : public QObject
{
    Q_OBJECT
public:
    //explicit Tower(QObject *parent = nullptr);
    Tower(QPoint pos, QString pixFileName);  //pos位置，pixFileName文件路径
    void draw(QPainter * painter);


private:
    QPoint _pos;
    QPixmap pixmap;

signals:

public slots:
};

#endif // TOWER_H
