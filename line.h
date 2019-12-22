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
    void RotateFigure(QPoint RotateCenter, int angle);
    void ScaleFigure(QPoint ScaleCenter, float mutiple);
    void CutUseCohen(int x1,int y1,int x2, int y2);
    void CutUseBarsky(int x1,int y1,int x2, int y2);
    void PrintMyself();
    static void DrawUseBresenham(QPainter& pp,QPoint& begin,QPoint& end);
    static void DrawUseDDA(QPainter& pp,QPoint& begin,QPoint& end);
    void DrawUseBresenham(QPainter& pp);
    void DrawUseDDA(QPainter& pp);

    void Move(int x, int y);
};

#endif // LINE_H
