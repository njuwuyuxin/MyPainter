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

Curve::Curve(const vector<QPoint> &points)
{
    for(size_t i=0;i<points.size();i++){
        ControlPoints.push_back(points[i]);
    }
}

void Curve::AddControlPoint(QPoint p)
{
    ControlPoints.push_back(p);
}

void Curve::DrawFigure(QPainter &pp)
{
    DrawFigureUseBezier(pp);
}

void Curve::DrawFigureUseBezier(QPainter &pp)
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
