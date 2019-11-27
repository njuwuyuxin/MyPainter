#ifndef ELLIPSE_H
#define ELLIPSE_H
#include "figure.h"

class Ellipse : public Figure
{
private:
    int centerX;
    int centerY;
    int Rx;
    int Ry;
public:
    Ellipse();
    Ellipse(int cx,int cy,int rx,int ry);
    void DrawFigure(QPainter &pp);
    static void DrawUseMidOval(QPainter& pp,QPoint& begin,QPoint& end);         //已知起始点和终点坐标 画椭圆
    static void DrawUseMidOval(QPainter& pp,int centerX,int centerY,int Rx,int Ry);      //已知中心坐标和长短轴 画椭圆
};

#endif // ELLIPSE_H
