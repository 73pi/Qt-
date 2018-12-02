#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QPaintEvent>
#include <QPainter>
#include <stdio.h>
#include <QTimer>
#include <QTime>
/* 如果不能识别 QT+= multimedia 就sudo apt-get install qtmultimedia5-dev */
/* 播放音乐的播放库 sudo apt-get install nas nas-bin */
/* 调用静态函数来播放 */
#include <QSound>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

   virtual void paintEvent(QPaintEvent *);
    virtual void mousePressEvent(QMouseEvent *event);

private:
    Ui::Widget *ui;
    int arr[10][8];

    int firstxy[2];
    int secondxy[2];

    bool nocorner(int ffirstxy[], int fsecondxy[]);
    bool onecorner(int ffirstxy[], int fsecondxy[]);
    bool twocorner(int ffirstxy[], int fsecondxy[]);
};

#endif // WIDGET_H
