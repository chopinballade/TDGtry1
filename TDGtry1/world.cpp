#include "world.h"
#include "icon.h"
#include "tdgobj.h"
#include <QMediaPlayer>
#include<iostream>
using namespace std;

//World::~World(){
//    delete this->_player;
//}

void World::initWorld(string mapFile){
    //TODO 下面的内容应该改为从地图文件装载

    QMediaPlayer * player = new QMediaPlayer;     //this part is for playing background music
    player->setMedia(QUrl("C:\\Users\\bobomei\\Desktop\\DAZUOYE\\bgm\\bgm1_start"));
    player->setVolume(10);
    player->play();


}


void World::show(QPainter * painter){
    int n = this->_objs.size();
    for (int i=0;i<n;i++){
        this->_objs[i]->show(painter);
    }
//    this->_player->show(painter);

}


