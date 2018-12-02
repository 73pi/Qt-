#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <mine.h>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    virtual void paintEvent(QPaintEvent*);
    virtual void mousePressEvent(QMouseEvent *event);
private:
    Ui::Widget *ui;
    mineItnit ten;
};

#endif // WIDGET_H
