#include "curve.h"

//求阶乘的小函数，用于计算n阶Bezier曲线各项系数
int factorial(int n){
    if(n==0)
        return 1;
    if(n<0)
        return n;
    int res=1;
    for(int i=1;i<=n;i++)
    {
        res*=i;
    }
    return res;
}

Curve::Curve()
{

}

Curve::Curve(int ID)
{
    id = ID;
}

Curve::Curve(const vector<QPoint> &points, CurveType type)
{
    for(size_t i=0;i<points.size();i++){
        ControlPoints.push_back(points[i]);
    }
    curveType=type;
}

void Curve::AddControlPoint(QPoint p)
{
    ControlPoints.push_back(p);
}

void Curve::DrawFigure(QPainter &pp)
{
    if(curveType==CurveType::BezierCurve)
        DrawUseBezier(pp);
    else if(curveType==CurveType::BSplineCurve)
        DrawUseBSpline(pp);
}

void Curve::RotateFigure(QPoint RotateCenter, int angle)
{
    for(size_t i=0;i<ControlPoints.size();i++){
        Figure::RotatePoint(ControlPoints[i],RotateCenter,angle);
    }
}

void Curve::ScaleFigure(QPoint ScaleCenter, float mutiple)
{
    for(size_t i=0;i<ControlPoints.size();i++){
        Figure::ScalePoint(ControlPoints[i],ScaleCenter,mutiple);
    }
}

void Curve::PrintMyself()
{

}

void Curve::DrawUseBezier(QPainter &pp)
{
    for(double u=0;u<=1;u+=0.001){
        vector<double> coefficients;        //用来存储生成曲线的Bezier公式的各项系数，系数个数=控制点=阶数+1
        size_t n = ControlPoints.size()-1;
        for(size_t i=0;i<=n;i++){
            double coefficient = (1.0*factorial(n)/(factorial(i)*factorial(n-i)))*pow(1-u,n-i)*pow(u,i);
            coefficients.push_back(coefficient);
        }
        double posX=0;
        double posY=0;
        for(size_t i=0;i<ControlPoints.size();i++){
            posX+=ControlPoints[i].x()*coefficients[i];
            posY+=ControlPoints[i].y()*coefficients[i];
        }
        QPoint temp((int)(posX+0.5),(int)(posY+0.5));
        pp.drawPoint(temp);
    }
}

void Curve::DrawUseBSpline(QPainter &pp)
{
    if(ControlPoints.size()<4){     //少于四个控制点没法画
        ControlPoints.clear();
        return;
    }
    for(size_t i=0;i<=ControlPoints.size()-4;i++){
        for(double t=0;t<=1;t+=0.001){
            //计算三次B样条曲线的四个系数
            double a1 = 1.0/6*pow(1-t,3);
            double a2 = 1.0/6*(3*t*t*t-6*t*t+4);
            double a3 = 1.0/6*(1-3*t*t*t+3*t*t+3*t);
            double a4 = 1.0/6*t*t*t;
            int x = (int)(ControlPoints[i].x()*a1+ControlPoints[i+1].x()*a2+ControlPoints[i+2].x()*a3+ControlPoints[i+3].x()*a4);
            int y = (int)(ControlPoints[i].y()*a1+ControlPoints[i+1].y()*a2+ControlPoints[i+2].y()*a3+ControlPoints[i+3].y()*a4);
            QPoint temp(x,y);
            pp.drawPoint(temp);
        }
    }
}

void Curve::Move(int x, int y)
{
    for(size_t i=0;i<ControlPoints.size();i++){
        QPoint newPoint(ControlPoints[i].x()+x,ControlPoints[i].y()+y);
        ControlPoints[i]=newPoint;
    }
}
