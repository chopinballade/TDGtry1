#include "choicewindow.h"
#include<QPainter>
#include<QPixmap>
#include<QPaintEvent>
#include<QPushButton>
#include<QMouseEvent>
#include<QDebug>
#include<QTimer>
#include<QMediaPlayer>
#include<QPixmap>
#include"mybutton.h"
#include"mainwindow.h"
#include"myobject.h"
#include"myobject2.h"
#include"enemy.h"
#include"heart.h"
#include <QtGlobal>
#include <QMessageBox>

ChoiceWindow::ChoiceWindow(QWidget *parent) :
    QMainWindow(parent),
    HP(30),wave(1)
{
    loadWave();

    this->setFixedSize(1100,700);
   //显示关卡选择界面的函数在下面单独的paintEvent
    MyButton * back_btn = new MyButton(":/button2.png"); //new一个“返回”按钮
    back_btn->setParent(this);  //指定父类
    back_btn->setIconSize(QSize(80,80));//这几步使得按钮比例按原图且可以调整大小
    back_btn->move(45,40); //设置返回按钮在屏幕的位置

    connect(back_btn, &MyButton::clicked, this, [=](){
        emit chooseBack();  //emit用于发送signal。chooseback()是添加在ChoiceWindow类里的信号函数。
    });



    //按下一个“建塔”按钮就能创建一个塔
    MyButton * setTower1 = new MyButton(":/button3.jpg");
    setTower1->setParent(this);
    setTower1->move(220,90);  //“建塔”按钮的位置
    connect(setTower1,&MyButton::clicked,this,&ChoiceWindow::set_tower1);

//    MyButton * setTower2 = new MyButton(":/button3.jpg");
//    setTower2->setParent(this);
//    setTower2->move(420,90);  //“建塔”按钮的位置
//    connect(setTower2,&MyButton::clicked,this,&ChoiceWindow::set_tower2);

//    MyButton * setTower3 = new MyButton(":/button3.jpg");
//    setTower3->setParent(this);
//    setTower3->move(620,90);  //“建塔”按钮的位置
//    connect(setTower3,&MyButton::clicked,this,&ChoiceWindow::set_tower3);

//    MyButton * setTower4 = new MyButton(":/button3.jpg");
//    setTower4->setParent(this);
//    setTower4->move(820,90);  //“建塔”按钮的位置
//    connect(setTower4,&MyButton::clicked,this,&ChoiceWindow::set_tower4);




//    //举例：按下一个“ ”按钮就能创造一个类似子弹的？可在指定两点之间运动的myobject类物体（视频14:30开始）
//    MyButton * addObject = new MyButton(":/button3.jpg");
//    addObject->setParent(this);
//    addObject->move(730,70);  //“发射子弹”按钮位置
//    connect(addObject,&MyButton::clicked,this,&ChoiceWindow::addMyObject);
//      //创建与建塔函数addMyObject()的connect

//    QTimer * timer1 = new QTimer(this);
//    connect(timer1, &QTimer::timeout, this, &ChoiceWindow::showEnemy);    //暂时不用showEnemy函数
//        //timeout--时间开始，this界面，执行的是choicewindow类的showEnemy函数
//    timer1->start(5000);  //从0毫秒开始，每______毫秒触发一次showEnemy函数，即new一个enemy出来。



//    QTimer * timer2 = new QTimer(this);
//    connect(timer2, &QTimer::timeout, this, &ChoiceWindow::updateScene);
//        //timeout--时间开始，this界面，执行的是choicewindow类的updatescene函数
//    timer2->start(10);  //从0毫秒开始，每10毫秒触发一次QTimer::timeout，即触发一次updatescene以更新界面，达到动画效果。
//  //这里关于游戏开始和更新界面的函数，改成了下面几行试一试


    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateScene()));
    timer->start(10);   //这个更新时间间隔越短，所有的运动速度也会按比例加快

    QTimer::singleShot(300, this, SLOT(gameStart()));// 设置300ms后游戏启动

}




//点击对应位置按钮建塔：
void ChoiceWindow::set_tower1(){    //点击“+”建塔按钮建一个固定了位置的塔

    Tower * a_new_tower = new Tower(QPoint(245,185), this);   //new一个新塔，设置位置。
    qDebug()<<"a new tower is newed.";  //这句话用来检验上面那一行有没有运行。发现可以运行，说明问题出在tower_list这里。

    tower_list.push_back(a_new_tower);//把这个刚创建好的塔放进QList里面，方法类似vector。
       //ChoiceWindow类private:  QList<Tower*> tower_list;

    update();  //若去掉这句函数，则需要最小化一下窗口才能显示出新建造的塔。因为重新打开窗口时自动update。不如自己写出来就不会出现这种情况。
}

//void ChoiceWindow::set_tower2(){
//    Tower * tower = new Tower(QPoint(445,185), this);
//    tower_list.push_back(tower);
//    update();
//}
//void ChoiceWindow::set_tower3(){
//    Tower * tower = new Tower(QPoint(645,185), this);
//    tower_list.push_back(tower);
//    update();
//}
//void ChoiceWindow::set_tower4(){
//    Tower * tower = new Tower(QPoint(845,185), this);
//    tower_list.push_back(tower);
//    update();
//}




