#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>
#include <stdio.h>
#include <QFile>
#include <QMessageBox>
#include <QList>
#include <QString>
#include <QMouseEvent>
#include <QTimer>

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


    int loadmap();  //读地图

    bool nocorner(int ffirstxy[], int fsecondxy[]);
    bool onecorner(int ffirstxy[], int fsecondxy[]);
    bool morecorner(int ffirstxy[], int fsecondxy[]);


private slots:
    void on_restsrtbut_clicked();

    void on_endbut_clicked();

private:
    Ui::Widget *ui;

    int m_arr[12][12];
    int m_arr_map[12][12];  //纪录已经遍历的位置
    int people_pos[2];
    int m_map;
    int win_flag;
    QList<int> map_pos;
};

#endif // WIDGET_H
