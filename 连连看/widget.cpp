#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setMaximumSize(320,256);
    this->setMinimumSize(320,256);

    QSound::play("/home/wu/qt_project/lianliankan/sound.wav");//调用静态函数来播放音乐，并且音乐应是wav

    firstxy[0]=firstxy[1]=-1;
    secondxy[0]=secondxy[1]=-1;

    int *adder = &arr[0][0];
   for( int i=0; i<20; i++)
        for(int j = 0; j<4; j++)
        {
            *adder=i;
            adder++;
        }
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    adder = &arr[0][0];
    for(int i = 0; i<40; i++)
    {
        int temp=qrand()%40;
        int tmp=*adder;
        *adder=*(adder+temp);
        *(adder+temp)=tmp;
        adder++;
    }
    for(int i = 0; i<40; i++)
    {
        int temp=qrand()%40;
        int tmp=*adder;
        *adder=*(adder-temp);
        *(adder-temp)=tmp;
        adder++;
    }

    QTimer *pTimer = new QTimer(this);
    connect(pTimer,SIGNAL(timeout()),this,SLOT(update()));
    pTimer->start(95);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::mousePressEvent(QMouseEvent *event)
{
   secondxy[1] = event->pos().rx()/32;
   secondxy[0] = event->pos().ry()/32;
   if(arr[firstxy[1]][firstxy[0]] == arr[secondxy[1]][secondxy[0]])
   {
       if(firstxy[1]!= secondxy[1] || firstxy[0] != secondxy[0] )
       {
           if(nocorner(firstxy,secondxy) ||
                   onecorner(firstxy,secondxy) ||
                   twocorner(firstxy,secondxy))
           {
               arr[firstxy[1]][firstxy[0]]=-1;
               arr[secondxy[1]][secondxy[0]]=-1;
           }
       }

   }
   else
   {
       firstxy[0]=secondxy[0];
       firstxy[1]=secondxy[1];
   }
}


void Widget::paintEvent(QPaintEvent *)
{
   QPainter painter(this);
    for(int i = 0; i<10; i++)
        for(int j = 0; j<8; j++)
        {
            char dri[20];
            sprintf(dri,":/image/%d.png",arr[i][j]);
            painter.drawPixmap(32*i, 32*j , QPixmap(dri));

        }
}

 bool Widget::nocorner(int ffirstxy[2], int fsecondxy[2])
 {
     if(ffirstxy[1] == fsecondxy[1])
     {
         if(ffirstxy[1] == 0 || ffirstxy[1] == 9)
             return true;
         int num=ffirstxy[0] - fsecondxy[0];
         if(num<0)
         {
             num=0-num;
             for(int i = 1; i<num; i++)
             {
                 if(arr[ffirstxy[1]][ffirstxy[0]+i] != -1)
                     return false;
             }
         }
         else
         {
             for(int i = 1; i<num; i++)
             {
                 if(arr[ffirstxy[1]][ffirstxy[0]-i] != -1)
                     return false;
             }
         }
         return true;
     }
     else if(ffirstxy[0] == fsecondxy[0])
     {
         if(ffirstxy[0] == 0 || ffirstxy[0] == 7)
             return true;
         int num=ffirstxy[1] - fsecondxy[1];
         if(num<0)
         {
             num=0-num;
             for(int i = 1; i<num; i++)
             {
                 if(arr[ffirstxy[1]+i][ffirstxy[0]] != -1)
                     return false;
             }
         }
         else
         {
             for(int i = 1; i<num; i++)
             {
                 if(arr[ffirstxy[1]-i][ffirstxy[0]] != -1)
                     return false;
             }
         }
         return true;
     }
     return false;
 }

 bool Widget::onecorner(int ffirstxy[2], int fsecondxy[2])
 {
     int fx_sy[2]={ffirstxy[0], fsecondxy[1]};
     int sx_fy[2]={fsecondxy[0], ffirstxy[1]};
     if((nocorner(ffirstxy,fx_sy) && nocorner(fx_sy,fsecondxy) && arr[fx_sy[1]][fx_sy[0]]==-1) ||
          (nocorner(ffirstxy,sx_fy) && nocorner(sx_fy,fsecondxy) && arr[sx_fy[1]][sx_fy[0]]==-1))
         return true;
    return false;
 }

 bool Widget::twocorner(int ffirstxy[2], int fsecondxy[2])
 {
     for(int i = 1; i< 10-ffirstxy[1]; i++)
     {
         int mffirstxy[2]={ffirstxy[0], ffirstxy[1]+i};
         if(arr[mffirstxy[1]][mffirstxy[0]]!=-1)
             break;
         if(onecorner(mffirstxy,fsecondxy))
             return true;
     }
     for(int i = 1; i< ffirstxy[1]+1; i++)
     {
         int mffirstxy[2]={ffirstxy[0], ffirstxy[1]-i};
         if(arr[mffirstxy[1]][mffirstxy[0]]!=-1)
             break;
         if(onecorner(mffirstxy,fsecondxy))
             return true;
     }
     for(int i = 1; i< 8-ffirstxy[0]; i++)
     {
         int mffirstxy[2]={ffirstxy[0]+i, ffirstxy[1]};
         if(arr[mffirstxy[1]][mffirstxy[0]]!=-1)
             break;
         if(onecorner(mffirstxy,fsecondxy))
             return true;
     }
     for(int i = 1; i< ffirstxy[0]+1; i++)
     {
         int mffirstxy[2]={ffirstxy[0]-i, ffirstxy[1]};
         if(arr[mffirstxy[1]][mffirstxy[0]] !=-1)
             break;
         if(onecorner(mffirstxy,fsecondxy))
             return true;
     }
    return false;
 }
