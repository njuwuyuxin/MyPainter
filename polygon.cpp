#include "polygon.h"

Polygon::Polygon()
{

}

Polygon::Polygon(int ID)
{
    id = ID;
}

Polygon::Polygon(const vector<QPoint> &vertexes)
{
    for(size_t i=0;i<vertexes.size();i++){
        Vertex.push_back(vertexes[i]);
    }
}

void Polygon::AddVertex(QPoint p)
{
    Vertex.push_back(p);
}

void Polygon::DrawFigure(QPainter &pp)
{
    DrawUseBresenham(pp);
}

void Polygon::RotateFigure(QPoint RotateCenter, int angle)
{
    for(size_t i=0;i<Vertex.size();i++){
        Figure::RotatePoint(Vertex[i],RotateCenter,angle);
    }
}

void Polygon::ScaleFigure(QPoint ScaleCenter, float mutiple)
{
    for(size_t i=0;i<Vertex.size();i++){
        Figure::ScalePoint(Vertex[i],ScaleCenter,mutiple);
    }
}

void Polygon::DrawUseDDA(QPainter &pp)
{
    for(size_t i=1;i<Vertex.size();i++){
        Line::DrawUseDDA(pp,Vertex[i-1],Vertex[i]);
    }
    Line::DrawUseDDA(pp,Vertex[Vertex.size()-1],Vertex[0]);   //进行封闭
}

void Polygon::DrawUseBresenham(QPainter &pp)
{
    for(size_t i=1;i<Vertex.size();i++){
        Line::DrawUseBresenham(pp,Vertex[i-1],Vertex[i]);
    }
    Line::DrawUseBresenham(pp,Vertex[Vertex.size()-1],Vertex[0]);   //进行封闭
}

void Polygon::Move(int x, int y)
{
    for(size_t i=0;i<Vertex.size();i++){
        QPoint newPoint(Vertex[i].x()+x,Vertex[i].y()+y);
        Vertex[i]=newPoint;
    }
}
