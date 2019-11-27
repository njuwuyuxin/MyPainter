#ifndef CIRCLE_H
#define CIRCLE_H
#include "figure.h"

class Circle : public Figure
{
private:
    QPoint CenterPoint;         //圆心坐标
    QPoint EdgePoint;           //鼠标所在的圆边缘坐标
    int radius;                 //半径
public:
    Circle();
    Circle(QPoint s,QPoint e);
    void DrawFigure(QPainter& pp);
    static void DrawUseMidCircle(QPainter& pp,QPoint center,QPoint edge);          //已知两点坐标（适用于鼠标拖动）
    static void DrawUseMidCircle(QPainter& pp,QPoint center,int R);                //已知圆心和半径（适合通用画圆）
    static void DrawLeftPart(QPainter& pp,int x,int y,QPoint &center);              //画出其余剩余对称的部分
};

#endif // CIRCLE_H
