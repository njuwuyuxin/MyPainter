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
    void AddVertex(QPoint p);
    void DrawFigure(QPainter &pp);
    void DrawUseDDA(QPainter &pp);
    void DrawUseBresenham(QPainter &pp);

    void Move(int x, int y);
};

#endif // POLYGON_H
