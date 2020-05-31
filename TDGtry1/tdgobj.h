#ifndef TDGOBJ_H
#define TDGOBJ_H
#include <QMediaPlayer>
#include <QImage>
#include <QPainter>
#include <string>
#include <icon.h>
#include <map>
using namespace std;
class TDGObj
{
public:
    TDGObj(){}

    void initObj(string type);  //初始化对象
    void show(QPainter * painter);  //展示出来

    void setPosX(int x){this->_pos_x=x;}  //设置坐标
    void setPosY(int y){this->_pos_y=y;}

    int getPosX() const{return this->_pos_x;}  //获取坐标
    int getPosY() const{return this->_pos_y;}
    int getHeight() const{return this->_icon.getHeight();}  //获取对象的高度和宽度
    int getWidth() const{return this->_icon.getWidth();}

    int getNextX(int direction);   //计算对象的下一个坐标
    int getNextY(int direction);

    virtual void onErase();  //虚函数。比如擦除一个敌人or水果时会发生音效等等事件

    string getObjType() const{
        return this->_icon.getTypeName();
    } //返回类名

protected:
    //所有坐标，单位均为游戏中的格

    QImage _pic;
    int _pos_x, _pos_y;//该物体在游戏中当前位置（左上角坐标）
    ICON _icon;//可以从 ICON类 中获取对象的素材，尺寸等信息

};

#endif // TDGOBJ_H
