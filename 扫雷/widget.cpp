#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("扫雷");
    this->setMaximumSize(160,160);
    this->setMinimumSize(160,160);

    QTimer *pTimer = new QTimer(this);
    connect(pTimer,SIGNAL(timeout()),this,SLOT(update()));
    pTimer->start(95);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    if(0 == ten.paintevent(painter))
        this->close();
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    int x_j = event->pos().rx()/20;
    int y_i = event->pos().ry()/20;

    if (event->button() == Qt::LeftButton)
        ten.leftmouse(y_i,x_j);

    if(event->button() == Qt::RightButton)
        ten.rightmouse(y_i,x_j);
}
