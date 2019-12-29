#include "line.h"
#include "bitset"
using std::bitset;

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

void Line::DrawFigure(QPainter& pp)
{
    DrawUseBresenham(pp,startPoint,endPoint);
}

void Line::RotateFigure(QPoint RotateCenter, int angle)
{
    Figure::RotatePoint(startPoint,RotateCenter,angle);
    Figure::RotatePoint(endPoint,RotateCenter,angle);
}

void Line::ScaleFigure(QPoint ScaleCenter, float mutiple)
{
    Figure::ScalePoint(startPoint,ScaleCenter,mutiple);
    Figure::ScalePoint(endPoint,ScaleCenter,mutiple);
}

//void Line::CutUseCohen(int XWmin, int YWmax, int XWmax, int YWmin)      //x1,y1,x2,y2
void Line::CutUseCohen(int x1, int y1, int x2, int y2)
{

    bitset<4> flag1("0000");
    bitset<4> flag2("0000");
    if(startPoint.y()<y1)
        flag1[0]=1;
    if(startPoint.y()>y2)
        flag1[1]=1;
    if(startPoint.x()>x2)
        flag1[2]=1;
    if(startPoint.x()<x1)
        flag1[3]=1;

    if(endPoint.y()<y1)
        flag2[0]=1;
    if(endPoint.y()>y2)
        flag2[1]=1;
    if(endPoint.x()>x2)
        flag2[2]=1;
    if(endPoint.x()<x1)
        flag2[3]=1;
//    CutUseBarsky(x1,y1,x2,y2);return;
    if(flag1.to_string()=="0000"&&flag2.to_string()=="0000"){   //完全在矩形框内，全取
        qDebug()<<"直线全取"<<endl;
        return;
    }
    while(flag1.to_string()!="0000"||flag2.to_string()!="0000"){
        if ((flag1 & flag2).to_string()!="0000"){
            qDebug()<<"直线舍弃"<<endl;
            startPoint.setX(-1);
            startPoint.setY(-1);
            endPoint.setX(-1);
            endPoint.setY(-1);
            return;
        }

        //flag标记 第一位：上 第二位：下 第三位：右 第四位：左
        cout<<"flag1:"<<(flag1.to_string())<<"  flag2:"<<flag2.to_string()<<endl;
        bitset<4> flag;
        if(flag1.to_string()!="0000")
            flag=flag1;
        else
            flag=flag2;

        if(flag1.to_string()==flag2.to_string()&&(flag1&flag2).to_string()!="0000"){    //完全不在框内，全舍
            qDebug()<<"直线舍弃"<<endl;
            startPoint.setX(-1);
            startPoint.setY(-1);
            endPoint.setX(-1);
            endPoint.setY(-1);
            return;
        }
        int x,y;
        //左右上下的顺序
        if(flag[3]!=0){
            x = x1;
            y = startPoint.y() + 1.0*(endPoint.y() - startPoint.y())*(x1 - startPoint.x()) / (endPoint.x() - startPoint.x());
        }
        else if(flag[2]!=0){
            x = x2;
            y = startPoint.y() + 1.0*(endPoint.y() - startPoint.y())*(x2 - startPoint.x()) / (endPoint.x() - startPoint.x());
        }
        else if(flag[0]!=0){
            y = y1;
            x = startPoint.x() + 1.0*(endPoint.x() - startPoint.x())*(y1 - startPoint.y()) / (endPoint.y() - startPoint.y());
        }
        else if(flag[1]!=0){
            y = y2;
            x = startPoint.x() + 1.0*(endPoint.x() - startPoint.x())*(y2 - startPoint.y()) / (endPoint.y() - startPoint.y());
        }

        if(flag1.to_string()==flag.to_string()){    //当前循环处理的是startPoint
            startPoint.setX(x);
            startPoint.setY(y);
            //重新计算flag
            if(startPoint.y()<y1)
                flag1[0]=1;
            else
                flag1[0]=0;
            if(startPoint.y()>y2)
                flag1[1]=1;
            else
                flag1[1]=0;
            if(startPoint.x()>x2)
                flag1[2]=1;
            else
                flag1[2]=0;
            if(startPoint.x()<x1)
                flag1[3]=1;
            else
                flag1[3]=0;
        }
        else{                                       //当前循环处理的是endPoint
            endPoint.setX(x);
            endPoint.setY(y);
            //重新计算flag
            if(startPoint.y()<y1)
                flag2[0]=1;
            else
                flag2[0]=0;
            if(startPoint.y()>y2)
                flag2[1]=1;
            else
                flag2[1]=0;
            if(startPoint.x()>x2)
                flag2[2]=1;
            else
                flag2[2]=0;
            if(startPoint.x()<x1)
                flag2[3]=1;
            else
                flag2[3]=0;
        }
    }

}

