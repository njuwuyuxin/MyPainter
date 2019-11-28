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

public:
    Line();
    Line(int line_id,QPoint s,QPoint e);
    void DrawFigure(QPainter& pp);
    static void DrawUseBresenham(QPainter& pp,QPoint& begin,QPoint& end);
    static void DrawUseDDA(QPainter& pp,QPoint& begin,QPoint& end);
    void DrawUseBresenham(QPainter& pp);
    void DrawUseDDA(QPainter& pp);
};

#endif // LINE_H
