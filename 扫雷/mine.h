#ifndef MINEITNIT_H
#define MINEITNIT_H

#include <stdio.h>
#include <QMessageBox>
#include <QPainter>
#include <QTimer>
#include <QTime>

class mineItnit
{
public:
    mineItnit();
    void initMine(int y_i, int x_j);
    void beforeinit();
     int scan(int i, int j);
     void reseach_mine(int i, int j);
     void leftmouse(int y_i,int x_j);
     void rightmouse(int y_i, int x_j);
     int paintevent(QPainter &painter);
private:
    int mine[8][8];
    int lei[8][8];  //雷的位置
    int firstpress;
};

#endif // MINEITNIT_H