void Line::CutUseBarsky(int x1, int y1, int x2, int y2)
{
    qDebug()<<"Before cut startPoint:"<<startPoint<<" EndPoint:"<<endPoint<<endl;
    int xmin=x1,xmax=x2;
    int ymin=y1,ymax=y2;

    double p[4];
    double q[4];
    int startX=startPoint.x();int endX=endPoint.x();
    int startY=startPoint.y();int endY=endPoint.y();
    p[0]=-(endX-startX);
    p[1]=endX-startX;
    p[2]=-(endY-startY);
    p[3]=endY-startY;

    q[0]=startX-xmin;
    q[1]=xmax-startX;
    q[2]=startY-ymin;
    q[3]=ymax-startY;

    double u1=0,u2=1;
    /*若存在p[k]=0，线段平行于窗口某边界*/
    for(int i=0;i<4;i++)
    {
        if(p[i]==0)
        {
            if(q[i]<0){
                /*应当舍弃该直线*/
                qDebug()<<"直线被舍弃1"<<endl;
                startPoint.setX(-1);
                startPoint.setY(-1);
                endPoint.setX(-1);
                endPoint.setY(-1);
                return;
            }
        }
        else{
            /*此边界与直线有交点,更新u1,u2*/
            double r=q[i]/p[i];
            if(p[i]<0)//由外到内
                u1=max(u1,r);
            else //由内到外
                u2=min(u2,r);
        }
    }
    if(u1>u2){//裁剪的左侧在右侧的右边，舍弃
        qDebug()<<"直线被舍弃2"<<endl;
        startPoint.setX(-1);
        startPoint.setY(-1);
        endPoint.setX(-1);
        endPoint.setY(-1);
        return;
    }
    else{

        startPoint.setX(startX+(int)(u1*p[1]+0.5));
        startPoint.setY(startY+(int)(u1*p[3]+0.5));

        endPoint.setX(startX+(int)(u2*p[1]+0.5));
        endPoint.setY(startY+(int)(u2*p[3]+0.5));
        qDebug()<<"After cut startPoint:"<<startPoint<<" EndPoint:"<<endPoint<<endl;
        return;
    }
}

void Line::PrintMyself()
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

void Line::DrawUseDDA(QPainter &pp, QPoint &begin, QPoint &end)
{
    int x1,y1,x2,y2,dx,dy;
    int sign;
    if(begin.x()<end.x()){
        x1=begin.x();
        y1=begin.y();
        x2=end.x();
        y2=end.y();
    }
    else{
        x1=end.x();
        y1=end.y();
        x2=begin.x();
        y2=begin.y();
    }
    //保证从左到右生成线段
    dx=abs(x2-x1);
    dy=abs(y2-y1);
    if(dx>dy){          //斜率的绝对值小于1，以x作为递增基准
        double k = dy*1.0/dx;
        sign=y2>y1?1:-1;
        int x=x1;
        double y=y1;
        for(;x<=x2;x++)
        {
            y+=k*sign;
            pp.drawPoint(x,(int)y);
        }
    }
    if(dx<dy){          //斜率的绝对值大于1，以y作为递增基准
        sign=y2>y1?1:-1;
        double k = dx*1.0/dy;       //实际上是斜率的倒数
        if(sign==1){     //正斜率
            int y=y1;
            double x=x1;
            for(;y<=y2;y++)
            {
                x+=k;
                pp.drawPoint((int)x,y);
            }
        }
        else{
            int y=y1;
            double x=x1;
            for(;y>=y2;y--)
            {
                x+=k;
                pp.drawPoint((int)x,y);
            }
        }
    }
}

void Line::DrawUseBresenham(QPainter &pp)
{
    DrawUseBresenham(pp,startPoint,endPoint);
}

void Line::DrawUseDDA(QPainter &pp)
{
    DrawUseDDA(pp,startPoint,endPoint);
}

void Line::Move(int x, int y)
{
    QPoint newPoint1(startPoint.x()+x,startPoint.y()+y);
    QPoint newPoint2(endPoint.x()+x,endPoint.y()+y);
    startPoint = newPoint1;
    endPoint = newPoint2;
}
