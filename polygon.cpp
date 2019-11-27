#include "polygon.h"

Polygon::Polygon()
{

}

void Polygon::AddVertex(QPoint p)
{
    Vertex.push_back(p);
}

void Polygon::DrawFigure(QPainter &pp)
{
    for(size_t i=1;i<Vertex.size();i++){
        Line::DrawUseBresenham(pp,Vertex[i-1],Vertex[i]);
    }
    Line::DrawUseBresenham(pp,Vertex[Vertex.size()-1],Vertex[0]);   //进行封闭
}
