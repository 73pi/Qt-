#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    x=2;
    y=2;
    fx=-2;
    fy=-2;
    flag=0;
    drict=D_RIGHT;
    createFood();
    QTimer *ptimer = new QTimer(this);
    connect(ptimer, SIGNAL(timeout()), this, SLOT(modify()));
    connect(ptimer, SIGNAL(timeout()), this, SLOT(update()));
    ptimer->start(200);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::modify()
{
    if(x>=100 || x<=-100 || fx>=100 || fx<=-100 ||y>=100 || y<=-100 ||fy>=100 || fy<=-100)
        this->close();
    if(flag==1)
        createFood();
    switch (drict) {
    case D_UP:
       y-=2;
       fy-=2;
        break;
    case D_DOWN:
        y+=2;
        fy+=2;
        break;
    case D_RIGHT:
        x+=2;
        fx+=2;
        break;
    case D_LEFT:
        x-=2;
        fx-=2;
        break;
    default:
        break;
    }

}

void Widget::paintEvent ( QPaintEvent * )
{
    QPoint Hand[4] = {
        QPoint(x, y),
        QPoint(fx, y),
        QPoint(fx,fy),
        QPoint(x,fy)
     };
    QPoint rHand[4] = {
        QPoint(rx+2, ry+2),
        QPoint(rx+2, ry-2),
        QPoint(rx-2, ry-2),
        QPoint(rx-2, ry+2)
     };

     QColor handColor(127, 0, 127);
     QColor rColor(127, 127, 127);

     int side = qMin(width(), height());

    //创建绘图类对象
    QPainter painter(this);
     painter.setRenderHint(QPainter::Antialiasing); //抗锯齿化
     painter.translate(width() / 2, height() / 2); //平移坐标系
     painter.scale(side / 200.0, side / 200.0);//按比例伸缩坐标系

     //设置画笔和画刷(时针)
     painter.setPen(Qt::NoPen);
     painter.setBrush(handColor);

      //绘制蛇头
     painter.save();
     painter.rotate(0);
      painter.drawConvexPolygon(Hand, 4);
      painter.restore();

      //绘制食物
      painter.setBrush(rColor);
      painter.save();
      painter.rotate(0);
       painter.drawConvexPolygon(rHand, 4);
       painter.restore();


      painter.setPen(handColor);
      painter.drawLine(-99, -99, -99, 99);
      painter.drawLine(-99, -99, 99, -99);
      painter.drawLine(99, 99, -99, 99);
      painter.drawLine(99, 99, 99, -99);


}

void Widget::createFood()
{
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    rx=(qrand()%200)-100;
    ry=(qrand()%200)-100;
}

void Widget::keyPressEvent ( QKeyEvent * event )
{
    if(event->key()==Qt::Key_Down)
        drict=D_DOWN;
    else if(event->key()==Qt::Key_Up)
        drict=D_UP;
    else if(event->key()==Qt::Key_Right)
        drict=D_RIGHT;
    else if(event->key()==Qt::Key_Left)
        drict=D_LEFT;
}

