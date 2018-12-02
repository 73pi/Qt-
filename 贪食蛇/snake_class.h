#ifndef SNAKE_CLASS_H
#define SNAKE_CLASS_H
#include <QList>
#include <QPoint>
typedef struct arrQPoint
{
        QPoint snake_point[4];
} arrQPoint;
class snake_class
{
private:
    enum{D_UP=0, D_DOWN, D_LEFT, D_RIGHT};
    int s_drict; //方向
    QList<arrQPoint> s_list;
public:
    snake_class();
    ~snake_class(){}
    void move(arrQPoint nextpos);
    void eat(arrQPoint food);
    bool isSelf(arrQPoint nextpos);
    bool isCrash(arrQPoint nextpos);
};

#endif // SNAKE_CLASS_H
