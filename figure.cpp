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

void Figure::CutUseCohen(int x1, int y1, int x2, int y2)
{
    return;
}

void Figure::CutUseBarsky(int x1, int y1, int x2, int y2)
{
    return;
}

int Figure::CalculateDistance(QPoint a, QPoint b)
{
    return (int)(sqrt(double(pow((a.x() - b.x()),2) + pow((a.y() - b.y()),2))));
}

void Figure::RotatePoint(QPoint &StartPoint, QPoint RotateCenter, int angle)
{
    qDebug()<<"original angle="<<angle<<endl;
    double RadiusAngle=angle*3.1415926535/180.0;
    double dx=StartPoint.x()-RotateCenter.x();
    double dy=StartPoint.y()-RotateCenter.y();
    qDebug()<<"radius angle="<<RadiusAngle<<endl;
    qDebug()<<"sin r:"<<sin(RadiusAngle)<<"  cos r:"<<cos(RadiusAngle)<<endl;
    StartPoint.setX(int(RotateCenter.x()+((double)(dx)*cos(RadiusAngle)-(double)(dy)*sin(RadiusAngle)+0.5)));
    StartPoint.setY(int(RotateCenter.y()+((double)(dx)*sin(RadiusAngle)+(double)(dy)*cos(RadiusAngle)+0.5)));
}

void Figure::ScalePoint(QPoint &StartPoint, QPoint ScaleCenter, float s)
{
//    qDebug()<<"ScaleCenter="<<ScaleCenter<<"   s="<<s<<"     StartPoint="<<StartPoint<<endl;
    float X=StartPoint.x()*s+ScaleCenter.x()*(1-s);
    float Y=StartPoint.y()*s+ScaleCenter.y()*(1-s);
    StartPoint.setX(int(X));
    StartPoint.setY(int(Y));
}
