#include "figure.h"


int Figure::CalculateDistance(QPoint a, QPoint b)
{
    return (int)(sqrt(double(pow((a.x() - b.x()),2) + pow((a.y() - b.y()),2))));
}
