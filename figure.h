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

};

#endif // FIGURE_H
