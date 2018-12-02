#include "snake_class.h"

snake_class::snake_class():s_drict(D_RIGHT)
{
    arrQPoint Hand = {
        QPoint(2, 2),
        QPoint(-2,2),
        QPoint(-2,-2),
        QPoint(2,-2)
     };
    s_list.clear();
    s_list.append(Hand);
}

void move(QPoint nextpos[4]);
void eat(QPoint food[4]);
bool isSelf(QPoint nextpos[4]);
bool isCrash(QPoint nextpos[4]);
