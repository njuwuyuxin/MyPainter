#ifndef ELLIPSE_H
#define ELLIPSE_H
#include "figure.h"

class Ellipse : public Figure
{
private:
    QPoint centerPoint;
    int Rx;
    int Ry;
public:
    Ellipse();
    Ellipse(int ID,int cx,int cy,int rx,int ry);
    void DrawFigure(QPainter &pp);
    void RotateFigure(QPoint RotateCenter, int angle);
    void ScaleFigure(QPoint ScaleCenter, float mutiple);
    static void DrawUseMidOval(QPainter& pp,QPoint& begin,QPoint& end);         //已知起始点和终点坐标 画椭圆
    static void DrawUseMidOval(QPainter& pp,int centerX,int centerY,int Rx,int Ry);      //已知中心坐标和长短轴 画椭圆

    void Move(int x, int y);
};

#endif // ELLIPSE_H
