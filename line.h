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
private:
    QPoint startPoint;
    QPoint endPoint;
    int id;

public:
    Line();
    Line(int line_id,QPoint s,QPoint e);
    void DrawFigure();
    void DrawUseBresenham(QPainter& pp,QPoint& begin,QPoint& end);
    void DrawUseBresenham(QPainter& pp);
};

#endif // LINE_H
