#include "polygon.h"

Polygon::Polygon()
{

}

Polygon::Polygon(int ID)
{
    id = ID;
}

void Polygon::AddVertex(QPoint p)
{
    Vertex.push_back(p);
}

void Polygon::DrawFigure(QPainter &pp)
{
    DrawUseBresenham(pp);
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
