#ifndef LINE_H
#define LINE_H
#include "figure.h"
#include <QPainter>
#include<QPoint>
#include<QPen>
#include<QColor>
#include<queue>
#include<math.h>
#include<vector>
#include<iostream>

class Line : public Figure
{
public:
    Line();
    void DrawFigure();
    void DrawUseBresenham(QPainter& pp,QPoint& begin,QPoint& end);
};

#endif // LINE_H
