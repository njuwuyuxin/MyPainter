#include "circle.h"

Circle::Circle()
{
    QPoint NullPoint(0,0);
    CenterPoint=EdgePoint=NullPoint;
    radius=0;
}

Circle::Circle(QPoint s, QPoint e)
{
    CenterPoint=s;
    EdgePoint=e;
    radius=CalculateDistance(s,e);
}

void Circle::DrawFigure(QPainter& pp)
{
    DrawUseMidCircle(pp,CenterPoint,radius);
}

void Circle::RotateFigure(QPoint RotateCenter, int angle)
{

}

void Circle::ScaleFigure(QPoint ScaleCenter, float mutiple)
{
    Figure::ScalePoint(CenterPoint,ScaleCenter,mutiple);
    radius = (int)(radius*mutiple);
}

void Circle::PrintMyself()
{

}

void Circle::DrawUseMidCircle(QPainter& pp, QPoint center, QPoint edge)
{
    int R=CalculateDistance(center,edge);
    DrawUseMidCircle(pp,center,R);
}

void Circle::DrawUseMidCircle(QPainter& pp, QPoint center, int R)
{
    int x,y,deltax,deltay,d;
    x=0;y=R;
    d=1-R;
    deltax=3;
    deltay=5-R-R;
    DrawLeftPart(pp,x,y,center);

    while(x<y)
    {
        if(d<0)
        {
             d+=deltax;
             deltax+=2;
             deltay+=2;
            x++;
        }
        else
        {
            d+=deltay;
            deltax+=2;
            deltay+=4;
            x++;
            y--;
        }
        //画八分之一部分，剩余部分坐标由对称可得

        DrawLeftPart(pp,x,y,center);
    }
}

void Circle::DrawLeftPart(QPainter &pp, int x, int y, QPoint &center)
{
    pp.drawPoint(center.x()+x,center.y()+y);
    pp.drawPoint(center.x()+y,center.y()+x);
    pp.drawPoint(center.x()+y,center.y()-x);
    pp.drawPoint(center.x()+x,center.y()-y);
    pp.drawPoint(center.x()-x,center.y()-y);
    pp.drawPoint(center.x()-y,center.y()-x);
    pp.drawPoint(center.x()-y,center.y()+x);
    pp.drawPoint(center.x()-x,center.y()+y);
}

void Circle::Move(int x, int y)
{
    QPoint newPoint(CenterPoint.x()+x,CenterPoint.y()+y);
    CenterPoint=newPoint;
}