//void ChoiceWindow::mousePressEvent(QMouseEvent *event){  //备用建塔方式，鼠标点击哪里就在哪里建塔
//    QPoint pressPos = event->pos();
//    Tower * tower = new Tower(pressPos,this);
//    tower_list.push_back(tower);
//    update();
//}





void ChoiceWindow::paintEvent(QPaintEvent *){ //每次打开choicewindow都会调用
    QPainter painter(this);
    QPixmap pixmap(":/TDGmap1.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pixmap);

    showInfo(&painter);   //输出HP和wave的文字框。showInfo函数的实现在下面

    if (gameEnded || gameWin){
        QString text = gameEnded ? "SORRY, YOU LOSE...." : "GOOD JOB! YOU WIN";
        QPainter painter(this);
        painter.setPen(QPen(Qt::white));
        painter.setFont(QFont("Comic Sans MS", 36 ));
        painter.drawText(QRect(160,245,1000,500), text);
        return;
    }

    foreach(Tower * tower, tower_list){   //foreach类似for。类型是Tower*的tower，在tower_list中找。
        tower->draw(&painter);
    }//建塔显示
    foreach (Enemy * enemy, enemy_list) {   //注意这里enemy的那句“Enemy * enemy”放到本cpp里的最上面去了
        enemy->draw(&painter);
    }//建enemy显示
    foreach (MyObject * object, bullet_list) {
        object->draw(&painter);
    }//建myobject(即子弹)显示。这里要改成判断距离自动发射

    Heart heart( ":/heart.png" );
    heart.draw(&painter);  //画心
}


void ChoiceWindow::gameOverScene(){
    if (gameEnded==false){
        gameEnded=true;
    }
}

void ChoiceWindow::HPDamage(int damage){
    this->HP -= damage;
    if (HP <= 0){
        gameOverScene();
    }
}

void ChoiceWindow::deleteEnemy(Enemy *enemy)
{
    Q_ASSERT(enemy);

    enemy_list.removeOne(enemy);
    delete enemy;

    if (enemy_list.empty()){
        ++ wave;
        if (!loadWave()){
            gameWin = true;
        }
    }
}

void ChoiceWindow::addBulletToList(MyObject *bullet){
    Q_ASSERT(bullet);

    bullet_list.push_back(bullet);
}

void ChoiceWindow::deleteBullet(MyObject *bullet){
    Q_ASSERT(bullet);

    bullet_list.removeOne(bullet);
    delete bullet;
}

bool ChoiceWindow::loadWave(){
    if (wave > 3)  //wave初值为1，一共设3波敌人
        return false;
    if(wave==1){
        int enemyStartInterval[] = { 1000, 4000, 7000};
        for (int i = 0; i < 3; ++i){
            Enemy *enemy = new Enemy(QPoint(-150,240), QPoint(1200,240), this);
            enemy->slowSpeed();
            enemy_list.push_back(enemy);

            QTimer::singleShot(enemyStartInterval[i], enemy, SLOT(turnAlive()));
        }
    }
    if(wave==2){
        int enemyStartInterval[] = { 1000, 3000,5000,7000,10500,13000,15000, 18000,20000};
        for (int i = 0; i < 9; ++i){
            Enemy *enemy = new Enemy(QPoint(-150,240), QPoint(1200,240), this);
            enemy->fastSpeed();
            enemy->changeEnemyType_1();
            enemy_list.push_back(enemy);

            QTimer::singleShot(enemyStartInterval[i], enemy, SLOT(turnAlive()));
        }
    }
    if(wave==3){
        int enemyStartInterval[] = { 1000,3500,6000,8500,11000};
        for (int i = 0; i < 5; ++i){
            Enemy *enemy = new Enemy(QPoint(-150,240), QPoint(1200,240), this);
            enemy->fastSpeed();
            enemy->fastSpeed();
            enemy->changeEnemyType_2();
            enemy_list.push_back(enemy);

            QTimer::singleShot(enemyStartInterval[i], enemy, SLOT(turnAlive()));
        }
    }

    return true;
}

void ChoiceWindow::showInfo(QPainter *painter){
    painter->save();  //先把画笔未改变状态之前的样子存起来
    painter->setPen(Qt::white);  //画笔颜色为白
    painter->setFont(QFont("Comic Sans MS", 17 ));  //设置字体和字号
    painter->drawText(QRect(70,550,400,100) , QString("HP: %1    wave: %2").arg(HP).arg(wave));
                      //指定绘画范围矩形框。左上角坐标（...,...），宽度...，高度...。
                      //输入信息。格式：第一个参数%1，第二个参数%2，括号外.arg(num1).arg(num2)
       //注意：尚未设置HP和wave值改变后，以上数字也改变的功能。可能会用到updatescene函数（吧）
    painter->restore();   //画完后恢复画笔
}

void ChoiceWindow::updateScene(){ //用于多次更新界面达到动画效果
    foreach (Enemy *enemy, enemy_list){
        enemy->move();
    }
    foreach (Tower *tower, tower_list){
        tower->checkEnemyInRange();
    }
    update();
}

QList<Enemy *> ChoiceWindow::fun_enemy_list() const{
    return enemy_list;
}

void ChoiceWindow::gameStart(){
    loadWave();
}



