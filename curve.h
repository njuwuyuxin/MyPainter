#ifndef CURVE_H
#define CURVE_H
#include "figure.h"
enum CurveType{BezierCurve,BSplineCurve};
class Curve : public Figure
{
private:
    vector<QPoint> ControlPoints;
    CurveType curveType;

public:
    Curve();
    Curve(int ID);
    Curve(const vector<QPoint> &points,CurveType type);
    void AddControlPoint(QPoint p);
    void DrawFigure(QPainter &pp);
    void RotateFigure(QPoint RotateCenter, int angle);
    void ScaleFigure(QPoint ScaleCenter, float mutiple);
    void PrintMyself();
    void DrawUseBezier(QPainter &pp);
    void DrawUseBSpline(QPainter &pp);

    void Move(int x, int y);
};

#endif // CURVE_H
