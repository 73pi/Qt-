#include "mine.h"

mineItnit::mineItnit()
{
   beforeinit();
}

void mineItnit::beforeinit()
{
    firstpress=0;
    for(int i=0; i<8; i++)
        for(int j=0; j<8; j++)
        {
            mine[i][j]=-1;
            lei[i][j]=-1;
        }
}

void mineItnit::initMine(int y_i, int x_j)
{
    for(int i=0; i<8; i++)
        for(int j=0; j<8; j++)
        {
            mine[i][j]=-1;
            lei[i][j]=-1;
        }
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    int mine_num=0;
    while(1)
    {
        int rx=qrand()%8;
        int ry=qrand()%8;
        if(lei[ry][rx] == -1 &&  (rx != x_j && ry != y_i))
        {
            lei[ry][rx]=11;
            mine_num++;
        }
        if(mine_num == 10)
            break;
    }
}

int mineItnit::scan(int i, int j)
{
    int flag=0;
    if(i != 0)  //扫描上边
    {
        if(lei[i-1][j] == 11)
            flag++;
    }
    if(i != 7)  //扫描下边
    {
        if(lei[i+1][j] == 11)
            flag++;
    }
    if(j != 0)  //扫描左边
    {
        if(lei[i][j-1] == 11)
            flag++;
    }
    if(j != 7)  //扫描右边
    {
        if(lei[i][j+1] == 11)
            flag++;
    }
    if(i !=0 && j !=0)  //扫描左上边
    {
        if(lei[i-1][j-1] == 11)
            flag++;
    }
    if(i !=0 && j !=7)  //扫描右上边
    {
        if(lei[i-1][j+1] == 11)
            flag++;
    }
    if(i !=7 && j !=0)  //扫描左下边
    {
        if(lei[i+1][j-1] == 11)
            flag++;
    }
    if(i !=7 && j !=7)  //扫描右下边
    {
        if(lei[i+1][j+1] == 11)
            flag++;
    }
    return flag;
}

 void mineItnit::reseach_mine(int i, int j)
 {
     if(mine[i][j] != -1 && mine[i][j] != 22)
         return;
     int ret=scan(i, j);
     if(ret != 0)
     {
         mine[i][j]=scan(i, j);
     }
     else
     {
         mine[i][j]=0;
         if(i != 0)  //扫描上边
             reseach_mine(i-1, j);
         if(i != 7)  //扫描下边
              reseach_mine(i+1, j);
         if(j != 0)  //扫描左边
             reseach_mine(i, j-1);
         if(j != 7)  //扫描右边
             reseach_mine(i, j+1);
         if(i !=0 && j !=0)  //扫描左上边
             reseach_mine(i-1, j-1);
         if(i !=0 && j !=7)  //扫描右上边
             reseach_mine(i-1, j+1);
         if(i !=7 && j !=0)  //扫描左下边
             reseach_mine(i+1, j-1);
         if(i !=7 && j !=7)  //扫描右下边
             reseach_mine(i+1, j+1);
     }
 }

 void mineItnit::leftmouse(int y_i,int x_j)
 {
     if(firstpress == 0)
     {
         initMine(y_i, x_j); //初始化
         firstpress=1;
     }

     if(lei[y_i][x_j] == 11 && mine[y_i][x_j] != 21)
     {
         mine[y_i][x_j]=12;
         QMessageBox::information(NULL, "扫到雷了","下次加油!");
         beforeinit();
         return;
     }
     if(mine[y_i][x_j] == -1 || mine[y_i][x_j] == 22)
      reseach_mine(y_i, x_j);
 }

  void mineItnit::rightmouse(int y_i,int x_j)
  {
      if(mine[y_i][x_j] == -1)
          mine[y_i][x_j]=21;
      else if(mine[y_i][x_j] == 21)
          mine[y_i][x_j]=22;
      else if(mine[y_i][x_j] == 22)
          mine[y_i][x_j]=-1;
  }

int mineItnit::paintevent(QPainter &painter)
{
    int endGame=0;
    int emply=0;
     for(int i = 0; i<8; i++)
         for(int j = 0; j<8; j++)
         {
             char dir[20];
             sprintf(dir,":/Image/%d.png",mine[i][j]);
             painter.drawPixmap(20*j, 20*i , QPixmap(dir));
             if(mine[i][j] == 21 && lei[i][j] == 11)
                 endGame++;
             if(mine[i][j] == -1)
                 emply++;
         }
     if(endGame == 10 && emply == 0)
     {
         QMessageBox::information(NULL, "游戏结束","成功通过!");
         return 0;
     }
     return 1;
}
