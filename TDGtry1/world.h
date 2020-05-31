#ifndef WORLD_H
#define WORLD_H
#include "tdgobj.h"
#include <vector>
#include <string>
#include <QPainter>
#include<iostream>
using namespace std;

class World         //这个类主要用于处理游戏世界里发生的东西（不管图片展示、计时器这些事情）
{
public:
//    World(){this->_player = new Player;}
//    ~World();
    void initWorld(string mapFile);   //初始化

    void show(QPainter * painter);
        //显示游戏世界所有对象。画出来
//    void handlePlayerMove(int direction, int steps);
//        //假定只有一个玩家。玩家的运动

private:
    vector<TDGObj *> _objs;  //去tdgobj.h
//    Player * _player;
};

#endif // WORLD_H
