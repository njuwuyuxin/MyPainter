#include "ellipse.h"

Ellipse::Ellipse()
{

}

Ellipse::Ellipse(int ID,int cx, int cy, int rx, int ry)
{
    id = ID;
    QPoint center(cx,cy);
    centerPoint = center;
    Rx=rx;
    Ry=ry;
}

void Ellipse::DrawFigure(QPainter &pp)
{
    DrawUseMidOval(pp,centerPoint.x(),centerPoint.y(),Rx,Ry);
}

void Ellipse::RotateFigure(QPoint RotateCenter, int angle)
{

}

void Ellipse::ScaleFigure(QPoint ScaleCenter, float mutiple)
{
    Figure::ScalePoint(centerPoint,ScaleCenter,mutiple);
    Rx=(int)(Rx*mutiple);
    Ry=(int)(Ry*mutiple);
}

void Ellipse::DrawUseMidOval(QPainter &pp, QPoint &begin, QPoint &end)
{
    int x0,y0,x1,y1,centerX,centerY;
    x0=begin.x();
    y0=begin.y();
    x1=end.x();
    y1=end.y();
    centerX=(x0+x1)/2;
    centerY=(y0+y1)/2;
    int Rx,Ry;
    Rx=abs(x0-x1)/2;
    Ry=abs(y0-y1)/2;

    DrawUseMidOval(pp,centerX,centerY,Rx,Ry);
}

void Ellipse::DrawUseMidOval(QPainter &pp, int centerX, int centerY, int Rx, int Ry)
{
    int x,y,p;
    x=0;
    y=Ry;
    p=4*Ry*Ry-4*Rx*Rx*Ry+Rx*Rx;
    pp.drawPoint(centerX+x,centerY+y);
    pp.drawPoint(centerX+x,centerY-y);

    while(Ry*Ry*x<Rx*Rx*y){
        if(p<0){
            p+=4 * (2 * Ry*Ry*x + 3 * Ry*Ry);
            x++;
        }
        else{
            p+=4 * (2 * Ry*Ry*x - 2 * Rx*Rx*y + 2 * Rx*Rx +3 * Ry*Ry);
            y--;
            x++;
        }
        pp.drawPoint(centerX+x,centerY+y);
        pp.drawPoint(centerX+x,centerY-y);
        pp.drawPoint(centerX-x,centerY+y);
        pp.drawPoint(centerX-x,centerY-y);
    }
    /* 第一象限下半部分的区域*/
    p=Ry*Ry*(2 * x +1)*(2 * x + 1) + 4 * Rx*Rx*(y-1)*(y-1)-4*Rx*Rx*Ry*Ry;
    while(y>0){

        if(p<=0){
            p += 4* (2 *Ry*Ry*x - 2* Rx*Rx*y+2*Ry*Ry+3*Rx*Rx);
            x++;
            y--;
        }
        else{
            p+= 4 *(-2 * Rx*Rx*y +3 *Rx*Rx);
            y--;
        }
        pp.drawPoint(centerX+x,centerY+y);
        pp.drawPoint(centerX+x,centerY-y);
        pp.drawPoint(centerX-x,centerY+y);
        pp.drawPoint(centerX-x,centerY-y);
    }
}

void Ellipse::Move(int x, int y)
{
    QPoint newPoint(centerPoint.x()+x,centerPoint.y()+y);
    centerPoint = newPoint;
}
