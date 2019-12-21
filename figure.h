#ifndef FIGURE_H
#define FIGURE_H

#include<QPainter>
#include<QPoint>
#include<QPen>
#include<QColor>
#include<queue>
#include<math.h>
#include<vector>
#include<iostream>
#include <QDebug>
using namespace std;

class Figure
{
public:
    int id;
    virtual void DrawFigure(QPainter& pp) = 0;              //画出图形
    virtual void DrawUseBresenham(QPainter& pp);
    virtual void DrawUseDDA(QPainter& pp);
    virtual void DrawUseBezier(QPainter& pp);
    virtual void DrawUseBSpline(QPainter& pp);

    virtual void RotateFigure(QPoint RotateCenter, int angle) = 0;      //图元绕旋转中心旋转angle角度
    virtual void ScaleFigure(QPoint ScaleCenter,float mutiple) = 0;     //图元以缩放中心，缩放mutiple倍
    virtual void Move(int x,int y)=0;                  //平移图元
    virtual void PrintMyself()=0;                      //打印图元有关信息
    static int CalculateDistance(QPoint a,QPoint b);   //计算两点间距离，由于返回像素个数因此返回int
    static void RotatePoint(QPoint& StartPoint, QPoint RotateCenter,int angle);       //将某一点绕旋转中心旋转angle角度
    static void ScalePoint(QPoint& StartPoint,QPoint ScaleCenter,float s);            //将某一点以缩放中心缩放s倍
};

#endif // FIGURE_H
