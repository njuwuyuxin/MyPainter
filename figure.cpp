#include "figure.h"


void Figure::DrawUseBresenham(QPainter &pp)
{
    return;
}

void Figure::DrawUseDDA(QPainter &pp)
{
    return;
}

void Figure::DrawUseBezier(QPainter &pp)
{
    return;
}

void Figure::DrawUseBSpline(QPainter &pp)
{
    return;
}

int Figure::CalculateDistance(QPoint a, QPoint b)
{
    return (int)(sqrt(double(pow((a.x() - b.x()),2) + pow((a.y() - b.y()),2))));
}
