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
    static int CalculateDistance(QPoint a,QPoint b);   //计算两点间距离，由于返回像素个数因此返回int
};

#endif // FIGURE_H
