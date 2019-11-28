#ifndef CURVE_H
#define CURVE_H
#include "figure.h"

class Curve : public Figure
{
private:
    vector<QPoint> ControlPoints;
public:
    Curve();
    Curve(const vector<QPoint> &points);
    void AddControlPoint(QPoint p);
    void DrawFigure(QPainter &pp);
    void DrawFigureUseBezier(QPainter &pp);
};

#endif // CURVE_H
