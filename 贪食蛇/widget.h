#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPoint>
#include <QColor>
#include <QTime>
#include <QPainter>
#include <QTimer>
#include <QList>
#include <QKeyEvent>

namespace Ui {
class Widget;
}

enum{D_UP=0, D_DOWN, D_LEFT, D_RIGHT};

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void createFood();

protected:
    virtual void paintEvent ( QPaintEvent *);
    virtual void keyPressEvent ( QKeyEvent * event );
public slots:
    void modify();

private:
    Ui::Widget *ui;
    int x;
    int y;
    int fx;
    int fy;
    int rx;
    int ry;
    int flag;//1-吃了，0-没吃
    int drict;//方向
};

#endif // WIDGET_H
