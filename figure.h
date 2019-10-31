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
using namespace std;

class Figure
{
public:
    virtual void DrawFigure() = 0;              //画出图形
    int CalculateDistance(QPoint a,QPoint b);   //计算两点间距离，由于返回像素个数因此返回int
};

#endif // FIGURE_H
