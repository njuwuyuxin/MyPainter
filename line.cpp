#include "line.h"

Line::Line()
{
    id=-1;
    QPoint NullPoint(0,0);
    startPoint=endPoint=NullPoint;
}

Line::Line(int line_id,QPoint s, QPoint e)
{
    id=line_id;
    startPoint = s;
    endPoint = e;
}

void Line::DrawFigure()
{

}

void Line::DrawUseBresenham(QPainter &pp, QPoint &begin, QPoint &end)
{
    int x1,y1,x2,y2,dx,dy;
    bool sign;
    x1=begin.x()<end.x()?begin.x():end.x();
    y1=begin.x()<end.x()?begin.y():end.y();
    x2=begin.x()<end.x()?end.x():begin.x();
    y2=begin.x()<end.x()?end.y():begin.y();
    dx=abs(x2-x1);
    dy=abs(y2-y1);
    if(dx>dy){//斜率的绝对值小于1
        sign=y2>y1?1:0;
        int x,y,p;
        x=x1;
        y=y1;
        p=2*dy-dx;//默认起始点为左端点
        for(;x<=x2;x++)
        {
            pp.drawPoint(x,y);
            if(p>=0)
            {
                y=y+(sign?1:-1);//斜率为正为1，斜率为负为-1
                p+=2*(dy-dx);
            }
            else
            {
                p+=2*dy;
            }
        }
    }
    else{//斜率绝对值大于1
        int x,y,p;
        if(y1>y2){
            swap(x1,x2);
            swap(y1,y2);
        }
        x=x1;y=y1;//默认起始点为上端点

        p=2*dx-dy;
        //起始点为上端点
        for(;y<=y2;y++)
        {
            sign=x2>x1?true:false;
            pp.drawPoint(x,y);
            if(p>=0)
            {
                x=x+(sign?1:-1);//斜率为正为1，斜率为负为-1
                p+=2*(dx-dy);
            }
            else
            {
                p+=2*dx;
            }
        }
    }
}

void Line::DrawUseBresenham(QPainter &pp)
{
    DrawUseBresenham(pp,startPoint,endPoint);
}
