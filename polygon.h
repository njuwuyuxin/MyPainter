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
    void DrawFigureUseDDA(QPainter &pp);
    void DrawFigureUseBresenham(QPainter &pp);
};

#endif // POLYGON_H
