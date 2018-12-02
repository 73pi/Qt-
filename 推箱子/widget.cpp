#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    m_map(1),
    win_flag(0)
{
    ui->setupUi(this);
    this->setWindowTitle("推箱子");
    this->setMinimumSize(360,360);
    this->setMaximumSize(360,360);

    if(0 != loadmap())
    {
        QMessageBox::information(this, "错误", "地图读取失败，退出!");
        this->close();
    }
    for(int i = 0; i < 12; i++)
        for(int j = 0; j < 12; j++)
            m_arr_map[i][j] = 0;

    QTimer *pTimer = new QTimer(this);
    connect(pTimer,SIGNAL(timeout()),this,SLOT(update()));
    pTimer->start(95);
    ui->level->display(m_map);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *)
{
    if(win_flag == 1)
        win_flag = 0;
    int map_pos_num = map_pos.size();
    for(int i = 0; i<map_pos_num; i++,i++)
    {
        if(m_arr[map_pos.at(i)][map_pos.at(i+1)] == 0)
            m_arr[map_pos.at(i)][map_pos.at(i+1)] = 3;
    }
   QPainter painter(this);
    for(int i = 0; i<12; i++)
        for(int j = 0; j<12; j++)
        {
            char dir[20];
            sprintf(dir,":/image/%d.jpg",m_arr[i][j]);
            painter.drawPixmap(30*j, 30*i , QPixmap(dir));
            if(m_arr[i][j] == 2 || m_arr[i][j] == 3)
            {
                if(win_flag==0)
                    win_flag = 1;
            }
        }
    if(win_flag == 0)
    {
        if(m_map==16)
            QMessageBox::information(NULL, "提示", "全部通关");
        else
        {
            win_flag=-1;
            QMessageBox::information(NULL, "提示", "恭喜过关");
        }
     }
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    int x_j = event->pos().rx()/30;
    int y_i = event->pos().ry()/30;
    if(m_arr[y_i][x_j] == 1 ||
            m_arr[y_i][x_j] == 6)
        return;
    int pos_pos[2] = {x_j, y_i};
    for(int i = 0; i < 12; i++)
        for(int j = 0; j < 12; j++)
            m_arr_map[i][j] = 0;
    if(nocorner(people_pos,pos_pos)==false &&
            onecorner(people_pos,pos_pos)==false &&
            morecorner(people_pos,pos_pos)==false)
        return;

    //推箱子和位移===========================================
    if(m_arr[y_i][x_j] == 2 || m_arr[y_i][x_j] == 5)
    {
        if(x_j == people_pos[0] && nocorner(people_pos,pos_pos))
        {
            if(y_i<people_pos[1])
            {
                if(m_arr[y_i-1][x_j] == 3)
                    m_arr[y_i-1][x_j] = 5;
                else if(m_arr[y_i-1][x_j] == 1 || m_arr[y_i-1][x_j] ==2 || m_arr[y_i-1][x_j] ==5)
                    return;
                else
                    m_arr[y_i-1][x_j] = 2;
            }
            else
            {
                if(m_arr[y_i+1][x_j] == 3)
                    m_arr[y_i+1][x_j] = 5;
                else if(m_arr[y_i+1][x_j] == 1 || m_arr[y_i+1][x_j] == 2 || m_arr[y_i+1][x_j] == 5)
                    return;
                else
                    m_arr[y_i+1][x_j] =2;
            }
        }
        else if(y_i == people_pos[1]  && nocorner(people_pos,pos_pos))
        {
            if(x_j<people_pos[0])
            {
                if(m_arr[y_i][x_j-1] == 3)
                    m_arr[y_i][x_j-1] = 5;
                else if(m_arr[y_i][x_j-1] == 1 || m_arr[y_i][x_j-1] == 2  || m_arr[y_i][x_j-1] == 5)
                    return;
                else
                    m_arr[y_i][x_j-1] =2;
            }
            else
            {
                if(m_arr[y_i][x_j+1] == 3)
                    m_arr[y_i][x_j+1] = 5;
                else if(m_arr[y_i][x_j+1] == 1 || m_arr[y_i][x_j+1] == 2  || m_arr[y_i][x_j+1] == 5)
                    return;
                else
                    m_arr[y_i][x_j+1] = 2;
            }
        }
        else
            return;
    }
    m_arr[people_pos[1]][people_pos[0]] =0;
    m_arr[y_i][x_j] = 4;
    people_pos[0] = x_j;
    people_pos[1] = y_i;
}

 int Widget::loadmap()
 {
     char map_dir[20];
     sprintf(map_dir,":/map/%d.map",m_map);
     QFile file(map_dir);
     if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
         return -1;

     map_pos.clear();
     int i=0;
     while(!file.atEnd())
     {
         QByteArray data = file.readLine();
         QString line = data;
         QStringList subs = line.split(' ');
         for(int j = 0; j<12; j++)
         {
                QString num = subs.at(j);
                m_arr[i][j] = num.toInt();
                if(m_arr[i][j] == 4)//人
                {
                    people_pos[0] = j;  //x
                    people_pos[1] = i;  //y
                }
                if(m_arr[i][j] == 3)//结束点
                {
                    map_pos.append(i);
                    map_pos.append(j);
                }
         }
         i++;
     }
     win_flag=0;
     return 0;
 }


 bool Widget::nocorner(int ffirstxy[2], int fsecondxy[2])
 {
     if(ffirstxy[1] == fsecondxy[1])
     {
         int max=ffirstxy[0]>fsecondxy[0]?ffirstxy[0]:fsecondxy[0];
         int min=ffirstxy[0]<fsecondxy[0]?ffirstxy[0]:fsecondxy[0];
         for(int i = 1; i<(max-min); i++)
         {
             if(m_arr[ffirstxy[1]][min+i] != 0 && m_arr[ffirstxy[1]][min+i] != 3)
                 return false;
         }
         return true;
     }
     else if(ffirstxy[0] == fsecondxy[0])
     {
         int max=ffirstxy[1]>fsecondxy[1]?ffirstxy[1]:fsecondxy[1];
         int min=ffirstxy[1]<fsecondxy[1]?ffirstxy[1]:fsecondxy[1];
         for(int i = 1; i<(max-min); i++)
         {
             if(m_arr[min+i][ffirstxy[0]] !=0 && m_arr[min+i][ffirstxy[0]] !=3)
                 return false;
         }
         return true;
     }
     return false;
 }

 bool Widget::onecorner(int ffirstxy[2], int fsecondxy[2])
 {
     int fx_sy[2]={ffirstxy[0], fsecondxy[1]};
     int sx_fy[2]={fsecondxy[0], ffirstxy[1]};
     if((nocorner(ffirstxy,fx_sy) && nocorner(fx_sy,fsecondxy) && (m_arr[fx_sy[1]][fx_sy[0]]==0||m_arr[fx_sy[1]][fx_sy[0]]==3)) ||
          (nocorner(ffirstxy,sx_fy) && nocorner(sx_fy,fsecondxy) && (m_arr[sx_fy[1]][sx_fy[0]]==0||m_arr[fx_sy[1]][fx_sy[0]]==3)))
         return true;
    return false;
 }

 bool Widget::morecorner(int ffirstxy[2], int fsecondxy[2])
 {
     for(int i = 1; i< 12-ffirstxy[1]; i++)
     {
         int mffirstxy[2]={ffirstxy[0], ffirstxy[1]+i};
         if(m_arr_map[mffirstxy[1]][mffirstxy[0]] == 0)
             m_arr_map[mffirstxy[1]][mffirstxy[0]] =1;
         else
             break;
         if(m_arr[mffirstxy[1]][mffirstxy[0]]!=0&&m_arr[mffirstxy[1]][mffirstxy[0]]!=3)
             break;
         if(onecorner(mffirstxy,fsecondxy))
             return true;
         if(morecorner(mffirstxy,fsecondxy))
             return true;
     }
     for(int i = 1; i< ffirstxy[1]+1; i++)
     {
         int mffirstxy[2]={ffirstxy[0], ffirstxy[1]-i};
         if(m_arr_map[mffirstxy[1]][mffirstxy[0]] == 0)
             m_arr_map[mffirstxy[1]][mffirstxy[0]] =1;
         else
             break;
         if(m_arr[mffirstxy[1]][mffirstxy[0]]!=0&&m_arr[mffirstxy[1]][mffirstxy[0]]!=3)
             break;
         if(onecorner(mffirstxy,fsecondxy))
             return true;
         if(morecorner(mffirstxy,fsecondxy))
             return true;
     }
     for(int i = 1; i< 12-ffirstxy[0]; i++)
     {
         int mffirstxy[2]={ffirstxy[0]+i, ffirstxy[1]};
         if(m_arr_map[mffirstxy[1]][mffirstxy[0]] == 0)
             m_arr_map[mffirstxy[1]][mffirstxy[0]] =1;
         else
             break;
         if(m_arr[mffirstxy[1]][mffirstxy[0]]!=0&&m_arr[mffirstxy[1]][mffirstxy[0]]!=3)
             break;
         if(onecorner(mffirstxy,fsecondxy))
             return true;
         if(morecorner(mffirstxy,fsecondxy))
             return true;
     }
     for(int i = 1; i< ffirstxy[0]+1; i++)
     {
         int mffirstxy[2]={ffirstxy[0]-i, ffirstxy[1]};
         if(m_arr_map[mffirstxy[1]][mffirstxy[0]] == 0)
             m_arr_map[mffirstxy[1]][mffirstxy[0]] =1;
         else
             break;
         if(m_arr[mffirstxy[1]][mffirstxy[0]] !=0&&m_arr[mffirstxy[1]][mffirstxy[0]]!=3)
             break;
         if(onecorner(mffirstxy,fsecondxy))
             return true;
         if(morecorner(mffirstxy,fsecondxy))
             return true;
     }
    return false;
 }


void Widget::on_restsrtbut_clicked()
{
    if(0 != loadmap())
    {
        QMessageBox::information(NULL,"错误", "地图读取失败，退出!");
        this->close();
    }
}

void Widget::on_endbut_clicked()
{
    m_map++;
    ui->level->display(m_map);
    if(0 != loadmap())
    {
        QMessageBox::information(NULL, "错误", "地图读取失败，退出!");
        this->close();
    }
}
