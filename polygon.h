#ifndef POLYGON_H
#define POLYGON_H
#include "figure.h"
#include "line.h"

class Polygon : public Figure
{
private:
    vector<QPoint> Vertex;      //多边形顶点集
public:
    Polygon();
    Polygon(int ID);
    Polygon(const vector<QPoint> &vertexes);
    void AddVertex(QPoint p);
    void DrawFigure(QPainter &pp);
    void RotateFigure(QPoint RotateCenter, int angle);
    void ScaleFigure(QPoint ScaleCenter, float mutiple);
    void PrintMyself();
    void DrawUseDDA(QPainter &pp);
    void DrawUseBresenham(QPainter &pp);

    void Move(int x, int y);
};

#endif // POLYGON_H
